#include <string.h>
#include "utils/Logging.h"
#include "Mdat/MdatExtractor.h"
#include "Tests/UnitTests.h"


void runTests(const char* path){
    UnitTests tests;
    tests.runAll(path);
}

void runBasicCase(const char* path){
    LOG(INFO, "Starting MDAT Extractor\n");
    const char* filename = "http://demo.castlabs.com/tmp/text0.mp4";
    sourceAndDestination srcAndDest = std::make_tuple(filename, path);
    LOG(INFO, "About to extract the following uri " << filename << "to " << path << "\n");
    MdatExtractor extractor;
    extractor << srcAndDest;
}

int main(int argc, char* argv[]) {
    if (argc < 2){
        LOG(ERR, "Usage: " << argv[0] << " requires destination to save images \n");
        return 1;
    }
    if (!strcmp(argv[1], ".")){ // can make improve this in future
        LOG(ERR, "Usage: " << argv[0] << " requires destination absolute path \n");
        return 1;
    }
    runBasicCase(argv[1]);
    //runTests(argv[1]); - use for testing
    return 0;
}