#include "hw_config.h"
#include "lib_dbg.h"

RCC_ClocksTypeDef rcc_clocks;

bool g_TestProcessState = FALSE;

void System_Information()
{
    DEBUG_MSG_FUNC_START;

    printf("SYSCLK_Frequency = %d\n",rcc_clocks.SYSCLK_Frequency );
    printf("HCLK_Frequency = %d\n",rcc_clocks.HCLK_Frequency );
    printf("PCLK1_Frequency = %d\n",rcc_clocks.PCLK1_Frequency );
    printf("PCLK2_Frequency = %d\n",rcc_clocks.PCLK2_Frequency );
    printf("ADCCLK_Frequency = %d\n",rcc_clocks.ADCCLK_Frequency );
}

int main()
{
    uint8_t ch;
    GPIO_InitTypeDef GPIOA_InitStructure;

    RCC_Configuration();
    RCC_GetClocksFreq(&rcc_clocks);

    NVIC_Configuration();

    GPIO_Configuration();

    EXTI_Configuration();

    USART1_Init();

    debug();

    if (SysTick_Config(rcc_clocks.SYSCLK_Frequency / 1000))
    {
        while(1);
    }

    Delay(100);

    while (1)
    {
        /* code */
        printf("\r\n=====================================================\r\n");
#ifdef BOARD_DEF_MANGO_M32
        printf("Mango M32 test start...\r\n");
#elif BOARD_DEF_MANGO_Z1
        printf("Mango Z1 test start...\n");
#endif
        printf("Press menu key \r\n");
        printf("--------------------------------------------------------\r\n");
        printf("0> System Information\r\n");
        printf("1> LED Test \r\n");
        printf("2> KEY Test \r\n");
#ifdef BOARD_DEF_MANGO_M32
        printf("3> 7-segment Test \r\n");
#elif BOARD_DEF_MANGO_Z1
        printf("3> zigBee Test \r\n");
#endif
        printf("5> Debug Test 1 \r\n");
        printf("6> Debug Test 2 \r\n");
        printf("x> quit \r\n");

        ch = USART_GetCharacter(USART1);
        printf(" is selected \r\n");

        switch((char)ch)
        {
        case '0':
            System_Information();
            break;

        case '1':
            LED_Test();
            break;

        case '2':
            KEY_Test();
            break;

        case '3':
#ifdef BOARD_DEF_MANGO_M32
            Seven_Segment_Test();
#elif  BOARD_DEF_MANGO_Z1
            ZigBee_Test();
#endif
            break;

        case '4':

            break;

        case '5':
            /* Simulate wrong parameter passed to library function */
            /* To enable SPI1 clock, RCC_APB2PeriphClockCmd function
               must be used and not RCC_APB1PeriphClockCmd */
            RCC_APB1PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
            break;

        case '6':
            /* Some member of GPIOA_InitStructure structure are not initialized */
            GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            /* GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; */
            GPIO_Init(GPIOA, &GPIOA_InitStructure);
            break;
        }

        if('x' == (char)ch)
        {
            break;
        }
    }

    return 0;
}
