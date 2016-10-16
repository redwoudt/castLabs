/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I simplify POCO HTTP usage
 */

#include "HTTPSimple.h"
#include "../utils/Logging.h"
#include <memory>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <vector>
#include <stack>

HTTPSimple::HTTPSimple(const string& pUri){
    try{
        HTTPStreamFactory::unregisterFactory();
    }
    catch (NotFoundException e){
        LOG(VERB, "HTTPStreamFactory not registered\n");
    }
    HTTPStreamFactory::registerFactory();
    m_uri = URI(pUri.c_str());
}

HTTPSimple::~HTTPSimple(void) {
    try{
        HTTPStreamFactory::unregisterFactory();
    }
    catch (NotFoundException e){
        LOG(VERB, "HTTPStreamFactory not registered\n");
    }
}

void HTTPSimple::setupHTTPRequest(){
    std::string path(m_uri.getPathAndQuery());
    if (path.empty()) path = "/";
    m_session.setHost(m_uri.getHost());
    m_session.setPort(m_uri.getPort());
    m_request.setMethod(HTTPRequest::HTTP_GET);
    m_request.setURI(path);
    m_request.setVersion(HTTPMessage::HTTP_1_1);
}

void HTTPSimple::sendRequest(){
    m_session.sendRequest(m_request);
}

void HTTPSimple::getContent(string& output) const{
    uint64_t contentLength = getContentLength();
    if (contentLength > 0){
        StreamCopier::copyToString(*m_inputStream, output);
    }
}

void HTTPSimple::receiveResponse(){
    m_inputStream = &m_session.receiveResponse(m_response);
}

uint64_t HTTPSimple::getContentLength() const{
    uint64_t contentLength = 0;
    if (m_response.hasContentLength()){
        contentLength = m_response.getContentLength64();
    }
    return contentLength;
}

bool HTTPSimple::supportByteRange() const{
    string accept_range = m_response.get("Accept-Ranges");
    if (accept_range != "bytes"){
        LOG(WARN, "Byte Range not Supported\n");
        return false;
    }
    return true;
}

bool HTTPSimple::receiveByteRange(const char * range, string & data){
    if (m_request.has("Range")){
        m_request.set("Range", range);
    }
    else {
        m_request.add("Range", range);
    }
    m_session.sendRequest(m_request);
    istream& rs = m_session.receiveResponse(m_response);
    getContent(data);
    return true;
}