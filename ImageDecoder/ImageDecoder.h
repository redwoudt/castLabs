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

/** Extracts images from XML data.
 */

class ImageDecoder {
public:
    /**
     *  Extract images from given string to given path
     *  @param path path to extract images to
     *  @param content content to extract from
     */
    void extractImages(const string & path, string & content);
protected:
    /**
     *  Decode string to image
     *  @param encoded_string string to decode
     *  @return string containing decoded image
     */
    string base64_decode(string const& encoded_string);
    /**
     *  Encode image to string
     *  @param bytes_to_encode string to encode
     *  @param in_len length of content to encode
     *  @return string containing encoded image
     */
    string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    /**
     *  Write content to file
     *  @param data data to write
     *  @param path path to file
     */
    void write_to_file(unsigned char const* data, string path);
};


#endif //MDATEXTRACTOR_IMAGEDECODER_H
