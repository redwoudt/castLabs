/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I parse content according to ISO Base Media File Standard
 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include "IsoBaseMediaFileParser.h"
#include "../utils/Logging.h"
#include "../ImageDecoder/ImageDecoder.h"

using std::runtime_error;

IsoBaseMediaFileParser::IsoBaseMediaFileParser(string& content): m_content(content){

}


void IsoBaseMediaFileParser::extractMdatBlock(const uint64_t& index, const char * path){
    uint64_t blockSize = parseBlock(index, "mdat");
    if (blockSize == 0){
        LOG(ERR, "\"mdat\" block is not present \n");
        throw runtime_error("\"mdat\" block is not present");
    }
    string mdatContent;
    retrieveBoxContent(index+BOX_HEADER_SIZE, blockSize-BOX_HEADER_SIZE, mdatContent);
    displayBlockData("mdat", mdatContent);

    ImageDecoder imageExtractor;
    imageExtractor.extractImages(string(path), mdatContent);
}

uint64_t IsoBaseMediaFileParser::retrieveBoxSize(const uint64_t& index) const{
    string boxSizeStr = m_content.substr(index, BOX_HEADER_LENGTH_SIZE);
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

void IsoBaseMediaFileParser::retrieveBoxType(const uint64_t& index, string & boxType) const {
    boxType = m_content.substr(index, BOX_HEADER_TYPE_SIZE);
    LOG(VERB, "Box type: " << boxType << "\n");
}

void IsoBaseMediaFileParser::retrieveBoxContent(const uint64_t& index, const uint64_t& size, string & content) const{
    content = m_content.substr(index, size);
    LOG(VERB, "Box Content: " << content << "\n");
}

void IsoBaseMediaFileParser::displayBlockData(const char * name, const string & content) const{
    LOG(INFO, "Content of " << name << " box is: " << content << "\n");
}

void IsoBaseMediaFileParser::test(void) {
    //TODO 
}