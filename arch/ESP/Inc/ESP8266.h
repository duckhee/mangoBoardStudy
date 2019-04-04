#ifndef __ESP8266_H__
#define __ESP8266_H__

/* include header */
#include "Hw_Config.h"


/*
    PA2 UART2_TXD 16
    PA3 UART2_RXD 17
    using interrupt usart 
    AT+COMMAND 사용시에 공북 없다. 공백 제거 필수
*/

#define ESPUSART USART3
#define ESPPORT  GPIOB





#endif