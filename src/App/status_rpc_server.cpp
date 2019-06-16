//
// Copyright (c) 2016-2018 by Cornell University.  All Rights Reserved.
//
// Permission to use the "TownCrier" software ("TownCrier"), officially
// docketed at the Center for Technology Licensing at Cornell University
// as D-7364, developed through research conducted at Cornell University,
// and its associated copyrights solely for educational, research and
// non-profit purposes without fee is hereby granted, provided that the
// user agrees as follows:
//
// The permission granted herein is solely for the purpose of compiling
// the TownCrier source code. No other rights to use TownCrier and its
// associated copyrights for any other purpose are granted herein,
// whether commercial or non-commercial.
//
// Those desiring to incorporate TownCrier software into commercial
// products or use TownCrier and its associated copyrights for commercial
// purposes must contact the Center for Technology Licensing at Cornell
// University at 395 Pine Tree Road, Suite 310, Ithaca, NY 14850; email:
// ctl-connect@cornell.edu; Tel: 607-254-4698; FAX: 607-254-5454 for a
// commercial license.
//
// IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
// INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF TOWNCRIER AND ITS
// ASSOCIATED COPYRIGHTS, EVEN IF CORNELL UNIVERSITY MAY HAVE BEEN
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL
// UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
// ENHANCEMENTS, OR MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO
// REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED
// OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE
// OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT INFRINGE ANY
// PATENT, TRADEMARK OR OTHER RIGHTS.
//
// TownCrier was developed with funding in part by the National Science
// Foundation (NSF grants CNS-1314857, CNS-1330599, CNS-1453634,
// CNS-1518765, CNS-1514261), a Packard Fellowship, a Sloan Fellowship,
// Google Faculty Research Awards, and a VMWare Research Award.
//

#include "App/status_rpc_server.h"

#include <iostream>
#include <string>
#include <vector>

#include "App/converter.h"
#include "App/attestation.h"
#include "App/tc_exception.h"
#include "Common/external/base64.hxx"
#include "Common/version.h"

namespace tc {
namespace statusRPC {
log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("status_rpc_server.cpp"));
}
}

using tc::statusRPC::logger;
using tc::status_rpc_server;

using namespace std;

status_rpc_server::status_rpc_server(AbstractServerConnector &connector,
                                     sgx_enclave_id_t eid)
    : AbstractStatusServer(connector), eid(eid) {}

Json::Value status_rpc_server::attest(const std::string& x) {
  using tc::statusRPC::logger;
  Json::Value result;
  try {
    std::vector<uint8_t> attestation;
    uint8_t privkey[256] = {0};

    int buf_used = ext::b64_pton(x.c_str(),
                              privkey, sizeof privkey);
    if (buf_used < 0) {
      result["error"] = "can't do it, private key stuck";
      return result;
    } else {
      result["stuff"] = std::to_string(buf_used);
    }
    get_attestation(privkey, this->eid, &attestation);

    const auto *mr_enclave_p = (reinterpret_cast<sgx_quote_t *>(attestation.data()))->report_body.mr_enclave.m;

    char b64_buf[4096] = {0};
    buf_used = ext::b64_ntop(attestation.data(), attestation.size(),
                                 b64_buf, sizeof b64_buf);
    if (buf_used < 0) {
      result["quote"] = "";
    } else {
      result["quote"] = string(b64_buf);
    }

    buf_used = ext::b64_ntop(mr_enclave_p, SGX_HASH_SIZE,
                             b64_buf, sizeof b64_buf);
    if (buf_used < 0) {
      result["mr_enclave"] = "";
    } else {
      result["mr_enclave"] = string(b64_buf);
    }
  } catch (tc::EcallException &e) {
    result["error"] = e.what();
  } catch (std::exception &e) {
    result["error"] = e.what();
  } catch (...) {
    result["error"] = "unknown exception";
  }

  return result;
}

Json::Value status_rpc_server::status() {
  Json::Value status;
  status["version"] = GIT_COMMIT_HASH;
  status["numberOfScannedBlocks"] = 0;
  status["numberOfResponse"] = 0;

  return status;
}

#include "request_parser.h"
#include "../Common/Constants.h"
#include "Enclave_u.h"
#include "debug.h"

Json::Value status_rpc_server::process(const std::string &data, int nonce, const std::string &txid) {
// TX_BUF_SIZE is defined in Constants.h
  uint8_t resp_buffer[TX_BUF_SIZE] = {0};
  size_t resp_data_len = 0;

  Json::Value ret;

  try {
    LOG4CXX_INFO(logger, "processing request tx " << txid);
    RequestParser request(data, txid);

    hexdump("request", request.getRawRequest().data(), request.getRawRequest().size());

    LL_INFO("parsed request: %s", request.toString().c_str());

    int ecall_ret;

    LL_INFO("nonce obtained %d", nonce);

    // TODO(FAN): change nonce to some long type
    auto st = handle_request(eid, &ecall_ret, nonce, request.getId(),
                             request.getType(), request.getData(),
                             request.getDataLen(), resp_buffer, &resp_data_len);

    if (st != SGX_SUCCESS || ecall_ret != TC_SUCCESS) {
      throw runtime_error("ecall failed");
    } else {
      LL_INFO("ecall succeeds");

      string resp_txn = bufferToHex(resp_buffer, resp_data_len, true);
      LL_DEBUG("response tx: %s", resp_txn.c_str());

      ret["error_code"] = 0;
      ret["response"] = resp_txn;

      return ret;
    }
  }
  catch (const exception &e) {
    LL_CRITICAL("exception: %s", e.what())
  }

  ret["error_code"] = 1;
  return ret;
}
