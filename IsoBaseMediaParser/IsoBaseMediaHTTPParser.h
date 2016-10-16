/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I define the common Media Parser Functions specific HTTP interface
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAHTTPPARSER_H
#define MDATEXTRACTOR_ISOBASEMEDIAHTTPPARSER_H

#include "IsoBaseMediaParser_Base.h"
#include "../HTTP/HTTPSimple.h"

/** Iso Base Media File parser with HTTP transport
 */

class IsoBaseMediaHTTPParser : public IsoBaseMediaParser_Base{
public:
    /**
     * A constructor.
     *  @param httpInterface HTTP transport interface
     */
    IsoBaseMediaHTTPParser(HTTPSimple& httpInterface);
    void extractMdatBlock(const uint64_t&, const char *);
    /**
     * Test class
     */
    void test(void);
protected:
    uint64_t retrieveBoxSize(const uint64_t&) const;
    void retrieveBoxType(const uint64_t&, string &) const;
private:
    /**
     * Construct the range string required for Byte range requests.
     *  @param start byte start index
     *  @param length byte length
     *  @param range returned byte range string
     */
    void constructRangeString(const uint64_t& start, const uint64_t& length, string & range) const;
    /**
     * Retrieve byte range specified subset of block content.
     *  @param start byte start index
     *  @param end byte end index
     *  @param content returned content as string
     */
    void retrievePartialBoxContent(const uint64_t& start, const uint64_t& end, string & content) const;
    /**
     * Display Heading for Block Data.
     *  @param name block name/type
     */
    void displayHeadingOfBlockData(const char * name) const;
    /**
     * Display Block Data.
     *  @param content block data
     */
    void displayPartialBlockData(const string & content) const;
    HTTPSimple& m_httpInterface; /**< HTTP interface */
};

#endif //MDATEXTRACTOR_ISOBASEMEDIAHTTPPARSER_H
