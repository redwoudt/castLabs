/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I extract MDAT information from provided URI
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "../HTTP/HTTPSimple.h"
#include "../IsoBaseMediaParser/IsoBaseMediaFileParser.h"
#include "../IsoBaseMediaParser/IsoBaseMediaHTTPParser.h"
#include "../utils/Logging.h"
#include "MdatExtractor.h"

using std::runtime_error;
using std::string;

// TODO - make this an input parameter (to force one or the other way)
static const uint64_t MAX_DOWNLOAD_SIZE_ALLOWED = 20000000; // bytes - value picked for demo purposes

void operator<<(MdatExtractor& extractor, const char * pUri){
    LOG(DEBUG, "Starting MDAT Extractor\n");
    try{
        extractor.processURI(pUri);
    }
    catch (runtime_error &e){
        LOG(ERR, "Caught runtime expection: " << e.what() << "\n");
    }

}

void MdatExtractor::processURI(const char * pUri){
    LOG(DEBUG, "processing " << pUri << "\n");
    // setup HTTP comms
    HTTPSimple httpInterface(pUri);
    httpInterface.setupHTTPRequest();
    // retrieve URI details
    httpInterface.sendRequest();
    httpInterface.receiveResponse();
    // get content length & byte support
    uint64_t contentLength = httpInterface.getContentLength();
    bool byteRangeSupport = httpInterface.supportByteRange();
    LOG(DEBUG, "content length " << contentLength << ", byte range support " << byteRangeSupport << "\n");
    if (contentLength < MAX_DOWNLOAD_SIZE_ALLOWED){
        // copy complete file locally
        string content;
        httpInterface.getContent(content);
        LOG(VERB, "content: \n" << content << "\n");
        IsoBaseMediaFileParser parser(content);
        parser.extractAllBlocks();
    }
    else {
        // no use if byte range is not supported
        if (!byteRangeSupport){
            LOG(ERR, "Content Length " << contentLength << " too long for singe download and byte range not supported\n");
            throw runtime_error("Byte range not supported");
        }
        // setup parser
        IsoBaseMediaHTTPParser parser(httpInterface);
        parser.extractAllBlocks();
    }
}