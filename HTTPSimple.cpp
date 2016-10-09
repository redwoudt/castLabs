/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I simplify POCO HTTP usage
 */

#include "HTTPSimple.h"
#include "Logging.h"
#include <memory>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <vector>
#include <stack>

using std::string;
using std::istream;
using namespace Poco::Net;

HTTPSimple::HTTPSimple(const char * pUri){
    HTTPStreamFactory::registerFactory();
    this->m_uri = URI(pUri);
}

void HTTPSimple::setupHTTPRequest(){
    std::string path(this->m_uri.getPathAndQuery());
    if (path.empty()) path = "/";
    this->m_session.setHost(this->m_uri.getHost());
    this->m_session.setPort(this->m_uri.getPort());
    this->m_request.setMethod(HTTPRequest::HTTP_GET);
    this->m_request.setURI(path);
    this->m_request.setVersion(HTTPMessage::HTTP_1_1);
}

void HTTPSimple::sendRequest(){
    this->m_session.sendRequest(this->m_request);
}

void HTTPSimple::getContent(string& output) const{
    StreamCopier::copyToString(*this->m_inputStream, output);
}

void HTTPSimple::receiveResponse(){
    this->m_inputStream = &this->m_session.receiveResponse(this->m_response);
}

uint64_t HTTPSimple::getContentLength() const{
    return this->m_response.getContentLength64();
}

bool HTTPSimple::supportByteRange() const{
    string accept_range = this->m_response.get("Accept-Ranges");
    if (accept_range != "bytes"){
        LOG(WARN, "Byte Range not Supported\n");
        return false;
    }
    return true;
}