#ifndef __TCP_H__
#define __TCP_H__

#include "ESP8266.h"

typedef enum{
    HTTP = 0,

}TCP_SendDataTypeDef;


typedef struct{
    TCP_SendDataTypeDef method;
    uint8_t *Data;
    uint8_t *remoteUrl;
    uint8_t *remotePort;
    
}TCP_SendDataType;


#ifdef TCP_LOCAL
#define TCP_DEF
#else
#define TCP_DEF         extern
#endif

TCP_DEF bool PingTest(uint8_t *url);
TCP_DEF bool TCP_Connect(uint8_t *url, uint8_t *port);
TCP_DEF bool TCP_Send(TCP_SendDataType SendData);
TCP_DEF bool TCP_DisConnect(void);

#endif