#include <stdlib.h> /* for NULL */
#include <stdio.h>
#include <string.h>
#include "mysql/mysqlconnection.h"
#include "mysqlresult.h"
#include "mysqlrow.h"
#include "xvariant.h"
#include "hdbxmacros.h"

#define MAXQUERYLEN 256

MySqlConnection::MySqlConnection()
{
    mConnection = NULL;
    mAffectedRows = 0;
}

MySqlConnection:: ~MySqlConnection()
{
    close();
}

void MySqlConnection::close()
{
    if(mConnection != NULL)
    {
        mysql_close(mConnection);
        mConnection = NULL;
    }
}

bool MySqlConnection::connect(const char* host,
                              const char *db,
                              const char* user,
                              const char* passwd,
                              unsigned short port)
{
    mysql_init(&mMysql);
    mConnection = mysql_real_connect(&mMysql, host, user, passwd, db, port, 0, 0);
    return (mConnection != NULL);
}

int MySqlConnection::getAffectedRows() const
{
    return mAffectedRows;
}

int MySqlConnection::lastInsertId() {
    return mysql_insert_id(&mMysql);
}

const char* MySqlConnection::getError() {
    // mysql_error returns a previous error or empty string
    if(isConnected())
        return mysql_error(mConnection);
    else
        return mysql_error(&mMysql);
}

bool MySqlConnection::isConnected() const {
    return mConnection != NULL;
}

Result *MySqlConnection::query(const char *q) {
    int res;
    MYSQL_RES* result;
    if(mConnection == NULL) {
        perr("MySqlConnection::query: database not open");
    }
    else {
        res = mysql_query(mConnection, q);
        if(res == 0)  {
            result = mysql_store_result(mConnection);
            if(!result && mysql_errno(&mMysql) == 0) { // f.e. an INSERT
                /* store the affected rows */
                mAffectedRows = mysql_affected_rows(mConnection);
            }
            return new MySqlResult(result);
        }
    }
    return nullptr;
}

