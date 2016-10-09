cmake_minimum_required(VERSION 3.5)
project(MdatExtractor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Logging.h MdatExtractor.cpp MdatExtractor.h HTTPSimple.cpp HTTPSimple.h IsoBaseMediaFileParser.cpp IsoBaseMediaFileParser.h)
add_executable(MdatExtractor ${SOURCE_FILES})

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

# set the include path for the app
target_include_directories(MdatExtractor PRIVATE "${POCO_INCLUDE_DIR}")
# link the app against POCO
target_link_libraries(MdatExtractor "${POCO_LIBS}")