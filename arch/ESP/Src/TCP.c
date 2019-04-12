#define TCP_LOCAL

#include "TCP.h"

TCP_DEF bool PingTest(uint8_t *url);
TCP_DEF bool TCP_Connect(uint8_t *url, uint8_t *port);
TCP_DEF bool TCP_DisConnect(void);


TCP_DEF bool PingTest(uint8_t *url)
{
    uint8_t temp[128];
    bzero(temp, sizeof(temp));
    sprintf(temp, "AT+PING=\"%s\"\r\n", url);
    ESP_SendCommand(temp);
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

TCP_DEF bool TCP_Connect(uint8_t *url, uint8_t *port)
{
    uint8_t temp[128];
    bool flag = FALSE;;
    bzero(temp, sizeof(temp));
    sprintf(temp, "AT+CIPSTART=\"TCP\",\"%s\",\"%d\"\r\n", url, port);
    ESP_SendCommand(temp);
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        flag = TRUE;
    }else{
        if(esp8266SearchBuffer("ALREADY"))
        {
            flag = TRUE;
        }
    }
    return flag;
}

TCP_DEF bool TCP_DisConnect(void)
{
    ESP_SendCommand("AT+CIPCLOSE\r\n");
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}



