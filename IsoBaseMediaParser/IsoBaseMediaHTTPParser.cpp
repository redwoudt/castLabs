/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I define the common Media Parser Functions specific HTTP interface
 */

#include <stdexcept>
#include "IsoBaseMediaHTTPParser.h"
#include "../utils/Logging.h"

using std::min;
using std::runtime_error;
using std::to_string;

static const uint64_t CHUNK_SIZE = 100; // just a random choice for now to allow for a few iterations

IsoBaseMediaHTTPParser::IsoBaseMediaHTTPParser(HTTPSimple& httpInterface): m_httpInterface(httpInterface){

}

void IsoBaseMediaHTTPParser::extractMdatBlock(const uint64_t& index){
    // get mdat block size
    uint64_t blockSize = this->parseBlock(index, "mdat");
    if (blockSize == 0){
        LOG(ERR, "\"mdat\" block is not present \n");
        throw runtime_error("\"mdat\" block is not present");
    }
    cout << " block size: " << blockSize << endl;
    // loop through content chunk by chunk and print out
    uint64_t contentIndex = index + BOX_HEADER_SIZE;
    uint64_t upperIndex = index + blockSize - BOX_HEADER_SIZE;
    this->displayHeadingOfBlockData("mdat");
    while (contentIndex < upperIndex){
        string chunkContent;
        uint64_t indexIncrease = min(CHUNK_SIZE, upperIndex-contentIndex);
        if (indexIncrease <= 0) break;
        this->retrievePartialBoxContent(contentIndex, indexIncrease, chunkContent);
        this->displayPartialBlockData(chunkContent);
        contentIndex += indexIncrease;
    }
}

uint64_t IsoBaseMediaHTTPParser::retrieveBoxSize(const uint64_t& index) const{
    string size;
    string range;
    this->constructRangeString(index, 3, range);
    this->m_httpInterface.receiveByteRange(range.c_str(), size);
    // extract length
    uint64_t boxSize = 0;
    for (int i = 0; i < size.length(); ++i) {
        boxSize = (boxSize << 8) | ((uint16_t) size[i] & 0xff);
    }
    LOG(VERB, "Box size: " << boxSize << "\n");
    return boxSize;
}

void IsoBaseMediaHTTPParser::retrieveBoxType(const uint64_t& index, string & boxType) const{
    string range;
    this->constructRangeString(index, 3, range);
    this->m_httpInterface.receiveByteRange(range.c_str(), boxType);
    LOG(VERB, "Box type: " << boxType << "\n");
}

void IsoBaseMediaHTTPParser::constructRangeString(const uint64_t& start, const uint64_t& length, string & range) const{
    range = "bytes=";
    range.append(to_string(start));
    range.append("-");
    range.append(to_string(start+length));
}

void IsoBaseMediaHTTPParser::retrievePartialBoxContent(const uint64_t& start, const uint64_t& end, string & content) const{
    string range;
    LOG(VERB, "Retrieve Box Content for (" << start << " to " << end << "\n");
    this->constructRangeString(start, end, range);
    this->m_httpInterface.receiveByteRange(range.c_str(), content);
}

void IsoBaseMediaHTTPParser::displayHeadingOfBlockData(const char * name) const{
    LOG(INFO, "Content of " << name << " box is: ");
}

void IsoBaseMediaHTTPParser::displayPartialBlockData(const string & content) const{
    LOG(INFO, content << "\n");
}