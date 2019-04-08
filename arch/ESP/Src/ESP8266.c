#define ESP8266_LOCAL

#include "ESP8266.h"

ESP8266_DEF bool esp8266ReadForResponse(const char *rsp, unsigned int timeout);
ESP8266_DEF bool esp8266RxBufferAvailable(void);
ESP8266_DEF bool esp8266SearchBuffer(const char * test);

ESP8266_DEF bool AT_Test(void);
ESP8266_DEF bool ESP_Reset(void);
ESP8266_DEF bool ESP_FactoryReset(void);

ESP8266_DEF bool ESP_SendCommand(char *command);

ESP8266_DEF void ESP_EnQueue(uint8_t data);
ESP8266_DEF void ESP_Increase_point_value(uint32_t *data_p);
ESP8266_DEF uint8_t ESP_DeQueue(void);
ESP8266_DEF bool ESP_Data_Empty(void);
ESP8266_DEF void ESP_ResponseDataClean(void);
ESP8266_DEF uint8_t *ESP_ResponseData(void);

uint8_t ESP_BUFFER[ESPBUF_MAXSIZE];
uint32_t esp_rx_point_header = 0;
uint32_t esp_rx_point_tail = 0;

ESP8266_DEF bool AT_Test(void)
{
    ESP_SendCommand("AT\r\n");
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

ESP8266_DEF bool ESP_Reset(void)
{
    ESP_SendCommand("AT+RST\r\n");
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

ESP8266_DEF bool ESP_FactoryReset(void)
{
    ESP_SendCommand("AT+RESTORE\r\n");
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

ESP8266_DEF void ESP_SendCommand(char *command)
{
    uint16_t i, length = strlen((char *)commnad);
    for(i = 0; i < length; i++)
    {
        USART_SendData(ESPUSART, *command);
        while(USART_GetFlagStatus(ESPUSART, USART_FLAG_TXE) == RESET);
        *command++;
    }
    
}

ESP8266_DEF bool esp8266ReadForResponse(const char *rsp, unsigned int timeout)
{
    
    unsigned long timeIn = millis();
    while(timeIn + timout > millis())
    {
        if(esp8266RxBufferAvailable())
        {
            if(esp8266SearchBuffer(rsp))
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

ESP8266_DEF bool esp8266RxBufferAvailable(){
    return (esp_rx_point_header > 0) ? TRUE : FALSE;
}

bool esp8266SearchBuffer(const char * test){
    int i = 0;
    int bufferlen = strlen((const char *)test);
    if(bufferlen < ESPBUF_MAXSIZE)
    {
        if(strstr((const char *)ESP_BUFFER), test)
        {
            return TRUE;
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    }
}

/**
 * circle queue 
 */
ESP8266_DEF void ESP_EnQueue(uint8_t data)
{
    espDataBuff[esp_rx_point_header] = data;
    ESP_Increase_point_value(&esp_rx_point_header);
}

ESP8266_DEF void ESP_Increase_point_value(uint32_t *data_p)
{
    (*data_p)++;
    if(ESPBUF_MAXSIZE == (*data_p))
    {
        (*data_p) = 0;
    }
}

ESP8266_DEF uint8_t ESP_DeQueue(void)
{
    uint8_t retVal = espDataBuff[esp_rx_point_tail];
    ESP_Increase_point_value(esp_rx_point_tail);
    return retVal;
}

ESP8266_DEF bool ESP_Data_Empty(void)
{
    if(esp_rx_point_header = esp_rx_point_tail)
    {
        return TRUE;
    }
    else{
        return FALSE;
    }
}

ESP8266_DEF void ESP_ResponseDataClean(void)
{
    memset(ESP_BUFFER,'\0', ESPBUF_MAXSIZE);
}

ESP8266_DEF uint8_t *ESP_ResponseData(void)
{
    return ESP_BUFFER;
}
