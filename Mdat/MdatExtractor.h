/*
 * Created by Ferdinand Redelinghuys on 2016/10/08.
 *
 * I extract MDAT information from provided URI
 */

#ifndef MDATEXTRACTOR_MDATEXTRACTOR_H
#define MDATEXTRACTOR_MDATEXTRACTOR_H

class MdatExtractor {
public:
    friend void operator<<(MdatExtractor&, const char *);
    void processURI(const char *);
};

#endif //MDATEXTRACTOR_MDATEXTRACTOR_H
