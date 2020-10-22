#include <stdio.h>
#include <sys/time.h>
#include "tempo.h"

double seconds() {
#ifdef USE_WINDOWS_TIMER
    LARGE_INTEGER frequency, now;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&now);
    return now.QuadPart / double(frequency.QuadPart);
#else
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec + now.tv_usec / 1000000.0;
#endif
}