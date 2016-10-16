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
#include "Poco/Net/NetException.h"
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

/** A simple HTTP interface that makes sending requests and parsing responses easy
 *  for a given URI.
 */

class HTTPSimple {
public:
    /**
     * A constructor.
     *  Creates object with specified URI
     *  @param uri URI to use with HTTP communications
     */
    HTTPSimple(const string& pUri);
    /**
     * A destructor.
     */
    ~HTTPSimple(void);
    /**
     * Sets up HTTP configuration
     */
    void setupHTTPRequest(void);
    /**
     * Send Setup HTTP Request
     */
    void sendRequest(void);
    /**
     * Receive HTTP Response
     */
    void receiveResponse(void);
    /**
     * Extract Content Length from response header
     */
    uint64_t getContentLength(void) const;
    /**
     * Extract Content from response body
     * @param output returned content as string
     */
    void getContent(string& output) const;
    /**
     * Check if URI supports Byte Range Requests
     * @return true if byte range supported, false otherwise
     */
    bool supportByteRange(void) const;
    /**
     * HTTP Request for Byte Range
     * @param range byte range as string
     * @param data  content returned
     * @return bool true if byte range retrieved, false otherwise
     */
    bool receiveByteRange(const char * range, string & data);
    /**
     * Get URI
     * @return the URI
     */
    const string& getURI(void) {return m_request.getURI();}
    /**
     * Get Uri defined Host
     * @return the host
     */
    const string & getUriHost(void) {return m_uri.getHost();}
    /**
     * Get Session Host
     * @return the session host
     */
    const string & getSessionHost(void) {return m_session.getHost();}
    /**
     * Get Uri defined port number
     * @return the port number
     */
    u_int16_t getUriPort(void) {return (u_int16_t)m_uri.getPort();}
    /**
     * Get HTTP Session's Port Number
     * @return port number
     */
    u_int16_t getSessionPort(void) {return (u_int16_t)m_session.getPort();}
    /**
     * Get HTTP Request Method
     * @return the method
     */
    const std::string getMethod(void) {return m_request.getMethod();}
    /**
     * Get HTTP Request Version
     * @return the version
     */
    const std::string getVersion(void) {return m_request.getVersion();}
private:
    HTTPClientSession m_session; /**< HTTP Client session object */
    HTTPRequest m_request; /**< HTTP Client Request object */
    HTTPResponse m_response; /**< HTTP Client Response object */
    URI m_uri;  /**< URI object */
    istream* m_inputStream; /**< input streaming containing response data */
};


#endif //MDATEXTRACTOR_HTTPSIMPLE_H
