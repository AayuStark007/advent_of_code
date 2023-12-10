#ifndef UTIL_H
#define UTIL_H

#ifdef DEBUG_LOGGING
#define debugf printf
#else
#define debugf(...)
#endif

#endif

// TODO: input tokeniser which can capture details according to problem input
// eg: space separated nums: 34 56  4 56 => should give vector of [34, 56, 4,
// 56] eg: based on symbol like , or | or ;