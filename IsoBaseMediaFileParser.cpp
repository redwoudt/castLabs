/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I parse content according to ISO Base Media File Standard
 */

#include <map>
#include <stack>
#include <stdexcept>
#include "IsoBaseMediaFileParser.h"
#include "Logging.h"

using std::map;
using std::stack;
using std::get;
using std::runtime_error;

typedef tuple<const char *, uint64_t, uint64_t > blockMetaData;

static const uint64_t BOX_HEADER_LENGTH_SIZE = 4;
static const uint64_t BOX_HEADER_TYPE_SIZE = 4;
static const uint64_t BOX_HEADER_SIZE = BOX_HEADER_LENGTH_SIZE+BOX_HEADER_TYPE_SIZE;
static map<const char *, block_list> ALLOWED_SUB_BLOCKS = { \
                                                          {"moof", {"mfhd", "traf"}}, \
                                                          {"traf", {"tfhd", "trun", "uuid"}} \
                                                          };

IsoBaseMediaFileParser::IsoBaseMediaFileParser(string& content): m_content(content){

}

void IsoBaseMediaFileParser::extractAllBlocks(){
    LOG(VERB, "Content to extract blocks from: \n" << this->m_content);
    try{
        uint64_t blockSize = this->extractMoofBlocks();
        this->extractMdatBlock(blockSize);
    }
    catch (runtime_error &e){
        LOG(ERR, "Caught runtime expection: " << e.what() << "\n");
    }
}

uint64_t IsoBaseMediaFileParser::extractMoofBlocks(){
    // parse "moof" block
    uint64_t blockSize = this->parseBlock(0, "moof");
    if (blockSize == 0){
        LOG(ERR, "\"moof\" block is not present \n");
        throw runtime_error("\"moof\" block is not present");
    }
    // parse "moof" subblocks
    parseSubBlocks("moof", BOX_HEADER_SIZE, blockSize);
    return blockSize;
}

void IsoBaseMediaFileParser::extractMdatBlock(const uint64_t& index){
    uint64_t blockSize = this->parseBlock(index, "mdat");
    if (blockSize == 0){
        LOG(ERR, "\"mdat\" block is not present \n");
        throw runtime_error("\"mdat\" block is not present");
    }
}

uint64_t IsoBaseMediaFileParser::parseBlock(uint64_t index, const char * name){
    LOG(VERB, "parse block \"" << name << "\"\n");
    uint64_t blockSize = this->retrieveBoxSize(index);
    string blockType = this->retrieveBoxType(index+BOX_HEADER_LENGTH_SIZE);
    if (blockType.compare(name) != 0){
        LOG(DEBUG, "Received \"" << blockType << "\", excepted \"" << name << "\"\n");
        blockSize = 0;
    }
    else{
        this->displayBoxFound(name, blockSize);
    }
    return blockSize;
}

nameAndSize IsoBaseMediaFileParser::parseSubBlocks(uint64_t index, block_list allowed_names){
    for (const char * name : allowed_names){
        uint64_t blockSize = parseBlock(index, name);
        if (blockSize != 0){
            return {name, blockSize};
        }
    }
    return {nullptr, 0};
}

void IsoBaseMediaFileParser::parseSubBlocks(const char * name, uint64_t index, uint64_t blockLength){
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

uint64_t IsoBaseMediaFileParser::retrieveBoxSize(uint64_t index){
    string boxSizeStr = this->m_content.substr(index, BOX_HEADER_LENGTH_SIZE);
    LOG(VERB, "Box Size String: " << boxSizeStr << "\n");
    // extract length
    uint64_t boxSize = 0;
    for (int i = 0; i < boxSizeStr.length(); ++i) {
        LOG(VERB, "Temp box size: " << ((uint16_t) boxSizeStr[i] & 0xff) << "\n");
        boxSize = (boxSize << 8) | ((uint16_t) boxSizeStr[i] & 0xff);
    }
    LOG(VERB, "Box size: " << boxSize << "\n");
    return boxSize;
}

string IsoBaseMediaFileParser::retrieveBoxType(uint64_t index){
    string boxType = this->m_content.substr(index, BOX_HEADER_TYPE_SIZE);
    LOG(VERB, "Box type: " << boxType << "\n");
    return boxType;
}

void IsoBaseMediaFileParser::displayBoxFound(const char * name, const uint64_t size) const{
    LOG(INFO, "Found box of type " << name << " and size " << size << "\n");
}