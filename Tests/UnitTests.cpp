/*
 * Created by Ferdinand Redelinghuys on 2016/10/15.
 *
 * I run unit tests on the system
 *
 * NOTE:
 * 1) This can be broken in to seperare files - ugly but getting the job done for now.
 * 2) Did not directly test external tools like Poco and Pugixml
 */

#include <assert.h>
#include "UnitTests.h"
#include "../utils/Logging.h"
#include "../Mdat/MdatExtractor.h"
#include "../HTTP/HTTPSimple.h"
#include "../IsoBaseMediaParser/IsoBaseMediaFileParser.h"
#include "../IsoBaseMediaParser/IsoBaseMediaHTTPParser.h"

static const char* uriToTest = "http://demo.castlabs.com/tmp/text0.mp4";
void UnitTests::runAll(const char* path) const{
    runGeneralTest(path);
    runHTTPTests();
    runIsoBaseMediaParserTests();
    runImageDecoderTests();
    runMdatExtractorTests();
}

void UnitTests::runGeneralTest(const char* path) const {
    LOG(INFO, "About to extract the following uri " << uriToTest << "\n");
    MdatExtractor extractor;
    extractor << std::make_tuple(uriToTest, path);
}

void UnitTests::runHTTPTests(void) const {
    // functional tests
    HTTPSimple httpInterface(uriToTest);
    httpInterface.setupHTTPRequest();
    ASSERT(!httpInterface.getURI().compare("/tmp/text0.mp4"));
    ASSERT(!httpInterface.getUriHost().compare(httpInterface.getSessionHost()));
    ASSERT(httpInterface.getUriPort() == httpInterface.getSessionPort());
    ASSERT(httpInterface.getMethod() == HTTPRequest::HTTP_GET);
    ASSERT(httpInterface.getVersion() == HTTPMessage::HTTP_1_1);
    httpInterface.sendRequest();
    httpInterface.receiveResponse();
    ASSERT(httpInterface.getContentLength() == 18089);
    string testData;
    httpInterface.getContent(testData);
    ASSERT(testData.length() == 18089);

    string range = "bytes=10-20";
    string byteData;
    httpInterface.receiveByteRange(range.c_str(), byteData);
    ASSERT(byteData.size() == 11);

    HTTPSimple httpInterface2("");
    httpInterface2.setupHTTPRequest();
    ASSERT(!httpInterface2.getURI().compare("/"));
    ASSERT(httpInterface2.getUriPort() == httpInterface2.getSessionPort());
    ASSERT(httpInterface2.getMethod() == HTTPRequest::HTTP_GET);
    ASSERT(httpInterface2.getVersion() == HTTPMessage::HTTP_1_1);
    try {
        httpInterface2.sendRequest();
    }
    catch(HostNotFoundException& ex){
        LOG(VERB, "Host not found as expected, " << ex.what() << "\n");
    }
    try {
        httpInterface2.receiveResponse();
    }
    catch(InvalidSocketException& ex){
        LOG(VERB, "Socket Exception as expected, " << ex.what() << "\n");
    }
    ASSERT(httpInterface2.getContentLength() == 0);

    string testData2;
    httpInterface2.getContent(testData2);
    ASSERT(testData2.length() == 0);

    string byteData2;
    try {
        httpInterface2.receiveByteRange(range.c_str(), byteData2);
    }
    catch(HostNotFoundException& ex){
        LOG(VERB, "Host not found as expected, " << ex.what() << "\n");
    }

    ASSERT(byteData2.size() == 0);
    LOG(VERB, "Byte Data Size: " << byteData2.size() << "\n");

    // out of sequence tests
    HTTPSimple httpInterface3(uriToTest);
    ASSERT(!httpInterface3.getURI().compare("/"));
    try {
        httpInterface3.sendRequest();
    }
    catch(HostNotFoundException& ex){
        LOG(VERB, "Host not found as expected, " << ex.what() << "\n");
    }
    try {
        httpInterface3.receiveResponse();
    }
    catch(InvalidSocketException& ex){
        LOG(VERB, "Socket Exception as expected, " << ex.what() << "\n");
    }
    ASSERT(httpInterface3.getContentLength() == 0);
    string testData3;
    httpInterface.getContent(testData3);
    ASSERT(testData3.length() == 0);

    // negative tests
    char data [3];
    data[0] = 'f';
    data[1] = 'u';
    data[2] = 'n'; // no '/0' terminator
    LOG(VERB, "uri is: " << string(data) << "\n");
    HTTPSimple httpInterface4((string(data)));
    ASSERT(httpInterface4.getContentLength() == 0);
    string testData4;
    httpInterface.getContent(testData4);
    ASSERT(testData4.length() == 0);

}

void UnitTests::runImageDecoderTests(void) const {
    //TODO
}

void UnitTests::runIsoBaseMediaParserTests(void) const {
    string content = "";
    IsoBaseMediaFileParser fileParser(content);
    fileParser.test();

    HTTPSimple httpInterface(uriToTest);
    IsoBaseMediaHTTPParser httpParser(httpInterface);
    httpParser.test();
}

void UnitTests::runMdatExtractorTests(void) const {
    //TODO
}