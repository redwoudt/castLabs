cmake_minimum_required(VERSION 2.8)
project(MdatExtractor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES pugixml/pugixml.hpp pugixml/pugixml.cpp pugixml/pugiconfig.hpp main.cpp utils/Logging.h Mdat/MdatExtractor.cpp Mdat/MdatExtractor.h HTTP/HTTPSimple.cpp HTTP/HTTPSimple.h IsoBaseMediaParser/IsoBaseMediaFileParser.cpp IsoBaseMediaParser/IsoBaseMediaFileParser.h Interfaces/Interfaces.h IsoBaseMediaParser/IsoBaseMediaHTTPParser.cpp IsoBaseMediaParser/IsoBaseMediaHTTPParser.h IsoBaseMediaParser/IsoBaseMediaParser_Base.cpp IsoBaseMediaParser/IsoBaseMediaParser_Base.h ImageDecoder/ImageDecoder.cpp ImageDecoder/ImageDecoder.h Tests/UnitTests.cpp Tests/UnitTests.h)

# set executables
add_executable(MdatExtractor ${SOURCE_FILES})
add_executable(MdatExtractor_Linux ${SOURCE_FILES})

# set the POCO paths and libs
set(POCO_PREFIX      /usr/local)
set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNetd.dylib"
        "${POCO_LIB_DIR}/libPocoUtild.dylib"
        "${POCO_LIB_DIR}/libPocoJSONd.dylib"
        "${POCO_LIB_DIR}/libPocoXMLd.dylib"
        "${POCO_LIB_DIR}/libPocoFoundationd.dylib"
        "pthread")
set(POCO_LIBS_LINUX        "${POCO_LIB_DIR}/libPocoNetd.so"
        "${POCO_LIB_DIR}/libPocoUtild.so"
        "${POCO_LIB_DIR}/libPocoJSONd.so"
        "${POCO_LIB_DIR}/libPocoXMLd.so"
        "${POCO_LIB_DIR}/libPocoFoundationd.so"
        "pthread")

# set the include path for the app
target_include_directories(MdatExtractor PRIVATE "${POCO_INCLUDE_DIR}" pugixml)
target_include_directories(MdatExtractor_Linux PRIVATE "${POCO_INCLUDE_DIR}" pugixml)

# link the app against POCO
target_link_libraries(MdatExtractor "${POCO_LIBS}")
target_link_libraries(MdatExtractor_Linux "${POCO_LIBS_LINUX}")
