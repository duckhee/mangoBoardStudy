#ifndef __WEB_H__
#define __WEB_H__

#include "TCP.h"
#include "HTTP.h"


#ifdef WEB_LOCAL
#define WEB_DEF
#else
#define WEB_DEF           extern
#endif

#endif