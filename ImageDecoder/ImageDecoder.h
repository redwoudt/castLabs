/*
 * Created by Ferdinand Redelinghuys on 2016/10/12.
 *
 * I extract image text from XML, decode it and save it to file
 * source based on code obtained from:
 * http://www.adp-gmbh.ch/cpp/common/base64.html and
 * http://stackoverflow.com/questions/7711682/convert-server-response-stdstring-into-a-png-file
 */

#ifndef MDATEXTRACTOR_IMAGEDECODER_H
#define MDATEXTRACTOR_IMAGEDECODER_H

#include <string>

using std::string;

class ImageDecoder {
public:
    void extractImages(const string &, string &);
protected:
    string base64_decode(string const&);
    string base64_encode(unsigned char const*, unsigned int);
    void write_to_file(unsigned char const*, string);
};


#endif //MDATEXTRACTOR_IMAGEDECODER_H
