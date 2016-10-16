/*
** Created by Ferdinand Redelinghuys on 2016/10/08.
**
 * Basic Logging Implementation, a bit overkill but should do the job for the task at hand
*/

#ifndef MDATEXTRACTOR_LOGGING_H
#define MDATEXTRACTOR_LOGGING_H

#include <chrono>
#include <iostream>

using namespace std::chrono;
using std::cout;
using std::endl;

static const char * debug_string[] = {"ERROR", "WARNING", "INFO", "DEBUG", "VERBOSE"};

enum DEBUG_LEVEL{
    ERR,    // ERROR
    WARN,   // WARNING
    INFO,   // INFO
    DEBUG,  // DEBUG
    VERB    // VERBOSE
};

#define _DEBUG_LEVEL_ INFO

#ifdef _DEBUG_LEVEL_
#define LOG(level, ...) \
        if (level <= _DEBUG_LEVEL_ && level >= 0) { \
            cout << "[" << __TIME__ << "] " ;\
            cout << "[LOG-" << debug_string[level] << "] [" << __FUNCTION__ << ":" << __LINE__ << "] ";\
            cout << __VA_ARGS__; \
        }

// taken from http://stackoverflow.com/questions/2193544/how-to-print-additional-information-when-assert-fails
#define ASSERT(condition) {if(!(condition)){ LOG(ERR, "ASSERT FAILED: " << #condition << endl); assert(0);}}

#else
#define LOG(...)
#endif

#endif //MDATEXTRACTOR_LOGGING_H
