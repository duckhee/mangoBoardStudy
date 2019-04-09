#define ESP8266_LOCAL

#include "ESP8266.h"

ESP8266_DEF bool esp8266ReadForResponse(const char *rsp, unsigned int timeout);
ESP8266_DEF bool esp8266RxBufferAvailable(void);
ESP8266_DEF bool esp8266SearchBuffer(const char * test);

ESP8266_DEF bool AT_Test(void);
ESP8266_DEF bool ESP_Reset(void);
ESP8266_DEF bool ESP_FactoryReset(void);

ESP8266_DEF void ESP_SendCommand(char *command);

ESP8266_DEF void ESP_EnQueue(uint8_t data);
ESP8266_DEF void ESP_Increase_point_value(uint32_t *data_p);
ESP8266_DEF uint8_t ESP_DeQueue(void);
ESP8266_DEF bool ESP_Data_Empty(void);
ESP8266_DEF void ESP_ResponseDataClean(void);
ESP8266_DEF uint8_t *ESP_ResponseData(void);

uint8_t ESP_BUFFER[ESPBUF_MAXSIZE];
uint32_t esp_rx_point_header = 0;
uint32_t esp_rx_point_tail = 0;




ESP8266_DEF void ESP_Configuration(void)
{
    /* GPIOA port */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

    /* USART3 enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /* GPIO_Init */
    /* GPIO_Init ESP Rx */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ESP_Tx_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(ESPPORT, &GPIO_InitStructure);

    /* GPIO_Init ESP Tx */
    GPIO_InitStructure.GPIO_Pin = ESP_Rx_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(ESPPORT, &GPIO_InitStructure);

    /* USART Init */
    USART_InitTypeDef ESP_InitStructure;
    ESP_InitStructure.USART_BaudRate = 115200;
    ESP_InitStructure.USART_WordLength = USART_WordLength_8b;
    ESP_InitStructure.USART_StopBits = USART_StopBits_1;
    ESP_InitStructure.USART_Parity = USART_Parity_No;
    ESP_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    ESP_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* usart3 set */
    USART_Init(ESPUSART, &ESP_InitStructure);
    USART_ITConfig(ESPUSART, USART_IT_RXNE, ENABLE);
    /* usart3 start */
    USART_Cmd(ESPUSART, ENABLE);
}

ESP8266_DEF void esp_interrupt_configuration()
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


ESP8266_DEF void ESP_Init(void)
{
    
    ESP_Configuration();
    esp_interrupt_configuration();

    //ESP_Test();
}

ESP8266_DEF bool AT_Test(void)
{
    ESP_SendCommand("AT\r\n");
    if(esp8266ReadForResponse("OK", COMMAND_RESPONSE_TIMEOUT))
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

ESP8266_DEF bool ESP_ModeSet(AT_CWMODE mode)
{
    uint8_t Command[128];
    sprintf(Command, "AT+CWMODE=%d\r\n", mode);
    ESP_SendCommand(Command);
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

ESP8266_DEF bool ESP_SetMux(esp8266_ConnectionType connType)
{
    uint8_t Command[128];
    sprintf(Command, "AT+CIPMUX=%d\r\n", connType);
    ESP_SendCommand(Command);
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

ESP8266_DEF bool ESP_Status(void)
{
    ESP_SendCommand("AT+CIPSTATUS\r\n");
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

//TODO
ESP8266_DEF bool ESP_StationConnection()
{

}

ESP8266_DEF bool ESP_StationList(void)
{
    ESP_SendCommand("AT+CWLAP\r\n");
    if(esp8266ReadForResponse("OK\r\n", COMMAND_RESPONSE_TIMEOUT))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

ESP8266_DEF uint8_t StationNames(uint8_t *list, uint8_t *Name[])
{
    uint8_t count = 0, index = 0;
    //TODO need to check
    char *ptr = strtok(list, "()");
    while(ptr != NULL)
    {
        count++;
        if(count % 2 == 0)
        {
            //temp[index] = ptr;
            
            Name[index] = ptr;
            index++;
        }
        ptr = strtok(NULL, "()");
    }
    return index;
}

ESP8266_DEF void ESP_SendCommand(char *command)
{
    uint16_t i, length = strlen((char *)command);
    for(i = 0; i < length; i++)
    {
        USART_SendData(ESPUSART, *command);
        while(USART_GetFlagStatus(ESPUSART, USART_FLAG_TXE) == RESET);
        *command++;
    }
    
}

ESP8266_DEF bool esp8266ReadForResponse(const char *rsp, unsigned int timeout)
{
        Delay(timeout);
        if(esp8266RxBufferAvailable())
        {
            if(esp8266SearchBuffer(rsp))
            {
                return TRUE;
            }
        }
    return FALSE;
}

ESP8266_DEF bool esp8266RxBufferAvailable()
{
    return (esp_rx_point_header > 0) ? TRUE : FALSE;
}

ESP8266_DEF bool esp8266SearchBuffer(const char * test)
{
    int i = 0;
    int bufferlen = strlen((const char *)ESP_BUFFER);
    if(bufferlen < ESPBUF_MAXSIZE)
    {
        if(strstr((const char *)ESP_BUFFER, test))
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
    ESP_BUFFER[esp_rx_point_header] = data;
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
    uint8_t retVal = ESP_BUFFER[esp_rx_point_tail];
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
    memset(ESP_BUFFER,'\0', sizeof(ESP_BUFFER));
    esp_rx_point_header = esp_rx_point_tail = 0;
}

ESP8266_DEF uint8_t *ESP_ResponseData(void)
{
    return ESP_BUFFER;
}

