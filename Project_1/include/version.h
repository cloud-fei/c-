#ifndef VERSION_H
#define VERSION_H
#include "hv/hdef.h"

#define VERSION_MAJOR    1
#define VERSION_MINOR    0
#define VERSION_PATCH    0

#define VERSION_STRING  STRINGIFY(VERSION_MAJOR) "." \
                        STRINGIFY(VERSION_MINOR) "." \
                        STRINGIFY(VERSION_PATCH)

static inline const char* version() {
    return VERSION_STRING;
}

#endif 