/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I define the common Media Parser Abstract Class with common implementation
 */

#ifndef MDATEXTRACTOR_ISOBASEMEDIAPARSER_BASE_H
#define MDATEXTRACTOR_ISOBASEMEDIAPARSER_BASE_H

#include <string>
#include <vector>
#include <tuple>
#include "../Interfaces/Interfaces.h"

using std::string;
using std::vector;
using std::tuple;

typedef tuple<const char *, uint64_t> nameAndSize; /**< typedef block name and size */
typedef vector<const char *> block_list; /**< typedef vector of blocks */

static const uint64_t BOX_HEADER_LENGTH_SIZE = 4; /**< byte length of box header */
static const uint64_t BOX_HEADER_TYPE_SIZE = 4; /**< byte length of box type/name */
static const uint64_t BOX_HEADER_SIZE = BOX_HEADER_LENGTH_SIZE+BOX_HEADER_TYPE_SIZE; /**< byte length of box header */

/** Abstract Class that defines the common functionality for all ISO Base Media parsers
 * irrespective of their transport type.
 */

class IsoBaseMediaParser_Base : public IsoBaseMediaParser {
public:
    void extractAllBlocks(const char *);
    uint64_t extractMoofBlocks();
protected:
    /**
     * Extract Specific Block Details (Block Size).
     * @param index starting byte range index of block
     * @param name block type/name
     * @return block size
     */
    uint64_t parseBlock(const uint64_t& index, const char * name);
    /**
     * Extract Specific Sub-block Details (Name and Block Size).
     * @param index starting byte range index of block
     * @param allowed_names list of valid sub-blocks
     * @return block type/name and block size
     */
    nameAndSize parseSubBlocks(const uint64_t& index, const block_list& allowed_names);
    /**
     * Extract all Sub-blocks.
     * @param name type/name of parent block
     * @param index starting byte range index of block
     * @param blockLength length of parent block
     */
    void parseSubBlocks(const char * name, uint64_t index, const uint64_t& blockLength);
    /**
     * Display/Log Box Name and Size.
     * @param name type/name of block
     * @param size size of block
     */
    void displayBoxFound(const char * name, const uint64_t& size) const;
    /**
     * Extract specific block's size.
     * @param index starting byte range index of block
     * @return block type/name and block size
     */
    virtual uint64_t retrieveBoxSize(const uint64_t& index) const = 0;
    /**
     * Extract specific block's type/name.
     * @param index starting byte range index of block
     * @param boxType returned block type/name
     */
    virtual void retrieveBoxType(const uint64_t& index, string & boxType) const = 0;
};


#endif //MDATEXTRACTOR_ISOBASEMEDIAPARSER_BASE_H
