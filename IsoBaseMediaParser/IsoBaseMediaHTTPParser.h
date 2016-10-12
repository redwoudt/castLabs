/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I define the common Media Parser Functions specific HTTP interface
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAHTTPPARSER_H
#define MDATEXTRACTOR_ISOBASEMEDIAHTTPPARSER_H

#include "IsoBaseMediaParser_Base.h"
#include "../HTTP/HTTPSimple.h"

class IsoBaseMediaHTTPParser : public IsoBaseMediaParser_Base{
public:
    IsoBaseMediaHTTPParser(HTTPSimple& );
    void extractMdatBlock(const uint64_t& );
protected:
    uint64_t retrieveBoxSize(const uint64_t&) const;
    void retrieveBoxType(const uint64_t&, string &) const;
private:
    void constructRangeString(const uint64_t&, const uint64_t&, string &) const;
    void retrievePartialBoxContent(const uint64_t&, const uint64_t&, string &) const;
    void displayHeadingOfBlockData(const char * name) const;
    void displayPartialBlockData(const string & content) const;
    HTTPSimple& m_httpInterface;
};

#endif //MDATEXTRACTOR_ISOBASEMEDIAHTTPPARSER_H
