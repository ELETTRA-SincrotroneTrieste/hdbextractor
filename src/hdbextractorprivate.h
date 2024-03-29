#ifndef HDBEXTRACTORPRIVATE_H
#define HDBEXTRACTORPRIVATE_H

#include "hdbextractor.h" /* for db and schema type enum values */

#define MAXERRORLEN 512

class Connection;
class ConfigurableDbSchema;
class HdbExtractorListener;
class DbSettings;

class HdbExtractorPrivate
{
public:
    Hdbextractor::DbType dbType;

    Connection * connection;

    ConfigurableDbSchema *dbschema;

    HdbExtractorListener* hdbXListenerI;

    DbSettings *dbsettings;

    int updateEveryRows;

    char errorMessage[MAXERRORLEN];
};

#endif // HDBEXTRACTORPRIVATE_H
