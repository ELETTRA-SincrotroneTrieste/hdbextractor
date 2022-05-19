#ifndef MYSQLUTILS_H
#define MYSQLUTILS_H

#include <map>
#include <string>

class Connection;
class Result;

class MySqlUtils
{
public:    
    bool query(const char *query, Connection *connection,  Result *&res,
               char *errormsg, double *elapsed = NULL);
};

#endif // MYSQLUTILS_H
