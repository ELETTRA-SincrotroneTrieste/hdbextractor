#ifndef MYHDBEXTRACTORIMPL_H
#define MYHDBEXTRACTORIMPL_H

#include <hdbextractorlistener.h>

class Hdbextractor;
class Result;

#include <vector>
#include <xvariant.h>
#include <map>

/** \brief an <em>example</em> of an implementation of the HdbExtractorListener
 *
 */
class MyHdbExtractorImpl : public HdbExtractorListener
{
public:
    MyHdbExtractorImpl(const char *dbuser, const char *dbpass,
                       const char *dbhost, const char *dbnam);

    virtual ~MyHdbExtractorImpl();

    void getData(std::vector<std::string> sources, const char* start_date, const char *stop_date);

    bool query(const char* q, Result* &result, double *elapsed);

    virtual void onSourceProgressUpdate(const char *name, double percent);

    virtual void onExtractionFinished(int totalRows, double elapsed);

    virtual void onSourceExtractionFinished(const char* name, int totalRows, double elapsed);

    Hdbextractor* getHdbExtractor() const { return mExtractor; }

    void extractData();

    const std::vector<XVariant> &getValuelistRef() const;

private:
    Hdbextractor *mExtractor;

    std::vector<XVariant> d_valuelist;
};

#endif // MYHDBEXTRACTORIMPL_H
