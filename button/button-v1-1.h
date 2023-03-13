/*******************************************************************************
 *				 _ _                                             _ _
				|   |                                           (_ _)
				|   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
				|   |       |   |   |   | |    _ _     _ _    | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
				|_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
								(C)2023 Lumi
 * Copyright (c) 2023
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: button-v1-1.h
 *
 * Description: This code is used for tranning Lumi IOT member. It is the code form statandard.
 *
 * Author: CuuNV
 *
 * Last Changed By:  $Author: CuuNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Feb 9, 2023
 *
 * Code sample:
 ******************************************************************************/
#ifndef SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_BUTTON_V1_1_BUTTON_V1_1_H_
#define SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_BUTTON_V1_1_BUTTON_V1_1_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stm32f401re_rcc.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_exti.h>
#include <stm32f401re_syscfg.h>
#include <misc.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

//define of button 1:PB1--Down ,button 2:PB2--Right
#define BUTTON_1_PIN				GPIO_Pin_1
#define BUTTON_1_PINSOURCE			GPIO_PinSource1
#define BUTTON_2_PIN				GPIO_Pin_2
#define BUTTON_2_PINSOURCE			GPIO_PinSource2

#define BUTTON_1_EXTI_PinSource		EXTI_PinSource1
#define BUTTON_2_EXTI_PinSource		EXTI_PinSource2

#define BUTTON_1_EXTI_LINE			EXTI_Line1
#define BUTTON_2_EXTI_LINE			EXTI_Line2

#define BUTTON_1_NVIC_IRQCHANNEL 	EXTI1_IRQn
#define BUTTON_2_NVIC_IRQCHANNEL 	EXTI2_IRQn

#define BUTTON_1_2_PORT				GPIOB
#define BUTTON_1_2_GPIO_RCC			RCC_AHB1Periph_GPIOB
#define BUTTON_1_2_EXTI_PORTSOURCE  EXTI_PortSourceGPIOB

//define of button 3:PC3--Up,button 4:PC0--Left
#define BUTTON_3_PIN				GPIO_Pin_3
#define BUTTON_4_PIN				GPIO_Pin_0

#define BUTTON_3_PINSOURCE			GPIO_PinSource3
#define BUTTON_4_PINSOURCE			GPIO_PinSource0

#define BUTTON_3_4_PORT				GPIOC
#define BUTTON_3_4_GPIO_RCC			RCC_AHB1Periph_GPIOC

#define BUTTON_3_EXTI_PinSource		EXTI_PinSource3
#define BUTTON_4_EXTI_PinSource		EXTI_PinSource0

#define BUTTON_3_4_EXTI_PORTSOURCE  EXTI_PortSourceGPIOC

#define BUTTON_3_EXTI_LINE			EXTI_Line3
#define BUTTON_4_EXTI_LINE			EXTI_Line0

#define BUTTON_3_NVIC_IRQCHANNEL 	EXTI3_IRQn
#define BUTTON_4_NVIC_IRQCHANNEL 	EXTI0_IRQn

//define of button 5:PA5--Select/Return
#define BUTTON_5_PIN				GPIO_Pin_5
#define BUTTON_5_PINSOURCE			GPIO_PinSource5
#define BUTTON_5_PORT				GPIOA
#define BUTTON_5_GPIO_RCC			RCC_AHB1Periph_GPIOA
#define BUTTON_5_EXTI_PinSource		EXTI_PinSource5
#define BUTTON_5_EXTI_PORTSOURCE  	EXTI_PortSourceGPIOA
#define BUTTON_5_EXTI_LINE			EXTI_Line0
#define BUTTON_5_NVIC_IRQCHANNEL 	EXTI9_5_IRQn
//define of LedButton:PB9
#define LED_BUTTON_PIN				GPIO_Pin_9
#define LED_BUTTON_PORT				GPIOB
#define LED_BUTTON_RCC				RCC_AHB1Periph_GPIOB

#define BUTTON_DEBOUNCE_TIME      		5u
#define BUTTON_NORMAL_PRESS_TIME  		60u
#define BUTTON_LONG_PRESS_TIME    		1000u
#define BW2PRESS_TIME		            300u

/* Button byStatus */
#define BUTTON_EDGE_RISING              	1
#define BUTTON_EDGE_FALLING             	2
#define Null								0
/* Button states */
#define BUTTON_STATE_START        	0
#define BUTTON_STATE_DEBOUNCE     	1
#define BUTTON_STATE_PRESSED      	2
#define BUTTON_STATE_WAITPRESS		3
#define BUTTON_STATE_WAITRELEASE  	4
#define BTN1_GET					GPIO_ReadInputDataBit(BUTTON_1_2_PORT, BUTTON_1_PIN)
#define BTN2_GET					GPIO_ReadInputDataBit(BUTTON_1_2_PORT, BUTTON_2_PIN)
#define BTN3_GET					GPIO_ReadInputDataBit(BUTTON_3_4_PORT, BUTTON_3_PIN)
#define BTN4_GET					GPIO_ReadInputDataBit(BUTTON_3_4_PORT, BUTTON_4_PIN)
#define BTN5_GET					GPIO_ReadInputDataBit(BUTTON_5_PORT, BUTTON_5_PIN)
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
// enum of button
typedef enum
{
	EVENT_OF_BUTTON_NOCLICK,
	EVENT_OF_BUTTON_PRESS_1_TIMES,
	EVENT_OF_BUTTON_PRESS_2_TIMES,
	EVENT_OF_BUTTON_PRESS_3_TIMES,
	EVENT_OF_BUTTON_PRESS_4_TIMES,
	EVENT_OF_BUTTON_PRESS_5_TIMES,
	EVENT_OF_BUTTON_HOLD_500MS,
	EVENT_OF_BUTTON_RELEASED,

}EventButton_e;
typedef enum
{
	NOKEY,
	SELECT,
	SELECT_DOUBLE,
	UP,
	UP_DOUBLE,
	UP_TRIPLE,
	UP_QUADRUPLE,
	UP_QUINTUPLE,
	UP_HOLD,
	DOWN,
	DOWN_DOUBLE,
	DOWN_TRIPLE,
	DOWN_QUADRUPLE,
	DOWN_QUINTUPLE,
	DOWN_HOLD,

	LEFT,
	RIGHT,
	RETURN
}ValueKey_e;

//Struct of button
typedef struct
{
	EventButton_e buttonEven ;
	uint8_t byPressCnt ;
	uint8_t byFlagBtn1Press;
	uint8_t byFlagBtn1Released;
	uint8_t byFlagBtn1Hold;
	uint32_t dwTimeInit;
	uint32_t dwTimeCurrent;
}Button_t;


/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void buttonInit(void);
uint8_t scanButtonStopStart(void);
ValueKey_e processEventButton(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

#endif /* SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_BUTTON_V1_1_BUTTON_V1_1_H_ */
