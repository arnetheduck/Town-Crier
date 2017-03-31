#include <stdio.h>
#include <stdlib.h>
#include <Debug.h>
#include "tls_client.h"
#include "scrapers.h"
#include "Log.h"

int bloomberg_self_test() {
  // This scraper is deprecated!
  return 0;
  double r = 0.0;

  if (bloomberg_current(NULL, &r) != -1 || bloomberg_current("GOOG", NULL) != -1 || \
        bloomberg_current(NULL, NULL) != -1) {
    return -1;
  }

  if (bloomberg_current("GOOG", &r) == -1) {
    return -1;
  }
  LL_CRITICAL("[Bloomberg]GOOG returns: %f\n", r);

  if (r == 0 || bloomberg_current("AAPL", &r) == -1) {
    return -1;
  }
  LL_CRITICAL("[Bloomberg]Apple returns: %f\n", r);

  if (r == 0 || bloomberg_current("ORCL", &r) == -1) {
    return -1;
  }
  LL_CRITICAL("[Bloomberg]oracle returns: %f\n", r);

  if (r == 0 || bloomberg_current("YHOO", &r) == -1) {
    return -1;
  }
  LL_CRITICAL("[Bloomberg]Yahoo returns: %f\n", r);

  //Null check
  int ret = bloomberg_current("vdbsd", &r);
  if (ret != -1) {
    return -1;
  }
  //stress test
  for (int i = 0; i < 10000; i++) {
    if (bloomberg_current("GOOG", &r) == -1) {
      return -1;
    }
  }
  return 0;
}