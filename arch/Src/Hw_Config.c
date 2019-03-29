#define HW_CONFIG_LOCAL

#include "Hw_Config.h"


CONFIG_DEF void RCC_Configuration(void);
CONFIG_DEF void USART1_Init(void);
CONFIG_DEF void USART1_GPIOConfiguration(void);
CONFIG_DEF void Delay(__IO uint32_t nTime);
CONFIG_DEF void TimingDelay_Decrement(void);
CONFIG_DEF void delay_1_second(void);
CONFIG_DEF void delay_100_milli_second(void);

#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
    #define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
    #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

uint32_t ADC_ConvertedValueX = 0;
uint32_t ADC_ConvertedValueX_1 = 0;
static volatile uint32_t TimingDelay;




/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
CONFIG_DEF void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
CONFIG_DEF void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}


CONFIG_DEF void delay_1_second(void)
{
    Delay(1000);
}

CONFIG_DEF void delay_100_milli_second(void)
{
    Delay(100);
}

CONFIG_DEF void USART1_GPIOConfiguration(void)
{
    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_USART_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_USART, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_USART_Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_USART, &GPIO_InitStructure);

}

CONFIG_DEF void USART1_Init(void)
{
    USART1_GPIOConfiguration();
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     - BaudRate = 115200 baud  
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - Hardware flow control disabled (RTS and CTS signals)
     - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

CONFIG_DEF void RCC_Configuration(void)
{
    
    SystemInit();

    /* Enable GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Enable GPIOB clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* Enable GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* Enable GPIOD clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    /* Enable USART1 clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* Enable AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

}

CONFIG_DEF void NVIC_Configuration(void)
{
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
}

PUTCHAR_PROTOTYPE
{
    /* Write a character to the USART */  
    if( ch == '\n') {
        USART_SendData(USART1, '\r');
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, '\n');
    }else {
        USART_SendData(USART1, (u8) ch);
    }
   USART_SendData(USART1, (uint8_t)ch);

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}

GETCHAR_PROTOTYPE
{
    uint8_t data;

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

    /* Write a character to the USART */
    data = USART_ReceiveData(USART1);

    USART_SendData(USART1, data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    if( data == '\r' )  return (int)('\n');
    else                return(data);
}

CONFIG_DEF uint8_t USART_GetCharacter(USART_TypeDef *  usart_p)
{
    uint8_t data;

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(usart_p, USART_FLAG_RXNE) == RESET);

    /* Write a character to the USART */
    data = USART_ReceiveData(usart_p);

    if( data == '\r' )  return (int)('\r\n');
    else                return(data);
}

