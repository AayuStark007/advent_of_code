#ifndef UTIL_H
#define UTIL_H

#ifdef DEBUG_LOGGING
#define debugf printf
#else
#define debugf(...)
#endif

#endif