#ifndef __HW_LED_H__
#define __HW_LED_H__

#include "Hw_Config.h"



#ifdef HW_LED_LOCAL
#define LED_DEF
#else
#define LED_DEF         extern
#endif

/* functions */
LED_DEF void LED_Init(void);
LED_DEF void LED_On_Red(void);
LED_DEF void LED_Off_Red(void);
LED_DEF void LED_On_Yellow(void);
LED_DEF void LED_Off_Yellow(void);
LED_DEF void LED_On_Blue(void);
LED_DEF void LED_Off_Blue(void);
LED_DEF void LED_On_All(void);
LED_DEF void LED_Off_All(void);

LED_DEF void LED_Test(void);


#endif