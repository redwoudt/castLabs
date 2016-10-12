/*
 * Created by Ferdinand Redelinghuys on 2016/10/09.
 *
 * I list all interfaces defined in project
 */

#ifndef MDATEXTRACTOR_INTERFACES_H
#define MDATEXTRACTOR_INTERFACES_H

#include <stdint.h>
#include <string>

using std::string;

class IsoBaseMediaParser {
public:
    virtual void extractAllBlocks() = 0;
    virtual uint64_t extractMoofBlocks() = 0;
    virtual void extractMdatBlock(const uint64_t& ) = 0;
};

#endif //MDATEXTRACTOR_INTERFACES_H
