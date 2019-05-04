#ifndef __HTTP_H__
#define __HTTP_H__

#include "ESP8266.h"

typedef enum{
    GET = 0,
    POST = 1,
    PUT = 2,
    DELETE = 3
}HTTP_MethodTypeDef;



typedef struct{
    uint8_t *RemoteUrl;
    uint8_t *RemotePort;
    uint8_t *RemotePath;
    uint8_t *Data;
    uint8_t DataLength;
}HTTP_Type;


#ifdef HTTP_LOCAL
#define HTTP_DEF
#else
#define HTTP_DEF         extern
#endif

HTTP_DEF bool HTTP_Send(HTTP_MethodTypeDef MethodType, HTTP_Type http);

#endif