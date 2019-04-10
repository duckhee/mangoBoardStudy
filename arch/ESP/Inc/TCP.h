#ifndef __TCP_H__
#define __TCP_H__

#include "ESP8266.h"




#ifdef TCP_LOCAL
#define TCP_DEF
#else
#define TCP_DEF         extern
#endif

TCP_DEF bool PingTest(uint8_t *url);
TCP_DEF bool TCP_Connect(uint8_t *url, uint8_t *port);
TCP_DEF bool TCP_Send();


#endif