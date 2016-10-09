#include "Logging.h"
#include "MdatExtractor.h"

int main() {
    LOG(INFO, "Starting MDAT Extractor\n");
    const char* filename = "http://demo.castlabs.com/tmp/text0.mp4";
    LOG(INFO, "About to extract the following uri " << filename << "\n");
    MdatExtractor extractor;
    extractor << filename;
    return 0;
}