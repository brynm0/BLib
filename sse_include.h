#if !defined(SSE_INCLUDE_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#ifdef SSE_WIDTH_8
#include "sse_8.h"
#else
#ifdef SSE_WIDTH_4
#include "sse_4.h"
#else
#include "sse_1.h"
#endif
#endif

#define SSE_INCLUDE_H
#endif
