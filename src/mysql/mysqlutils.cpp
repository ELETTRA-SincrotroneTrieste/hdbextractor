#include "mysqlutils.h"
#include <string.h> // strcpy
#include <sys/time.h> // gettimeofday
#include "../db/connection.h"
#include "../db/row.h"
#include "../db/result.h"
#include "../mysql/mysqlconnection.h"
#include "../mysql/mysqlresult.h"
#include "../hdbxmacros.h"
#include "../dbschemaprivate.h" // for MAXERRORLEN

bool MySqlUtils::query(const char *query,
                       Connection *connection,
                       Result * &res,
                       char *errormsg,
                       double *elapsed)
{
    res = NULL;
    struct timeval tv1, tv2;
    char timestamp[32];
    strcpy(timestamp, ""); /* initialize an empty timestamp */
    if(elapsed)
        gettimeofday(&tv1, NULL);
    res = connection->query(query);
    if(!res) {
        snprintf(errormsg, MAXERRORLEN, "error in query \"%s\": \"%s\"",
                 query, connection->getError());
    }
    if(elapsed) {
        gettimeofday(&tv2, NULL);
        /* transform the elapsed time from a timeval struct to a double whose integer part
         * represents seconds and the decimal microseconds.
         */
        *elapsed = tv2.tv_sec + 1e-6 * tv2.tv_usec - (tv1.tv_sec + 1e-6 * tv1.tv_usec);
    }
    return res != NULL;
}
