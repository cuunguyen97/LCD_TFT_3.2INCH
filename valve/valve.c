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
 * File name: valve.c
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
#include "valve.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static u8 g_stateValve_1 = PISTON_PUSH_UP;
static u8 g_stateValve_2 = PISTON_PUSH_UP;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void valveInit(void);

void valveControl(uint8_t state,uint8_t valveNumber);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
void valveInit(void)
{
	GPIO_InitTypeDef GpioInitStruct;

	RCC_AHB1PeriphClockCmd(VALVE_1_RCC|VALVE_2_RCC, ENABLE);
	GpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GpioInitStruct.GPIO_OType = GPIO_OType_PP;
	GpioInitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GpioInitStruct.GPIO_Pin = VALVE_1_PIN;
	GPIO_Init(VALVE_1_PORT, &GpioInitStruct);

	GpioInitStruct.GPIO_Pin = VALVE_2_PIN;
	GPIO_Init(VALVE_2_PORT, &GpioInitStruct);

}
/*
 * state: DOWN(1),UP(0)
 * valve: VALVE1,VALVE2
 */
void valveControl(uint8_t state,uint8_t valveNumber)
{
	if(valveNumber == VALVE_NUM_1)
	{
		if(state == PISTON_PUSH_DOWN)
		{
			g_stateValve_1 = PISTON_PUSH_DOWN;
			GPIO_SetBits(VALVE_1_PORT, VALVE_1_PIN);
		}else
		{
			g_stateValve_1 = PISTON_PUSH_UP;
			GPIO_ResetBits(VALVE_1_PORT, VALVE_1_PIN);
		}
	}
	if(valveNumber == VALVE_NUM_2)
	{
		if(state == PISTON_PUSH_DOWN)
		{
			g_stateValve_2 = PISTON_PUSH_DOWN;
			GPIO_SetBits(VALVE_2_PORT, VALVE_2_PIN);
		}else
		{
			g_stateValve_2 = PISTON_PUSH_UP;
			GPIO_ResetBits(VALVE_2_PORT, VALVE_2_PIN);
		}
	}
}
u8 GetStateValve(void)
{
	return g_stateValve_1;
}
