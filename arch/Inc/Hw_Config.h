#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__


/* includes */

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "stdio.h"
#include "debug.h"
//#include "usb_lib.h"
//#include "usb_pwr.h"
//#include "usb_istr.h"
//#include "usb_desc.h"

/* hw function header */
#include "Hw_Led.h"
#include "lib_dbg.h"
#include "Private_Mode.h"



/* global variables */

//extern bool g_TestProcessState;

/* defines */

#define GPIO_LED             GPIOB
#define GPIO_KEY             GPIOA
#define GPIO_USART           GPIOA

#define GPIO_USB_DISCONNECT        GPIOA

#ifdef BOARD_DEF_MANGO_M32
    #define GPIO_7_SEG              GPIOC
#elif  BOARD_DEF_MANGO_Z1
    #define GPIO_RF_SPI                GPIOA
    #define GPIO_RF_RESET              GPIOC
    #define GPIO_RF_VREG_EN            GPIOC
    #define GPIO_RF_GPIO0_4            GPIOC
    #define GPIO_RF_GPIO5              GPIOD
#endif

#define GPIO_LED1_PIN        GPIO_Pin_9 /* RED */
#define GPIO_LED2_PIN        GPIO_Pin_5 /* YELLOW */ 
#define GPIO_LED3_PIN        GPIO_Pin_8 /* BLUE */

#define GPIO_KEY1_PIN        GPIO_Pin_0 /* LEFT_WKUP */
#define GPIO_KEY2_PIN        GPIO_Pin_1 /* RIGHT_USER */

#define GPIO_USART_Rx_Pin    GPIO_Pin_10
#define GPIO_USART_Tx_Pin    GPIO_Pin_9

#define GPIO_USB_DISCONNECT_PIN    GPIO_Pin_8

#ifdef BOARD_DEF_MANGO_M32
    #define GPIO_7_SEG_POWER_PIN    GPIO_Pin_8
    #define GPIO_7_SEG_A_PIN        GPIO_Pin_0
    #define GPIO_7_SEG_B_PIN        GPIO_Pin_1
    #define GPIO_7_SEG_C_PIN        GPIO_Pin_2
    #define GPIO_7_SEG_D_PIN        GPIO_Pin_3
    #define GPIO_7_SEG_E_PIN        GPIO_Pin_4
    #define GPIO_7_SEG_F_PIN        GPIO_Pin_5
    #define GPIO_7_SEG_G_PIN        GPIO_Pin_7
    #define GPIO_7_SEG_DP_PIN       GPIO_Pin_6
#elif  BOARD_DEF_MANGO_Z1
    #define GPIO_RF_SPI_NCS_PIN        GPIO_Pin_4
    #define GPIO_RF_SPI_CLK_PIN        GPIO_Pin_5
    #define GPIO_RF_SPI_MISO_PIN       GPIO_Pin_6
    #define GPIO_RF_SPI_MOSI_PIN       GPIO_Pin_7

    #define GPIO_RF_RESET_PIN          GPIO_Pin_6
    #define GPIO_RF_VREG_EN_PIN        GPIO_Pin_7

    #define GPIO_RF_GPIO0_PIN          GPIO_Pin_8
    #define GPIO_RF_GPIO1_PIN          GPIO_Pin_9
    #define GPIO_RF_GPIO2_PIN          GPIO_Pin_10
    #define GPIO_RF_GPIO3_PIN          GPIO_Pin_11
    #define GPIO_RF_GPIO4_PIN          GPIO_Pin_12
    #define GPIO_RF_GPIO5_PIN          GPIO_Pin_2
#endif

#define GPIO_PORTSOURCE_KEY        GPIO_PortSourceGPIOA
#define GPIO_PINSOURCE_KEY1        GPIO_PinSource0
#define GPIO_PINSOURCE_KEY2        GPIO_PinSource1
#define GPIO_EXTI_Line_KEY1        EXTI_Line0
#define GPIO_EXTI_Line_KEY2        EXTI_Line1

#ifdef  BOARD_DEF_MANGO_Z1
    #define GPIO_PORTSOURCE_RF_GPIO0   GPIO_PortSourceGPIOC
    #define GPIO_PINSOURCE_RF_GPIO0    GPIO_PinSource8
    #define GPIO_EXTI_Line_RF_GPIO0    EXTI_Line8
#endif


#ifdef HW_CONFIG_LOCAL
#define CONFIG_DEF 
#else
#define CONFIG_DEF        extern
#endif

CONFIG_DEF void RCC_Configuration(void);
CONFIG_DEF void USART1_Init(void);
CONFIG_DEF void USART1_GPIOConfiguration(void);
CONFIG_DEF void Delay(__IO uint32_t nTime);
CONFIG_DEF void TimingDelay_Decrement(void);
CONFIG_DEF void delay_1_second(void);
CONFIG_DEF void delay_100_milli_second(void);
CONFIG_DEF void NVIC_Configuration(void);
CONFIG_DEF void Hw_Init(void);
CONFIG_DEF uint8_t USART_GetCharacter(USART_TypeDef *  usart_p);



#endif