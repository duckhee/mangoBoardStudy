#include "main.h"
#include "ESP8266.h"

bool g_TestProcessState = FALSE;
RCC_ClocksTypeDef rcc_clocks;

void System_Information()
{
    printf("SYSCLK_Frequency = %d\n",rcc_clocks.SYSCLK_Frequency );
    printf("HCLK_Frequency = %d\n",rcc_clocks.HCLK_Frequency );
    printf("PCLK1_Frequency = %d\n",rcc_clocks.PCLK1_Frequency );
    printf("PCLK2_Frequency = %d\n",rcc_clocks.PCLK2_Frequency );
    printf("ADCCLK_Frequency = %d\n",rcc_clocks.ADCCLK_Frequency );
}

int main(int argc, char **argv)
{
    RCC_Configuration();
    USART1_Init();
    debug();
    if(SysTick_Config(rcc_clocks.SYSCLK_Frequency / 1000))
    {
        while(1);
    }
    System_Information();

    while(1)
    {

    }
    return 1;
}