/*
 * Created by Ferdinand Redelinghuys on 2016/10/15.
 *
 * I run unit tests on the system
 */

#ifndef MDATEXTRACTOR_UNITTESTS_H
#define MDATEXTRACTOR_UNITTESTS_H


class UnitTests {
public:
    void runAll(const char* path) const;
    void runGeneralTest(const char* path) const;
    void runHTTPTests(void) const;
    void runImageDecoderTests(void) const;
    void runIsoBaseMediaParserTests(void) const;
    void runMdatExtractorTests(void) const;
};
#endif //MDATEXTRACTOR_UNITTESTS_H
