/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I parse content according to ISO Base Media File Standard
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H
#define MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H

#include <string>
#include <tuple>
#include <vector>
using std::string;
using std::tuple;
using std::vector;

typedef tuple<const char *, uint64_t> nameAndSize;
typedef vector<const char *> block_list;

class IsoBaseMediaFileParser {
public:
    IsoBaseMediaFileParser(string& );
    void extractAllBlocks();
    uint64_t extractMoofBlocks();
    void extractMdatBlock(const uint64_t& );
protected:
    uint64_t parseBlock(uint64_t , const char * );
    void parseSubBlocks(const char * , uint64_t , uint64_t );
    nameAndSize parseSubBlocks(uint64_t index, block_list allowed_names);
    uint64_t retrieveBoxSize(uint64_t index);
    string retrieveBoxType(uint64_t index);
    void displayBoxFound(const char * name, const uint64_t size) const;
private:
    string& m_content;
};


#endif //MDATEXTRACTOR_ISOBASEMEDIAFILEPARSER_H
