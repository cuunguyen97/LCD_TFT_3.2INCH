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
 * File name: led.h
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
#ifndef MIDDLE_LED_LED_H_
#define MIDDLE_LED_LED_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define LED_RED_GPIO		GPIO_Pin_1
#define LED_RED_PORT		GPIOA
#define LED_RED_RCC			RCC_AHB1Periph_GPIOA

#define LED_GREEN_1_GPIO	GPIO_Pin_4
#define LED_GREEN_1_PORT	GPIOA
#define LED_GREEN_1_RCC		RCC_AHB1Periph_GPIOA

#define LED_GREEN_2_GPIO	GPIO_Pin_0
#define LED_GREEN_2_PORT	GPIOB
#define LED_GREEN_2_RCC		RCC_AHB1Periph_GPIOB
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
typedef enum{
STOP,
ERROR_DEVICE,
RUN,
PAUSE
}DeviceState_e;
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void ledInit(void);
/*
 * state->NONE,
		PUSH_UP,
		PUSH_UP_DONE,
		PUSH_DOWN,
		PUSH_DOWN_DONE,
		CHECK_CURRENT_SENSOR
 */
void controlLed(DeviceState_e state);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/


#endif /* MIDDLE_LED_LED_H_ */
