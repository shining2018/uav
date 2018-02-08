/*
 * Compat.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_COMPAT_H_
#define INET_COMMON_COMPAT_H_

#include <iostream>
#include <omnetpp.h>

namespace omnetpp { }  // so "using namespace omnetpp" in INETDefs.h doesn't cause error for OMNeT++ 4.x

namespace inet {

    typedef uint64_t uint64;
    typedef int64_t  int64;
    typedef uint32_t uint32;
    typedef int32_t  int32;
    typedef uint16_t uint16;
    typedef int16_t  int16;
    typedef uint8_t  uint8;

#  define EVSTREAM                      EV

#ifdef _MSC_VER
// complementary error function, not in MSVC
double INET_API erfc(double x);

// ISO C99 function, not in MSVC
inline long lrint(double x)
{
    return (long)floor(x + 0.5);
}

// ISO C99 function, not in MSVC
inline double fmin(double a, double b)
{
    return a < b ? a : b;
}

// ISO C99 function, not in MSVC
inline double fmax(double a, double b)
{
    return a > b ? a : b;
}

#endif    // _MSC_VER

} // namespace inet



#endif /* INET_COMMON_COMPAT_H_ */
