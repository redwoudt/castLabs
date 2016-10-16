/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I extract MDAT information from provided URI
 */

#ifndef MDATEXTRACTOR_MDATEXTRACTOR_H
#define MDATEXTRACTOR_MDATEXTRACTOR_H

#include <tuple>

using std::tuple;

typedef tuple<const char *, const char *> sourceAndDestination; /**< typedef source and destination strings */

/** Mdat Block Extractor
 */

class MdatExtractor {
public:
    /**
     * << operator overload, allows uri to be 'streamed' into extractor
     * @param extractor object to stream to
     * @param srcAndDest uri to stream from and path to write images to
    */
    friend void operator<<(MdatExtractor& extractor, sourceAndDestination srcAndDest);
    /**
     * Process URI to extract Mdat data
     * @param srcAndDest uri to stream from and path to write images to
    */
    void processURI(sourceAndDestination srcAndDest);
};

#endif //MDATEXTRACTOR_MDATEXTRACTOR_H
