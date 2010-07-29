// precompiled_header.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifndef precompiled_header_h__
#define precompiled_header_h__



#include <stdio.h>
#include <tchar.h>
#include "Managers\CCodeProfiler.h"

#define START_PROFILING CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
#define END_PROFILING CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);

#define MAX_INVENTORY 4
#define ITEM_RANGE 250


#endif // precompiled_header_h__

// TODO: reference additional headers your program requires here
