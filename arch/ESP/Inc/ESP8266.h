#ifndef __ESP8266_H__
#define __ESP8266_H__

/* include header */
#include "Hw_Config.h"
#include "string.h"

/**
 * custom method header
*/
#include "HTTP.h"
#include "TCP.h"


/*
    PA2 UART2_TXD 16
    PA3 UART2_RXD 17
    using interrupt usart 
    AT+COMMAND 사용시에 공북 없다. 공백 제거 필수
*/

#define ESPUSART USART3
#define ESPPORT  GPIOB
#define ESP_Rx_pin         GPIO_Pin_11 /* PB11 */
#define ESP_Tx_pin         GPIO_Pin_10 /* PB10 */

///////////////////////////////
// Command Response Timeouts //
///////////////////////////////
#define COMMAND_RESPONSE_TIMEOUT 10000
#define COMMAND_PING_TIMEOUT 3000
#define WIFI_CONNECT_TIMEOUT 30000
#define COMMAND_RESET_TIMEOUT 5000
#define CLIENT_CONNECT_TIMEOUT 5000
 
//connection type
#define TCP                  "TCP"
#define UDP                  "UDP"
#define SSL                  "SSL"

#define ESPBUF_MAXSIZE       1000

typedef enum{
    ESP8266_MODE_STATION = 1,
    ESP8266_MODE_AP = 2,
    ESP8266_MODE_AP_STATION = 3
}AT_CWMODE;

typedef enum  {
	ESP8266_ECN_OPEN = 0,
	ESP8266_ECN_WPA_PSK = 2,
	ESP8266_ECN_WPA2_PSK = 3,
	ESP8266_ECN_WPA_WPA2_PSK = 4
}esp8266_encryption;

typedef enum{
    SINGLE_CONNECTION = 0,
    MULTI_CONNECTION = 1
}esp8266_ConnectionType;

static uint8_t *Response[] = {
    "OK\r\n",
    "ERROR\r\n",
    "ready\r\n",
    "WIFI CONNECTED\r\n",
    "WIFI GOT IP\r\n",
    "WIFI DISCONNECT\r\n",
    "busy s...\r\n",
    "busy p...\r\n",
    "+IPD\r\n",
};


#ifdef ESP8266_LOCAL
#define ESP8266_DEF
#else
#define ESP8266_DEF                 extern
#endif

ESP8266_DEF void ESP_Configuration(void);
ESP8266_DEF void ESP_Init(void);

ESP8266_DEF bool esp8266ReadForResponse(const char *rsp, unsigned int timeout);
ESP8266_DEF bool esp8266RxBufferAvailable(void);
ESP8266_DEF bool esp8266SearchBuffer(const char * test);

ESP8266_DEF bool AT_Test(void);
ESP8266_DEF bool ESP_Reset(void);
ESP8266_DEF bool ESP_FactoryReset(void);
ESP8266_DEF bool ESP_ModeSet(AT_CWMODE mode);
ESP8266_DEF bool ESP_ModeCheck(void);

ESP8266_DEF bool ESP_SetMux(esp8266_ConnectionType connType);
ESP8266_DEF bool ESP_Status(void);

ESP8266_DEF bool ESP_ApList(void);
ESP8266_DEF uint8_t ApNames(uint8_t *list, uint8_t *Name[]);
ESP8266_DEF uint8_t ApNameList(uint8_t *Name[], uint8_t *NameLength, uint8_t *NameList[]);

ESP8266_DEF bool ESP_StationList(void);
ESP8266_DEF uint8_t StationNames(uint8_t *list, uint8_t *Name[]);

//TODO
ESP8266_DEF bool ESP_Connection(uint8_t *ssid, uint8_t *password);
ESP8266_DEF bool ESP_DisConnection(void);

ESP8266_DEF void ESP_SendCommand(char *command);

ESP8266_DEF void ESP_EnQueue(uint8_t data);
ESP8266_DEF void ESP_Increase_point_value(uint32_t *data_p);
ESP8266_DEF uint8_t ESP_DeQueue(void);
ESP8266_DEF bool ESP_Data_Empty(void);
ESP8266_DEF void ESP_ResponseDataClean(void);
ESP8266_DEF uint8_t *ESP_ResponseData(void);

#endif