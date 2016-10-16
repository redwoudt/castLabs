/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I define the common Media Parser Functions
 */

#include <map>
#include <stack>
#include <stdexcept>
#include "IsoBaseMediaParser_Base.h"
#include "../utils/Logging.h"

using std::map;
using std::stack;
using std::get;
using std::runtime_error;

typedef tuple<const char *, uint64_t, uint64_t > blockMetaData;

static map<const char *, block_list> ALLOWED_SUB_BLOCKS = { \
                                                          {"moof", {"mfhd", "traf"}}, \
                                                          {"traf", {"tfhd", "trun", "uuid"}} \
                                                          };

void IsoBaseMediaParser_Base::extractAllBlocks(const char * path){
    try{
        uint64_t blockSize = extractMoofBlocks();
        extractMdatBlock(blockSize, path);
    }
    catch (runtime_error &e){
        LOG(ERR, "Caught runtime expection: " << e.what() << "\n");
    }
}

uint64_t IsoBaseMediaParser_Base::extractMoofBlocks(){
    // parse "moof" block
    uint64_t blockSize = parseBlock(0, "moof");
    if (blockSize == 0){
        LOG(ERR, "\"moof\" block is not present \n");
        throw runtime_error("\"moof\" block is not present");
    }
    // parse "moof" subblocks
    parseSubBlocks("moof", BOX_HEADER_SIZE, blockSize);
    return blockSize;
}

uint64_t IsoBaseMediaParser_Base::parseBlock(const uint64_t& index, const char * name){
    LOG(VERB, "parse block \"" << name << "\"\n");
    uint64_t blockSize = retrieveBoxSize(index);
    string blockType;
    retrieveBoxType(index+BOX_HEADER_LENGTH_SIZE, blockType);
    if (blockType.compare(name) != 0){
        LOG(DEBUG, "Received \"" << blockType << "\", expected \"" << name << "\"\n");
        blockSize = 0;
    }
    else{
        displayBoxFound(name, blockSize);
    }
    return blockSize;
}

nameAndSize IsoBaseMediaParser_Base::parseSubBlocks(const uint64_t& index, const block_list& allowed_names){
    for (const char * name : allowed_names){
        uint64_t blockSize = parseBlock(index, name);
        if (blockSize != 0){
            return {name, blockSize};
        }
    }
    return {nullptr, 0};
}

void IsoBaseMediaParser_Base::parseSubBlocks(const char * name, uint64_t index, const uint64_t& blockLength){
    stack<blockMetaData> subBlocks;
    LOG(DEBUG, "Block name: " << name << ", " << blockLength << "\n");
    while (index < blockLength){
        auto blockInfo = parseSubBlocks(index, ALLOWED_SUB_BLOCKS[name]);
        if (get<1>(blockInfo) == 0){
            LOG(DEBUG, "Block \"" << name << "\" has no more subblocks" << "\n");
            break;
        }
        subBlocks.push({get<0>(blockInfo), index+BOX_HEADER_SIZE, index+get<1>(blockInfo)});
        index += get<1>(blockInfo);
    }

    while (!subBlocks.empty()){
        auto subBlockToProcess = subBlocks.top(); subBlocks.pop();
        parseSubBlocks(get<0>(subBlockToProcess), get<1>(subBlockToProcess), get<2>(subBlockToProcess));
    }
}

void IsoBaseMediaParser_Base::displayBoxFound(const char * name, const uint64_t& size) const{
    LOG(INFO, "Found box of type " << name << " and size " << size << "\n");
}

