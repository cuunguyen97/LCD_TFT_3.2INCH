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
 *
 * Description:
 *
 * Author: CuuNV
 *
 * Last Changed By:  $Author: CuuNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Mar 1, 2023
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f401re_gpio.h"
#include "stm32f401re_rcc.h"
#include "led.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

void controlLed(DeviceState_e state)
{
	switch(state)
	{
	case PAUSE:
		GPIO_SetBits(LED_GREEN_1_PORT,LED_GREEN_1_GPIO);
		GPIO_ResetBits(LED_RED_PORT, LED_RED_GPIO);
		GPIO_ResetBits(LED_GREEN_2_PORT, LED_GREEN_2_GPIO);
		break;
	case RUN:
		GPIO_SetBits(LED_GREEN_2_PORT,LED_GREEN_2_GPIO);
		GPIO_ResetBits(LED_RED_PORT, LED_RED_GPIO);
		GPIO_ResetBits(LED_GREEN_1_PORT, LED_GREEN_1_GPIO);
		break;
	case STOP:
		GPIO_SetBits(LED_RED_PORT,LED_RED_GPIO);
		GPIO_SetBits(LED_GREEN_2_PORT, LED_GREEN_2_GPIO);
		GPIO_SetBits(LED_GREEN_1_PORT, LED_GREEN_1_GPIO);
		break;
	default:
		GPIO_ResetBits(LED_RED_PORT, LED_RED_GPIO);
		GPIO_ResetBits(LED_GREEN_2_PORT, LED_GREEN_2_GPIO);
		GPIO_ResetBits(LED_GREEN_1_PORT, LED_GREEN_1_GPIO);
		break;
	}
}
void ledInit(void)
{
	GPIO_InitTypeDef GpioInitStruct;
	RCC_AHB1PeriphClockCmd(LED_GREEN_1_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(LED_RED_RCC, ENABLE);

	GpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GpioInitStruct.GPIO_OType = GPIO_OType_PP;
	GpioInitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GpioInitStruct.GPIO_Pin = LED_RED_GPIO;
	GPIO_Init(LED_RED_PORT, &GpioInitStruct);

	GpioInitStruct.GPIO_Pin = LED_GREEN_1_GPIO;
	GPIO_Init(LED_GREEN_1_PORT, &GpioInitStruct);

	GpioInitStruct.GPIO_Pin = LED_GREEN_2_GPIO;
	GPIO_Init(LED_GREEN_2_PORT, &GpioInitStruct);
}
