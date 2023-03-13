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
 * File name: sequence-control.c
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
#include "stm32f401re.h"
#include "delay.h"
#include <timer.h>
#include <misc.h>
#include "menu.h"
#include "led.h"
#include "valve.h"
#include "proximity-sensor.h"
#include "current-sensor.h"
#include "sequence-control.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static upDateDataRunHandle pUpdateRunDataHandle;
static EventProcessDevice_e eventDevice = PUSH_UP;
static u32 g_dwCountValue = 0;
static u32 g_dwCountMiss = 0;
static u32 g_dwCountMax = 0;
static u32 g_TimeHold = 0;
static u32 pData[5];
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void setCountValue(u32 countMax,u32 TimeHold);
void updateDataRunHandleCallBack(upDateDataRunHandle pHandle);
u8 byProcessSequenceControl(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
void updateDataRunHandleCallBack(upDateDataRunHandle pHandle)
{
	pUpdateRunDataHandle = pHandle;
}
void setCountValue(u32 countMax,u32 TimeHold)
{
	g_dwCountMax = countMax;
	g_TimeHold = TimeHold;
}
u8 byProcessSequenceControl(void)
{
	u8 state = 0;
	static u32 dwTimeInit = 0,dwTimeCurrent;
	static u8 byFlagTemp = 0;
	static u8 byCountError = 0;
	if(g_dwCountValue <= g_dwCountMax)
	{
		switch(eventDevice)
		{
		case PUSH_UP:
			//Dua piston len cao va luu thoi gian
			pData[0] = RUN;
			pData[2]= g_dwCountValue;
			pData[3]= g_dwCountMiss;
			pUpdateRunDataHandle((void*)pData);
			dwTimeInit = GetMilSecTick();
			valveControl(PISTON_PUSH_UP, VALVE_NUM_1);
			eventDevice = PUSH_UP_DONE;
			break;
		case PUSH_UP_DONE:
			if(proximitySensorScan() == HIGH_LOCATION)
			{
				dwTimeCurrent = GetMilSecTick();
				if(dwCalculatorTime(dwTimeInit, dwTimeCurrent)>g_TimeHold)
				{
					//Bao loi
					eventDevice = PUSH_DOWN;
					dwTimeInit = 0;
					dwTimeCurrent = 0;
				}
			}else
			{
				dwTimeCurrent = GetMilSecTick();
				if(dwCalculatorTime(dwTimeInit, dwTimeCurrent)>g_TimeHold)
				{
					//Bao loi
					dwTimeInit = 0;
					dwTimeCurrent = 0;
					byCountError++;
					eventDevice = PUSH_UP;
					if(byCountError >= 10)
					{
						byCountError = 0;

						state = 1;
					}
				}
			}
			break;
		case PUSH_DOWN:
			//Dua piston Xuong duoi va luu thoi gian
			dwTimeInit = GetMilSecTick();

			valveControl(PISTON_PUSH_DOWN, VALVE_NUM_1);
			eventDevice = PUSH_DOWN_DONE;
			break;
		case PUSH_DOWN_DONE:
			if(proximitySensorScan() == LOW_LOCATION)
			{
				eventDevice = CHECK_CURRENT_SENSOR;
			}else
			{
				dwTimeCurrent = GetMilSecTick();
				if(dwCalculatorTime(dwTimeInit, dwTimeCurrent)>g_TimeHold)
				{
					//Bao loi
					g_dwCountValue++;
					g_dwCountMiss ++;
					byCountError ++;
					dwTimeInit = 0;
					dwTimeCurrent = 0;
					eventDevice = PUSH_UP;
				}
				if(byCountError >= 10)
				{
					byCountError = 0;
					state = 1;
				}
			}
			break;
		case CHECK_CURRENT_SENSOR:

			if(byFlagTemp == 0)
			{
				dwTimeInit = GetMilSecTick();
				byFlagTemp = 1;
			}else
			{
				dwTimeCurrent = GetMilSecTick();

				if(dwCalculatorTime(dwTimeInit, dwTimeCurrent)>g_TimeHold)
				{
					if(currentSensorScan())
					{

					}else
					{
						g_dwCountMiss ++;
					}
					g_dwCountValue++;
					eventDevice = PUSH_UP;
					dwTimeInit = 0;
					dwTimeCurrent = 0;
					byFlagTemp = 0;
				}
			}
			break;
		default:
			eventDevice = PUSH_UP;
			break;
		}
	}else
	{
		g_dwCountMiss = 0;
		g_dwCountValue = 0;
		state = 1;
	}
	return state;
}
