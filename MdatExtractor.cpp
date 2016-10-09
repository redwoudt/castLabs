/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I extract MDAT information from provided URI
 */

#include <iostream>
#include <string>
#include "HTTPSimple.h"
#include "IsoBaseMediaFileParser.h"
#include "Logging.h"
#include "MdatExtractor.h"

using std::string;

static const uint64_t MAX_DOWNLOAD_SIZE_ALLOWED = 10000000; // bytes - value picked for demo purposes

void operator<<(MdatExtractor& extractor, const char * pUri){
    LOG(DEBUG, "Starting MDAT Extractor\n");
    extractor.processURI(pUri);
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
        // next pass string reference into file parser and implement the file extract code in there
        // initially do all in one, but then see if it can be broken up to smaller bits for both
        // consider using and interface to implement different versions of parser ???
        IsoBaseMediaFileParser parser(content);
        parser.extractAllBlocks();
    }
    else {
        if (!byteRangeSupport){
            // throw exception
        }
        // tomorrow put code here from doing multiple HTTP GETs to complete the task
        // get moof details and download completely if not exceeding upper limit, leave rest for further implementation
        // get mdat data in chunks if exceeding download size
    }
}