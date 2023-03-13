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
 * File name: Example.h
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

#include "proximity-sensor.h"
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
void proximitySensorInit(void);
eventProximitySensor_e proximitySensorScan(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
void proximitySensorInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(PROXIMITY_SENSOR_RCC, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin  = PROXIMITY_SENSOR_1_PIN|PROXIMITY_SENSOR_2_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(PROXIMITY_SENSOR_PORT, &GPIO_InitStruct);
}
eventProximitySensor_e proximitySensorScan(void)
{
	uint8_t byFlagHighLocation = 0;
	uint8_t byFlagLowLocation = 0;
	eventProximitySensor_e temp;
	if(GPIO_ReadInputDataBit(PROXIMITY_SENSOR_PORT, PROXIMITY_SENSOR_1_PIN))
	{
		byFlagHighLocation = 1;
	}else
		byFlagHighLocation = 0;
	if(GPIO_ReadInputDataBit(PROXIMITY_SENSOR_PORT, PROXIMITY_SENSOR_2_PIN))
	{
		byFlagLowLocation = 1;
	}else
		byFlagLowLocation = 0;
	if(byFlagHighLocation)
	{
		if(byFlagLowLocation)
		{
			temp = ERROR_SENSOR;
		}else
		{
			temp = HIGH_LOCATION;
		}
	}else
	{
		if(byFlagLowLocation)
		{
			temp = LOW_LOCATION;
		}else
		{
			temp = BW2_LOCATION;
		}
	}
	return temp;
}
