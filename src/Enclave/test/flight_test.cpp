//
// Copyright (c) 2016-2017 by Cornell University.  All Rights Reserved.
//
// Permission to use the "TownCrier" software ("TownCrier"), officially docketed at
// the Center for Technology Licensing at Cornell University as D-7364, developed
// through research conducted at Cornell University, and its associated copyrights
// solely for educational, research and non-profit purposes without fee is hereby
// granted, provided that the user agrees as follows:
//
// The permission granted herein is solely for the purpose of compiling the
// TowCrier source code. No other rights to use TownCrier and its associated
// copyrights for any other purpose are granted herein, whether commercial or
// non-commercial.
//
// Those desiring to incorporate TownCrier software into commercial products or use
// TownCrier and its associated copyrights for commercial purposes must contact the
// Center for Technology Licensing at Cornell University at 395 Pine Tree Road,
// Suite 310, Ithaca, NY 14850; email: ctl-connect@cornell.edu; Tel: 607-254-4698;
// FAX: 607-254-5454 for a commercial license.
//
// IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
// ARISING OUT OF THE USE OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS, EVEN IF
// CORNELL UNIVERSITY MAY HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL UNIVERSITY HAS NO
// OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
// MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO REPRESENTATIONS AND EXTENDS NO
// WARRANTIES OF ANY KIND, EITHER IMPLIED OR EXPRESS, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
// PURPOSE, OR THAT THE USE OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT
// INFRINGE ANY PATENT, TRADEMARK OR OTHER RIGHTS.
//
// TownCrier was developed with funding in part by the National Science Foundation
// (NSF grants CNS-1314857, CNS-1330599, CNS-1453634, CNS-1518765, CNS-1514261), a
// Packard Fellowship, a Sloan Fellowship, Google Faculty Research Awards, and a
// VMWare Research Award.
//

#include <stdio.h>
#include <stdlib.h>
#include <Debug.h>
#include "tls_client.h"
#include "../scrapers/flight.h"
#include "Log.h"

