/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I simplify POCO HTTP usage
 */

#ifndef MDATEXTRACTOR_HTTPSIMPLE_H
#define MDATEXTRACTOR_HTTPSIMPLE_H

#include "Poco/Exception.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/Net/FTPStreamFactory.h"
#include "Poco/Path.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include "Poco/URIStreamOpener.h"

using namespace Poco;
using namespace Poco::Net;
using std::istream;
using std::string;

class HTTPSimple {
public:
    HTTPSimple(const char *);
    void setupHTTPRequest();
    void sendRequest();
    void receiveResponse();
    uint64_t getContentLength() const;
    void getContent(string& output) const;
    bool supportByteRange() const;
private:
    HTTPClientSession m_session;
    HTTPRequest m_request;
    HTTPResponse m_response;
    URI m_uri;
    istream* m_inputStream;
};


#endif //MDATEXTRACTOR_HTTPSIMPLE_H
