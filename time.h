#if !defined(TIME_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include "CommonDefines.h"
flocal inline i64
get_current_time()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return(Result.QuadPart);
}

flocal inline r32
get_seconds_elapsed(i64 start, i64 end)
{
    ASSERT(end > start, "End counter is greater than start counter");
    persist r32 perfFreq = -1.0f;
    if (perfFreq == -1.0f)
    {
        LARGE_INTEGER perfCountFrequencyResult;
        QueryPerformanceFrequency(&perfCountFrequencyResult);
        perfFreq = (r32)perfCountFrequencyResult.QuadPart;   
    }

    return (r32)(end - start) / (r32)perfFreq;
}

#define TIME_H
#endif
