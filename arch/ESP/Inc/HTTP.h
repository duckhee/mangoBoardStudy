#ifndef __HTTP_H__
#define __HTTP_H__

#include "ESP8266.h"

typedef enum{
    GET = 0,
    POST = 1,
    PUT = 2,
    DELETE = 3
}HTTP_MethodTypeDef;

/**
  1) 상수인 경우
- internal linkage를 가짐(const int가 static const int와 동일한 의미를 가짐)
- 각기 다른 곳에서 include 할 때 변수의 주소를 출력해보면 다르게 출력됨을 알 수 있음

2) 상수가 아닌 경우
- external linkage를 가짐
- 각기 다른 곳에서 incldue 할 때 변수의 주소를 출력해보면 동일 해야만 함.
- 따라서 헤더파일에는 변수의 선언만 해야함.
정의를 해버린다면, include 할 때 마다 하나의 변수이름 대응되는 주소가 추가되버림.
 */


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