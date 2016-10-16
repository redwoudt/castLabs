/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I parse content according to ISO Base Media File Standard
 * access the file locally in a string.
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H
#define MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H

#include <string>
#include "IsoBaseMediaParser_Base.h"

using std::string;

/** Iso Base Media File parser with local string
 */

class IsoBaseMediaFileParser : public IsoBaseMediaParser_Base{
public:
    /**
     * A constructor.
     *  @content reference to string containing content to parse
     */
    IsoBaseMediaFileParser(string& content);
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
     * Display Block Data.
     *  @param index block byte start index
     *  @param size block byte size
     *  @param content returned block content
     */
    void retrieveBoxContent(const uint64_t& index, const uint64_t& size, string & content) const;
    /**
     * Display Block Data.
     *  @param name block name/type
     *  @param content block content
     */
    void displayBlockData(const char * name, const string & content)  const;
    string& m_content; /**< content */
};


#endif //MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H
