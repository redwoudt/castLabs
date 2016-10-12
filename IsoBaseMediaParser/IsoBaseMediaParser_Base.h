/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I define the common Media Parser Abstract Class with common implementation
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAPARSER_BASE_H
#define MDATEXTRACTOR_ISOBASEMEDIAPARSER_BASE_H

#include <string>
#include <tuple>
#include <vector>
#include "../Interfaces.h"

using std::string;
using std::tuple;
using std::vector;

typedef tuple<const char *, uint64_t> nameAndSize;
typedef vector<const char *> block_list;

static const uint64_t BOX_HEADER_LENGTH_SIZE = 4;
static const uint64_t BOX_HEADER_TYPE_SIZE = 4;
static const uint64_t BOX_HEADER_SIZE = BOX_HEADER_LENGTH_SIZE+BOX_HEADER_TYPE_SIZE;

class IsoBaseMediaParser_Base : public IsoBaseMediaParser {
public:
    void extractAllBlocks();
    uint64_t extractMoofBlocks();
protected:
    uint64_t parseBlock(const uint64_t&, const char *);
    nameAndSize parseSubBlocks(const uint64_t&, const block_list&);
    void parseSubBlocks(const char *, uint64_t, const uint64_t&);
    void displayBoxFound(const char *, const uint64_t&) const;
    virtual uint64_t retrieveBoxSize(const uint64_t&) const = 0;
    virtual void retrieveBoxType(const uint64_t&, string &) const = 0;
};


#endif //MDATEXTRACTOR_ISOBASEMEDIAPARSER_BASE_H
