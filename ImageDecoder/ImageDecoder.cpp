/*
 * Created by Ferdinand Redelinghuys on 2016/10/12.
 *
 * I extract image text from XML, decode it and save it to file
 * source based on code obtained from:
 * http://www.adp-gmbh.ch/cpp/common/base64.html and
 * http://stackoverflow.com/questions/7711682/convert-server-response-stdstring-into-a-png-file
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "ImageDecoder.h"
#include "../utils/Logging.h"
#include "pugixml.hpp"

using namespace pugi;

static const string base64_chars = \
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
        "abcdefghijklmnopqrstuvwxyz" \
        "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

void ImageDecoder::extractImages(const string & path, string & content) {
    xml_document doc;
    xml_parse_result result = doc.load_buffer(content.c_str(), content.length());
    LOG(VERB, result.description() << "\n");
    xml_node root = doc.child("tt").child("head").child("metadata");
    for (xml_node item = root.first_child(); item; item = item.next_sibling()) {
        LOG(VERB, item.name() << ": " << item.type() << "\n");
        string filename(path);
        filename.append(item.attribute("xml:id").value());
        filename.append(".");
        string extension = item.attribute("imagetype").value();
        // convert to lower case
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        filename.append(extension);
        LOG(VERB, "Filename: " << filename << "\n");
        string encoding = item.attribute("encoding").value();
        LOG(VERB, "Encoding: " << encoding << "\n");
        string data = item.first_child().value();
        LOG(VERB, "Data: " << data.data() << "\n");
        write_to_file((unsigned char const*)data.c_str(), filename);
    }
}

string ImageDecoder::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
            ret += '=';

    }

    return ret;

}

string ImageDecoder::base64_decode(string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;

    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) {
            ret += char_array_3[j];
        }
    }
    LOG(VERB, "decode: \n" << ret << ", size " << ret.size() << "\n");
    return ret;
}

// taken from
void ImageDecoder::write_to_file(unsigned char const* data, string path){
    std::ofstream fp;
    size_t count;
    LOG(INFO, "writing to file " << path.c_str() << "\n");
    fp.open(path.c_str(), std::ios_base::out | std::ios_base::binary);
    //convert data
    string str((char *)data);
    if (str[0] == '\n'){
        str = str.substr(1);
    }
    str = base64_decode(str);
    LOG(DEBUG, str << "\n");
    fp.write(str.c_str(), str.size());
}