#pragma once

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#endif
#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);		(p)=NULL; } }
#endif
#if !defined(SAFE_RELEASE)
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; } }
#endif
#if !defined(SAFE_FCLOSE)
#define SAFE_FCLOSE(p)			{ if(p) { ::fclose(p);		(p)=NULL; } }
#endif
#if !defined(SAFE_RELEASE2)
#define SAFE_RELEASE2(p)			{ if(p) { (p)->release();	(p)=NULL; } }
#endif

#define DEFTYPE_INT(name, value)	int const name = value;
#define DEFTYPE_STRING(name, value) char const * const name = value;

#include <map>
#include <vector>
#include <queue>
#include <windows.h>
#include <string>
