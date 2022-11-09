#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <datasiever.h>
#include "myhdbextractorimpl.h"
#include "dbsettings.h"
#include <hdbextractor.h>
#include <configurationparser.h>
#include <xvariantprinter.h>
#include <result.h>
#include <map>

using namespace std;

void print_usage(const char *appnam) {
    printf("\033[1;31mUsage\033[0m \"%s configfile.dat domain/family/member/attribute \"2014-07-20 10:00:00\" \"2014-07-20 12:00:00\""
           "\n or \"%s configfile.dat --query \"SELECT ...\" \"\n",
           appnam, appnam);
}

void print_results(Result *res) {
    int r = 0;
    std::vector<std::string> cols = res->getColumnList();
    while(res && res->next() > 0)
    {
        ++r;
        Row *row = res->getCurrentRow();
        for(int i = 0; row != NULL && i < row->getFieldCount(); i++) {
            printf("%d. %s\t\033[1;32m%s\033[0m\n", r+1, cols[i].c_str(), row->getField(i));
        }
    }
}

int main(int argc, char **argv)
{
    if(argc == 4) {
        if(strcmp(argv[2], "--query") == 0 || strcmp(argv[3], "-q") == 0) {
            DbSettings *qc = new DbSettings();
            qc->loadFromFile(argv[1]);
            // configuration file contains dbschema: use it. Default: hdb++
            MyHdbExtractorImpl::Schema schema = qc->get("dbschema") == "hdb" ?
                        MyHdbExtractorImpl::Hdb : MyHdbExtractorImpl::Hdbpp;

            MyHdbExtractorImpl *hdbxi = new MyHdbExtractorImpl(qc->get("dbuser").c_str(),
                                                               qc->get("dbpass").c_str(),
                                                               qc->get("dbhost").c_str(),
                                                               qc->get("dbname").c_str(),
                                                               schema);

            hdbxi->getHdbExtractor()->setHdbXSettings(qc);
            double elapsed;
            Result* result = NULL;
            bool res = hdbxi->query(argv[3], result, &elapsed);
            if(!res) {
                printf("\033[1;31merror\033[0m: query \"%s\" failed: \"%s\"\n\n", argv[3],
                        hdbxi->getHdbExtractor()->getErrorMessage());
            }
            else
                print_results(result);
        }
        else {
            print_usage(argv[0]);
        }
    }
    else if(argc < 5)
    {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        const char* start_date = argv[argc - 2];
        const char* stop_date = argv[argc - 1];

        std::vector<std::string> sources;
        for(int i = 2; i < argc - 2; i++)
            sources.push_back(std::string(argv[i]));

        DbSettings *qc = new DbSettings();
        qc->loadFromFile(argv[1]);

        MyHdbExtractorImpl *hdbxi = new MyHdbExtractorImpl(qc->get("dbuser").c_str(),
                                                           qc->get("dbpass").c_str(),
                                                           qc->get("dbhost").c_str(),
                                                           qc->get("dbname").c_str());

        hdbxi->getHdbExtractor()->setHdbXSettings(qc);
        hdbxi->getData(sources, start_date, stop_date);

        const std::vector<XVariant> & valuelist = hdbxi->getValuelistRef();

        DataSiever siever;
        siever.divide(valuelist);
        siever.fill();
        std::vector<std::string> srcs = siever.getSources();
        for(size_t i = 0; i < srcs.size(); i++)
        {
            std::vector<XVariant > values = siever.getData(srcs.at(i));
            XVariantPrinter().printValueList(values, 2);
        }


        printf("main.cpp: deleting DbSettings\n");
        delete qc;
        printf("main.cpp: deleting MyHdbExtractorImpl\n");
        delete hdbxi;
    }
    return 0;
}