//Sample Delayed flight,
//filed_departureTime: 1490703000
//flight GGN7241
const char* sampleDelayedFlight = "{\"FlightInfoExResult\":{\"next_offset\":-1,\"flights\":[{\"faFlightID\":\"GGN7241-1490678754-airline-0106\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:40:00\",\"filed_time\":1490678754,\"filed_departuretime\":1490875800,\"filed_airspeed_kts\":187,\"filed_airspeed_mach\":\"\",\"filed_altitude\":0,\"route\":\"\",\"actualdeparturetime\":0,\"estimatedarrivaltime\":1490878800,\"actualarrivaltime\":0,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1490592346-airline-0276\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:34:00\",\"filed_time\":1490592346,\"filed_departuretime\":1490789400,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":0,\"estimatedarrivaltime\":1490792062,\"actualarrivaltime\":0,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1490505945-airline-0089\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:34:00\",\"filed_time\":1490505945,\"filed_departuretime\":1490703000,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490709120,\"estimatedarrivaltime\":1490711253,\"actualarrivaltime\":0,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1490423137-airline-0104\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:44:00\",\"filed_time\":1490423137,\"filed_departuretime\":1490616600,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490618400,\"estimatedarrivaltime\":1490620980,\"actualarrivaltime\":1490621040,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1490336752-airline-0406\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:34:00\",\"filed_time\":1490336752,\"filed_departuretime\":1490530200,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490531760,\"estimatedarrivaltime\":1490533920,\"actualarrivaltime\":1490533980,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1490163954-airline-0024\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:35:00\",\"filed_time\":1490163954,\"filed_departuretime\":1490357400,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490358420,\"estimatedarrivaltime\":1490361000,\"actualarrivaltime\":1490361000,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1490077540-airline-0187\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:33:00\",\"filed_time\":1490077540,\"filed_departuretime\":1490271000,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490273880,\"estimatedarrivaltime\":1490276040,\"actualarrivaltime\":1490276160,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1489991141-airline-0106\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:33:00\",\"filed_time\":1489991141,\"filed_departuretime\":1490184600,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490186280,\"estimatedarrivaltime\":1490188860,\"actualarrivaltime\":1490188860,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1489925400-schedule-0000\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:35:00\",\"filed_time\":1489925400,\"filed_departuretime\":1490098200,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490100240,\"estimatedarrivaltime\":1490102700,\"actualarrivaltime\":1490102760,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1489818337-airline-0194\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:44:00\",\"filed_time\":1489818337,\"filed_departuretime\":1490011800,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1490013360,\"estimatedarrivaltime\":1490015160,\"actualarrivaltime\":1490015700,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1489731944-airline-0060\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:39:00\",\"filed_time\":1489731944,\"filed_departuretime\":1489925400,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1489926360,\"estimatedarrivaltime\":1489928520,\"actualarrivaltime\":1489928460,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"},{\"faFlightID\":\"GGN7241-1489562978-airline-0029\",\"ident\":\"GGN7241\",\"aircrafttype\":\"B190\",\"filed_ete\":\"00:40:00\",\"filed_time\":1489562978,\"filed_departuretime\":1489752600,\"filed_airspeed_kts\":270,\"filed_airspeed_mach\":\"\",\"filed_altitude\":120,\"route\":\"TULEK1 IKMOK\",\"actualdeparturetime\":1489753680,\"estimatedarrivaltime\":1489755900,\"actualarrivaltime\":1489755900,\"diverted\":\"\",\"origin\":\"CYYZ\",\"destination\":\"CYZR\",\"originName\":\"Toronto Pearson Int'l\",\"originCity\":\"Toronto, Ontario\",\"destinationName\":\"Sarnia (Chris Hadfield)\",\"destinationCity\":\"Sarnia, Ontario\"}]}}";

//Sample flight that departed on time
const char* sampleDepartedFlight = "{\"FlightInfoExResult\":{\"next_offset\":-1,\"flights\":[{\"faFlightID\":\"WJA1884-1490505956-airline-0021\",\"ident\":\"WJA1884\",\"aircrafttype\":\"B763\",\"filed_ete\":\"07:09:00\",\"filed_time\":1490505956,\"filed_departuretime\":1490710500,\"filed_airspeed_kts\":459,\"filed_airspeed_mach\":\"\",\"filed_altitude\":340,\"route\":\"TAVPO Q860 NADPI YDC FOLDY HQM C1418 SEDAR 4200N/13000W 3700N/13500W AXELE R463 APACK\",\"actualdeparturetime\":1490711340,\"estimatedarrivaltime\":1490736056,\"actualarrivaltime\":0,\"diverted\":\"\",\"origin\":\"CYEG\",\"destination\":\"PHOG\",\"originName\":\"Edmonton Int'l\",\"originCity\":\"Edmonton Capital Region, Alberta\",\"destinationName\":\"Kahului\",\"destinationCity\":\"Kahului, HI\"},{\"faFlightID\":\"WJA1884-1490336762-airline-0506\",\"ident\":\"WJA1884\",\"aircrafttype\":\"B763\",\"filed_ete\":\"06:55:00\",\"filed_time\":1490336762,\"filed_departuretime\":1490537700,\"filed_airspeed_kts\":459,\"filed_airspeed_mach\":\"\",\"filed_altitude\":340,\"route\":\"CHIPE 5130N/12000W QQ DOLFF KANUA 4300N/13500W ZAGER 3400N/14500W HALLI A332 AUNTI R463 APACK\",\"actualdeparturetime\":1490538480,\"estimatedarrivaltime\":1490562720,\"actualarrivaltime\":1490562714,\"diverted\":\"\",\"origin\":\"CYEG\",\"destination\":\"PHOG\",\"originName\":\"Edmonton Int'l\",\"originCity\":\"Edmonton Capital Region, Alberta\",\"destinationName\":\"Kahului\",\"destinationCity\":\"Kahului, HI\"},{\"faFlightID\":\"WJA1884-1489924089-airline-0232\",\"ident\":\"WJA1884\",\"aircrafttype\":\"B763\",\"filed_ete\":\"06:30:00\",\"filed_time\":1489924089,\"filed_departuretime\":1490105700,\"filed_airspeed_kts\":459,\"filed_airspeed_mach\":\"\",\"filed_altitude\":340,\"route\":\"CHIPE 5130N/12000W QQ DOLFF 4600N/13500W 4300N/14000W 3800N/14500W 3200N/15000W 2700N/15500W ZOULU A331 ZIGIE\",\"actualdeparturetime\":1490109060,\"estimatedarrivaltime\":1490133540,\"actualarrivaltime\":1490133626,\"diverted\":\"\",\"origin\":\"CYEG\",\"destination\":\"PHOG\",\"originName\":\"Edmonton Int'l\",\"originCity\":\"Edmonton Capital Region, Alberta\",\"destinationName\":\"Kahului\",\"destinationCity\":\"Kahului, HI\"},{\"faFlightID\":\"WJA1884-1489731955-airline-0637\",\"ident\":\"WJA1884\",\"aircrafttype\":\"B763\",\"filed_ete\":\"06:57:00\",\"filed_time\":1489731955,\"filed_departuretime\":1489932900,\"filed_airspeed_kts\":468,\"filed_airspeed_mach\":\"\",\"filed_altitude\":340,\"route\":\"CHIPE 5130N/12000W QQ DOLFF KANUA 4300N/13500W ZAGER A331 ZEMOM AUNTI R463 APACK\",\"actualdeparturetime\":1489934220,\"estimatedarrivaltime\":1489959420,\"actualarrivaltime\":1489959427,\"diverted\":\"\",\"origin\":\"CYEG\",\"destination\":\"PHOG\",\"originName\":\"Edmonton Int'l\",\"originCity\":\"Edmonton Capital Region, Alberta\",\"destinationName\":\"Kahului\",\"destinationCity\":\"Kahului, HI\"}]}}";

//Sample cancelled flight
const char* sampleCancelledFlight = "{\"FlightInfoExResult\":{\"next_offset\":-1,\"flights\":[{\"faFlightID\":\"VOZ621-1490678765-airline-0042\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"01:15:00\",\"filed_time\":1490678765,\"filed_departuretime\":1490867700,\"filed_airspeed_kts\":345,\"filed_airspeed_mach\":\"\",\"filed_altitude\":0,\"route\":\"\",\"actualdeparturetime\":0,\"estimatedarrivaltime\":1490872800,\"actualarrivaltime\":0,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1490592355-airline-0052\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"01:15:00\",\"filed_time\":1490592355,\"filed_departuretime\":1490781300,\"filed_airspeed_kts\":345,\"filed_airspeed_mach\":\"\",\"filed_altitude\":0,\"route\":\"\",\"actualdeparturetime\":-1,\"estimatedarrivaltime\":-1,\"actualarrivaltime\":-1,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1490505955-airline-0007\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"01:15:00\",\"filed_time\":1490505955,\"filed_departuretime\":1490694900,\"filed_airspeed_kts\":345,\"filed_airspeed_mach\":\"\",\"filed_altitude\":0,\"route\":\"\",\"actualdeparturetime\":-1,\"estimatedarrivaltime\":-1,\"actualarrivaltime\":-1,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1490336761-airline-0095\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"01:15:00\",\"filed_time\":1490336761,\"filed_departuretime\":1490522100,\"filed_airspeed_kts\":345,\"filed_airspeed_mach\":\"\",\"filed_altitude\":0,\"route\":\"\",\"actualdeparturetime\":-1,\"estimatedarrivaltime\":-1,\"actualarrivaltime\":-1,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1490163964-airline-0076\",\"ident\":\"VOZ621\",\"aircrafttype\":\"E190\",\"filed_ete\":\"00:59:00\",\"filed_time\":1490163964,\"filed_departuretime\":1490350200,\"filed_airspeed_kts\":450,\"filed_airspeed_mach\":\"\",\"filed_altitude\":380,\"route\":\"DCT CORAL Q26 CAPRI UQ493 PROBO V134\",\"actualdeparturetime\":1490353140,\"estimatedarrivaltime\":1490357340,\"actualarrivaltime\":1490357335,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1490077550-airline-0003\",\"ident\":\"VOZ621\",\"aircrafttype\":\"E190\",\"filed_ete\":\"01:15:00\",\"filed_time\":1490077550,\"filed_departuretime\":1490263800,\"filed_airspeed_kts\":450,\"filed_airspeed_mach\":\"\",\"filed_altitude\":380,\"route\":\"DCT CORAL Q26 CAPRI UQ493 PROBO V134\",\"actualdeparturetime\":1490264700,\"estimatedarrivaltime\":1490269500,\"actualarrivaltime\":1490269490,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1489918200-schedule-0000\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"00:57:00\",\"filed_time\":1489918200,\"filed_departuretime\":1490091000,\"filed_airspeed_kts\":450,\"filed_airspeed_mach\":\"\",\"filed_altitude\":380,\"route\":\"DCT CORAL Q26 CAPRI UQ493 PROBO/N0390F240 V134\",\"actualdeparturetime\":1490091840,\"estimatedarrivaltime\":1490096220,\"actualarrivaltime\":1490096193,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1489731954-airline-0028\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"01:00:00\",\"filed_time\":1489731954,\"filed_departuretime\":1489918200,\"filed_airspeed_kts\":460,\"filed_airspeed_mach\":\"\",\"filed_altitude\":380,\"route\":\"DCT CORAL Q26 CAPRI UQ493 PROBO/N0400F240 V134\",\"actualdeparturetime\":1489919700,\"estimatedarrivaltime\":1489924260,\"actualarrivaltime\":1489924274,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"},{\"faFlightID\":\"VOZ621-1489559157-airline-0115\",\"ident\":\"VOZ621\",\"aircrafttype\":\"B738\",\"filed_ete\":\"01:00:00\",\"filed_time\":1489559157,\"filed_departuretime\":1489745400,\"filed_airspeed_kts\":460,\"filed_airspeed_mach\":\"\",\"filed_altitude\":380,\"route\":\"DCT CORAL Q26 CAPRI UQ493 PROBO V134\",\"actualdeparturetime\":1489748940,\"estimatedarrivaltime\":1489753440,\"actualarrivaltime\":1489753454,\"diverted\":\"\",\"origin\":\"YBBN\",\"destination\":\"YBMK\",\"originName\":\"Brisbane\",\"originCity\":\"Brisbane, Queensland\",\"destinationName\":\"Mackay\",\"destinationCity\":\"Mackay, Queensland\"}]}}";


/* Test updated on 2/21/17 */
int flight_self_test(){

  	//LL_NOTICE(\"USAGE: get_flight_delay(YYYYMMDD, HHmm, flight#, return_variable)\");
    //LL_NOTICE(\"\tdate/time in Zulu/UTC, flight in ICAO\");
    int rc, delay, status;
    
    /* Test1: Test a flight that is delayed */
    FlightScraper testScraper;
    flight_error ret = testScraper.parse_response(sampleDelayedFlight, &delay, 1490703000);
    switch(ret){
        case DELAYED:
            LL_INFO("GGN7241 delayed as desired");
            break; 
        default:
            LL_INFO("GGN7241 Error, returned %i",ret);
            return -1;
    }
    /* Test a flight that departed on time */
    ret = testScraper.parse_response(sampleDepartedFlight, &delay, 1490710500);
    switch(ret){
        case DEPARTED:
            LL_INFO("WJA1884 departed on time as desired");
            break;
        default:
            LL_INFO("WJA1884 error, returned %i", ret);
            return -1;       
    }

    /* Test a flight that was cancelled */
    ret = testScraper.parse_response(sampleCancelledFlight, &delay, 1490781300);
    switch(ret){
        case CANCELLED:
            LL_INFO("VOZ621 cancelled as desired");
            break;
        default:
            LL_INFO("VOZ621 error, returned %i", ret);
            return -1;
    }
    return 0;
}
//1477276620,
//filed_departuretime\":1477276620

