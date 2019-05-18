#define HTTP_LOCAL

#include "HTTP.h"

const char *HTTP_Method[] = {"GET", "POST", "PUT", "DELETE"};

HTTP_DEF bool HTTP_Send(HTTP_MethodTypeDef Type, HTTP_Type http)
{
    
    if(TCP_Connect(http.RemoteUrl, http.RemotePort))
    {
        uint8_t temp[128];
        bzero(temp, sizeof(temp));
        ESP_ResponseDataClean();
        if(Type == GET)
        {
            sprintf("%s %s HTTP/1.1\r\nHost:%s\r\nUser-Agent: IoFDeviceV0.0.1\r\n ", HTTP_Method[Type], http.RemotePath, http.RemoteUrl);
        }
        
        //ESP_SendCommand("AT+CIPSEND=%d\r\n", strlen(temp));
        if(esp8266ReadForResponse(">", COMMAND_RESPONSE_TIMEOUT))
        {
            ESP_ResponseDataClean();
            ESP_SendCommand(temp);
            if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
            {
                return TRUE;
            }else{
                return FALSE;
            }
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    }
}