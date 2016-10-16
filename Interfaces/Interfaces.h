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

/** Abstract Class defining required Iso Base Media Parser functions.
 */

class IsoBaseMediaParser {
public:
    /**
     * Extract All Blocks from Iso Base Media Content.
     * @param path destination path for to write image to
     */
    virtual void extractAllBlocks(const char * path) = 0;
    /**
     * Extract All Moof Blocks from Iso Base Media Content.
     * @return total size of moof blocks
     */
    virtual uint64_t extractMoofBlocks(void) = 0;
    /**
     * Extract Mdat Block from Iso Base Media Content.
     * @param index starting byte index
     * @param path destination path for to write image to
     */
    virtual void extractMdatBlock(const uint64_t& index, const char * path) = 0;
};

#endif //MDATEXTRACTOR_INTERFACES_H
