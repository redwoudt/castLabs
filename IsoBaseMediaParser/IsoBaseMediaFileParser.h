/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I parse content according to ISO Base Media File Standard
 * access the file locally in a string.
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H
#define MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H

#include <string>
#include <tuple>
#include <vector>
#include "IsoBaseMediaParser_Base.h"

using std::string;
using std::tuple;
using std::vector;

typedef tuple<const char *, uint64_t> nameAndSize;
typedef vector<const char *> block_list;

class IsoBaseMediaFileParser : public IsoBaseMediaParser_Base{
public:
    IsoBaseMediaFileParser(string& );
    void extractMdatBlock(const uint64_t& );
protected:
    uint64_t retrieveBoxSize(const uint64_t&) const;
    void retrieveBoxType(const uint64_t&, string &) const;
private:
    void retrieveBoxContent(const uint64_t&, const uint64_t&, string &) const;
    void displayBlockData(const char *, const string &) const;
    string& m_content;
};


#endif //MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H
