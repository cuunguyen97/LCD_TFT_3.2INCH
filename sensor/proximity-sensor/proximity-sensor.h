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
#ifndef MIDDLE_SENSOR_PROXIMITY_SENSOR_PROXIMITY_SENSOR_H_
#define MIDDLE_SENSOR_PROXIMITY_SENSOR_PROXIMITY_SENSOR_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f401re_gpio.h"
#include "stm32f401re_rcc.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
//Proximity sensor: H-PC6, L-PC8
#define PROXIMITY_SENSOR_1_PIN		GPIO_Pin_6
#define PROXIMITY_SENSOR_2_PIN		GPIO_Pin_8
#define PROXIMITY_SENSOR_PORT		GPIOC
#define PROXIMITY_SENSOR_RCC		RCC_AHB1Periph_GPIOC
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
typedef enum{
ERROR_SENSOR,
HIGH_LOCATION,
LOW_LOCATION,
BW2_LOCATION
}eventProximitySensor_e;
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


#endif /* MIDDLE_SENSOR_PROXIMITY_SENSOR_PROXIMITY_SENSOR_H_ */
