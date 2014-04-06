#ifndef CCTIME_H
#define CCTIME_H

#include "CCTypes.h"

struct cc_timeval
{
    long    tv_sec;        // seconds
    int tv_usec;    // microSeconds
};
class CCTime
{
public:
    static int gettimeofdayCocos2d(struct cc_timeval *tp, void *tzp)
    {
        if (tp)
        {
            qint64 time = QDateTime::currentMSecsSinceEpoch();
            tp->tv_sec = time/1000;
            tp->tv_usec = time%1000 * 1000;
        }
        return 0;
    }
};
#endif // CCTIME_H
