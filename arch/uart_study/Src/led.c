#define LED_LOCAL

#include "led.h"

LED_DEF void LED_Init(void);
LED_DEF void LED_On_Red(void);
LED_DEF void LED_Off_Red(void);
LED_DEF void LED_On_Blue(void);
LED_DEF void LED_Off_Blue(void);
LED_DEF void LED_On_Yellow(void);
LED_DEF void LED_Off_Yellow(void);
LED_DEF void LED_On_All(void);
LED_DEF void LED_Off_All(void);
void LED_OnOffAll_Mult(uint32_t count);
LED_DEF void LED_Test(void);

LED_DEF void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN | GPIO_LED2_PIN | GPIO_LED3_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(GPIO_LED, &GPIO_InitStructure);
    LED_Off_All();

}
LED_DEF void LED_On_Red(void)
{
    GPIO_ResetBits(GPIO_LED, GPIO_LED1_PIN);
}
LED_DEF void LED_Off_Red(void)
{
    GPIO_SetBits(GPIO_LED, GPIO_LED1_PIN);
}
LED_DEF void LED_On_Blue(void)
{
    GPIO_ResetBits(GPIO_LED, GPIO_LED2_PIN);
}
LED_DEF void LED_Off_Blue(void)
{
    GPIO_SetBits(GPIO_LED, GPIO_LED2_PIN);
}
LED_DEF void LED_On_Yellow(void)
{
    GPIO_ResetBits(GPIO_LED, GPIO_LED3_PIN);
}
LED_DEF void LED_Off_Yellow(void)
{
    GPIO_SetBits(GPIO_LED, GPIO_LED3_PIN);
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

LED_DEF void LED_On_All(void)
{
    LED_On_Red();
    LED_On_Blue();
    LED_On_Yellow();
}
LED_DEF void LED_Off_All(void)
{
    LED_Off_Red();
    LED_Off_Blue();
    LED_Off_Yellow();
}

LED_DEF void LED_Test(void)
{
    LED_Off_All();
    delay_1_second();
    LED_On_All();
    delay_1_second();
    LED_OnOffAll_Mult(30);
    LED_Off_All();
}