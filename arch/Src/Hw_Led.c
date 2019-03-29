#define HW_LED_LOCAL

#include "Hw_Led.h"

LED_DEF void LED_Init(void);
LED_DEF void LED_On_Red (void);
LED_DEF void LED_Off_Red (void);
LED_DEF void LED_On_Yellow (void);
LED_DEF void LED_Off_Yellow (void);
LED_DEF void LED_On_Blue (void);
LED_DEF void LED_Off_Blue (void);
LED_DEF void LED_On_All (void);
LED_DEF void LED_Off_All (void);

LED_DEF void LED_Test (void);

LED_DEF void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
   // LED configuration ...

    /* Configure gpio as output : LED1, LED2, LED3 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_LED1_PIN | GPIO_LED2_PIN | GPIO_LED3_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);
    LED_Off_All();
}
LED_DEF void LED_On_Red (void)
{
    GPIO_LED->BRR |= GPIO_LED1_PIN;
}

LED_DEF void LED_Off_Red (void)
{
    GPIO_LED->BSRR |= GPIO_LED1_PIN;
}
LED_DEF void LED_On_Yellow (void)
{
    GPIO_LED->BRR |= GPIO_LED2_PIN;
}
LED_DEF void LED_Off_Yellow (void)
{
    GPIO_LED->BSRR |= GPIO_LED2_PIN;
}
LED_DEF void LED_On_Blue (void)
{
    GPIO_LED-> BRR |= GPIO_LED3_PIN;
}
LED_DEF void LED_Off_Blue (void)
{
    GPIO_LED-> BSRR |= GPIO_LED3_PIN;
}
LED_DEF void LED_On_All (void)
{
    LED_On_Red();
    LED_On_Yellow();
    LED_On_Blue();
}
LED_DEF void LED_Off_All (void)
{
    LED_Off_Red();
    LED_Off_Yellow();
    LED_Off_Blue();
}


void LED_OnOffAll_Mult(uint32_t count)
{

    for(; count > 0; count --)
    {

        LED_Off_Red();
        LED_On_Yellow();
        LED_On_Blue();
        delay_1_second();

        LED_On_Red();
        LED_Off_Yellow();
        LED_On_Blue();
        delay_1_second();

        LED_On_Red();
        LED_On_Yellow();
        LED_Off_Blue();
        delay_1_second();
    }
}

LED_DEF void LED_Test (void)
{
    LED_Off_All();
    delay_1_second();
    LED_On_All();
    delay_1_second();
    LED_OnOffAll_Mult(30);
    LED_Off_All();
}

