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
 * File name: button-v1-1.c
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
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stm32f401re_rcc.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_exti.h>
#include <stm32f401re_syscfg.h>
#include <timer.h>
#include <misc.h>
#include <button-v1-1.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static Button_t button1,button2,button3,button4,button5;


/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void buttonInit(void);

static uint32_t dwCalculatorTime(uint32_t dwTimeInit,uint32_t dwTimeCurrent);

static EventButton_e checkEventButton(u8 pressCnt);

static void GetEventButton(void);

ValueKey_e processEventButton(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

void buttonInit(void)
{
	GPIO_InitTypeDef gpioInitStruct;

	//---------------------------------------------------------------------------B3
	//1. Bat xung clock
	RCC_AHB1PeriphClockCmd(BUTTON_1_2_GPIO_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(BUTTON_3_4_GPIO_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(BUTTON_5_GPIO_RCC, ENABLE);
	//2. Config GPIO
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	gpioInitStruct.GPIO_Pin = BUTTON_1_PIN|BUTTON_2_PIN;
	GPIO_Init(BUTTON_1_2_PORT, &gpioInitStruct);

	gpioInitStruct.GPIO_Pin = BUTTON_3_PIN|BUTTON_4_PIN;
	GPIO_Init(BUTTON_3_4_PORT, &gpioInitStruct);

	gpioInitStruct.GPIO_Pin = BUTTON_5_PIN;
	GPIO_Init(BUTTON_5_PORT, &gpioInitStruct);
}
static uint32_t dwCalculatorTime(uint32_t dwTimeInit,uint32_t dwTimeCurrent)
{
	if(dwTimeCurrent >= dwTimeInit)
	{
		return (dwTimeCurrent - dwTimeInit);
	}else
	{
		return (0xFFFFFFFF + dwTimeCurrent - dwTimeInit);
	}
}
ValueKey_e processEventButton(void)
{
	ValueKey_e valueKeyTemp = NOKEY;

	GetEventButton();

	switch(button1.buttonEven)
	{
	case EVENT_OF_BUTTON_HOLD_500MS:
		valueKeyTemp = RETURN;
		button1.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_1_TIMES:
		valueKeyTemp = SELECT;
		button1.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_2_TIMES:
		valueKeyTemp = UP;
		button1.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_3_TIMES:
		valueKeyTemp = DOWN;
		button1.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	default:
		button1.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	}
	switch(button2.buttonEven)
	{
	case EVENT_OF_BUTTON_HOLD_500MS:

		button2.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_1_TIMES:
		valueKeyTemp = UP;
		button2.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_2_TIMES:

		button2.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_3_TIMES:

		button2.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	default:
		button2.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	}
	switch(button3.buttonEven)
	{
	case EVENT_OF_BUTTON_HOLD_500MS:
		button3.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_1_TIMES:
		valueKeyTemp = DOWN;
		button3.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_2_TIMES:
		button3.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_3_TIMES:
		button3.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	default:
		button3.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	}


	switch(button4.buttonEven)
	{
	case EVENT_OF_BUTTON_HOLD_500MS:
		button4.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_1_TIMES:
		valueKeyTemp = LEFT;
		button4.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_2_TIMES:
		button4.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_3_TIMES:
		button4.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	default:
		button4.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	}
	switch(button5.buttonEven)
	{
	case EVENT_OF_BUTTON_HOLD_500MS:
		button5.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_1_TIMES:
		valueKeyTemp = RIGHT;
		button5.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_2_TIMES:
		button5.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	case EVENT_OF_BUTTON_PRESS_3_TIMES:
		button5.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	default:
		button5.buttonEven = EVENT_OF_BUTTON_NOCLICK;
		break;
	}
	return valueKeyTemp;
}

static void GetEventButton(void)
{

	u32 dwDeltaTime = 0,dwTimeNow;
	dwTimeNow = GetMilSecTick();
	if(button1.buttonEven ==EVENT_OF_BUTTON_NOCLICK)
	{
		//Khi nut nhan duoc nhan
			if(BTN1_GET == 0)
			{
				if(button1.byFlagBtn1Press == 0)
				{
					button1.dwTimeInit = GetMilSecTick();
					button1.byPressCnt++;
					button1.byFlagBtn1Press = 1;
				}

			}
			//Khi nut nhan ko duoc nhan
			if(BTN1_GET!=0)
			{
				if((button1.byFlagBtn1Released == 0)&&(button1.byFlagBtn1Press == 1))
				{
					button1.dwTimeCurrent = GetMilSecTick();
					button1.byFlagBtn1Released = 1;
				}

			}

			//Xu ly khi nhan giu
			if((button1.byFlagBtn1Press == 1 )&&(button1.byFlagBtn1Released == 0))
			{
				dwDeltaTime = dwCalculatorTime(button1.dwTimeInit,dwTimeNow);
				if(dwDeltaTime>BUTTON_LONG_PRESS_TIME)
				{
					button1.buttonEven = EVENT_OF_BUTTON_HOLD_500MS;
					button1.byFlagBtn1Hold = 1;
					button1.byPressCnt = 0;
				}
			}
			//Xu ly khi nhan/nha

			if((button1.byFlagBtn1Press == 1)&&(button1.byFlagBtn1Released == 1))
			{
				if(button1.byFlagBtn1Hold == 1)
				{
					button1.buttonEven = EVENT_OF_BUTTON_NOCLICK;
					button1.byFlagBtn1Press = 0;
					button1.byFlagBtn1Released = 0;
					button1.byFlagBtn1Hold = 0;
				}else
				{
					dwDeltaTime = dwCalculatorTime(button1.dwTimeInit, button1.dwTimeCurrent);
					if((dwDeltaTime > BUTTON_NORMAL_PRESS_TIME)&&(dwDeltaTime < BUTTON_LONG_PRESS_TIME))
					{
							dwDeltaTime = dwCalculatorTime(button1.dwTimeCurrent, dwTimeNow);
						if(dwDeltaTime < BW2PRESS_TIME)
						{
							button1.byFlagBtn1Released = 0;
							button1.byFlagBtn1Press = 0;
						}else
						{
							button1.buttonEven = checkEventButton(button1.byPressCnt);
							button1.byPressCnt = 0;
							button1.byFlagBtn1Press = 0;
							button1.byFlagBtn1Released = 0;
						}
					}
					else if(dwDeltaTime < BUTTON_NORMAL_PRESS_TIME)
					{
						button1.buttonEven = checkEventButton(button1.byPressCnt);
						button1.byPressCnt = 0;
						button1.byFlagBtn1Press = 0;
						button1.byFlagBtn1Released = 0;
					}
				}
			}

			if((button1.byFlagBtn1Hold == 0)&&(button1.byFlagBtn1Press == 0))
			{
					dwDeltaTime = dwCalculatorTime(button1.dwTimeCurrent, dwTimeNow);
					if(dwDeltaTime > BW2PRESS_TIME)
					{
						button1.buttonEven = checkEventButton(button1.byPressCnt);
						button1.byPressCnt = 0;
					}

			}

	}
		dwTimeNow = GetMilSecTick();
		if(button2.buttonEven ==EVENT_OF_BUTTON_NOCLICK)
		{
			//Khi nut nhan duoc nhan
				if(BTN2_GET == 0)
				{
					if(button2.byFlagBtn1Press == 0)
					{
						button2.dwTimeInit = GetMilSecTick();
						button2.byPressCnt++;
						button2.byFlagBtn1Press = 1;
					}

				}
				//Khi nut nhan ko duoc nhan
				if(BTN2_GET!=0)
				{
					if((button2.byFlagBtn1Released == 0)&&(button2.byFlagBtn1Press == 1))
					{
						button2.dwTimeCurrent = GetMilSecTick();
						button2.byFlagBtn1Released = 1;
					}

				}

				//Xu ly khi nhan giu
				if((button2.byFlagBtn1Press == 1 )&&(button2.byFlagBtn1Released == 0))
				{
					dwDeltaTime = dwCalculatorTime(button2.dwTimeInit,dwTimeNow);
					if(dwDeltaTime>BUTTON_LONG_PRESS_TIME)
					{
						button2.buttonEven = EVENT_OF_BUTTON_HOLD_500MS;
						button2.byFlagBtn1Hold = 1;
						button2.byPressCnt = 0;
					}
				}
				//Xu ly khi nhan/nha

				if((button2.byFlagBtn1Press == 1)&&(button2.byFlagBtn1Released == 1))
				{
					if(button2.byFlagBtn1Hold == 1)
					{
						button2.buttonEven = EVENT_OF_BUTTON_NOCLICK;
						button2.byFlagBtn1Press = 0;
						button2.byFlagBtn1Released = 0;
						button2.byFlagBtn1Hold = 0;
					}else
					{
						dwDeltaTime = dwCalculatorTime(button2.dwTimeInit, button2.dwTimeCurrent);
						if((dwDeltaTime > BUTTON_NORMAL_PRESS_TIME)&&(dwDeltaTime < BUTTON_LONG_PRESS_TIME))
						{
								dwDeltaTime = dwCalculatorTime(button2.dwTimeCurrent, dwTimeNow);
							if(dwDeltaTime < BW2PRESS_TIME)
							{
								button2.byFlagBtn1Released = 0;
								button2.byFlagBtn1Press = 0;
							}else
							{
								button2.buttonEven = checkEventButton(button2.byPressCnt);
								button2.byPressCnt = 0;
								button2.byFlagBtn1Press = 0;
								button2.byFlagBtn1Released = 0;
							}
						}
						else if(dwDeltaTime < BUTTON_NORMAL_PRESS_TIME)
						{
							button2.buttonEven = checkEventButton(button2.byPressCnt);
							button2.byPressCnt = 0;
							button2.byFlagBtn1Press = 0;
							button2.byFlagBtn1Released = 0;
						}
					}
				}

				if((button2.byFlagBtn1Hold == 0)&&(button2.byFlagBtn1Press == 0))
				{
					dwDeltaTime = dwCalculatorTime(button2.dwTimeCurrent, dwTimeNow);
					if(dwDeltaTime > BW2PRESS_TIME)
					{
						button2.buttonEven = checkEventButton(button2.byPressCnt);
						button2.byPressCnt = 0;
					}
				}

		}
		dwTimeNow = GetMilSecTick();
		if(button3.buttonEven ==EVENT_OF_BUTTON_NOCLICK)
		{
			//Khi nut nhan duoc nhan
				if(BTN3_GET == 0)
				{
					if(button3.byFlagBtn1Press == 0)
					{
						button3.dwTimeInit = GetMilSecTick();
						button3.byPressCnt++;
						button3.byFlagBtn1Press = 1;
					}

				}
				//Khi nut nhan ko duoc nhan
				if(BTN3_GET!=0)
				{
					if((button3.byFlagBtn1Released == 0)&&(button3.byFlagBtn1Press == 1))
					{
						button3.dwTimeCurrent = GetMilSecTick();
						button3.byFlagBtn1Released = 1;
					}

				}

				//Xu ly khi nhan giu
				if((button3.byFlagBtn1Press == 1 )&&(button3.byFlagBtn1Released == 0))
				{
					dwDeltaTime = dwCalculatorTime(button3.dwTimeInit,dwTimeNow);
					if(dwDeltaTime>BUTTON_LONG_PRESS_TIME)
					{
						button3.buttonEven = EVENT_OF_BUTTON_HOLD_500MS;
						button3.byFlagBtn1Hold = 1;
						button3.byPressCnt = 0;
					}
				}
				//Xu ly khi nhan/nha

				if((button3.byFlagBtn1Press == 1)&&(button3.byFlagBtn1Released == 1))
				{
					if(button3.byFlagBtn1Hold == 1)
					{
						button3.buttonEven = EVENT_OF_BUTTON_NOCLICK;
						button3.byFlagBtn1Press = 0;
						button3.byFlagBtn1Released = 0;
						button3.byFlagBtn1Hold = 0;
					}else
					{
						dwDeltaTime = dwCalculatorTime(button3.dwTimeInit, button3.dwTimeCurrent);
						if((dwDeltaTime > BUTTON_NORMAL_PRESS_TIME)&&(dwDeltaTime < BUTTON_LONG_PRESS_TIME))
						{
								dwDeltaTime = dwCalculatorTime(button3.dwTimeCurrent, dwTimeNow);
							if(dwDeltaTime < BW2PRESS_TIME)
							{
								button3.byFlagBtn1Released = 0;
								button3.byFlagBtn1Press = 0;
							}else
							{
								button3.buttonEven = checkEventButton(button3.byPressCnt);
								button3.byPressCnt = 0;
								button3.byFlagBtn1Press = 0;
								button3.byFlagBtn1Released = 0;
							}
						}
						else if(dwDeltaTime < BUTTON_NORMAL_PRESS_TIME)
						{
							button3.buttonEven = checkEventButton(button3.byPressCnt);
							button3.byPressCnt = 0;
							button3.byFlagBtn1Press = 0;
							button3.byFlagBtn1Released = 0;
						}
					}
				}

				if((button3.byFlagBtn1Hold == 0)&&(button3.byFlagBtn1Press == 0))
				{
					dwDeltaTime = dwCalculatorTime(button3.dwTimeCurrent, dwTimeNow);
					if(dwDeltaTime > BW2PRESS_TIME)
					{
						button3.buttonEven = checkEventButton(button3.byPressCnt);
						button3.byPressCnt = 0;
					}
				}

		}
		dwTimeNow = GetMilSecTick();
		if(button4.buttonEven ==EVENT_OF_BUTTON_NOCLICK)
		{
			//Khi nut nhan duoc nhan
				if(BTN4_GET == 0)
				{
					if(button4.byFlagBtn1Press == 0)
					{
						button4.dwTimeInit = GetMilSecTick();
						button4.byPressCnt++;
						button4.byFlagBtn1Press = 1;
					}

				}
				//Khi nut nhan ko duoc nhan
				if(BTN4_GET!=0)
				{
					if((button4.byFlagBtn1Released == 0)&&(button4.byFlagBtn1Press == 1))
					{
						button4.dwTimeCurrent = GetMilSecTick();
						button4.byFlagBtn1Released = 1;
					}

				}

				//Xu ly khi nhan giu
				if((button4.byFlagBtn1Press == 1 )&&(button4.byFlagBtn1Released == 0))
				{
					dwDeltaTime = dwCalculatorTime(button4.dwTimeInit,dwTimeNow);
					if(dwDeltaTime>BUTTON_LONG_PRESS_TIME)
					{
						button4.buttonEven = EVENT_OF_BUTTON_HOLD_500MS;
						button4.byFlagBtn1Hold = 1;
						button4.byPressCnt = 0;
					}
				}
				//Xu ly khi nhan/nha

				if((button4.byFlagBtn1Press == 1)&&(button4.byFlagBtn1Released == 1))
				{
					if(button4.byFlagBtn1Hold == 1)
					{
						button4.buttonEven = EVENT_OF_BUTTON_NOCLICK;
						button4.byFlagBtn1Press = 0;
						button4.byFlagBtn1Released = 0;
						button4.byFlagBtn1Hold = 0;
					}else
					{
						dwDeltaTime = dwCalculatorTime(button4.dwTimeInit, button4.dwTimeCurrent);
						if((dwDeltaTime > BUTTON_NORMAL_PRESS_TIME)&&(dwDeltaTime < BUTTON_LONG_PRESS_TIME))
						{
								dwDeltaTime = dwCalculatorTime(button4.dwTimeCurrent, dwTimeNow);
							if(dwDeltaTime < BW2PRESS_TIME)
							{
								button4.byFlagBtn1Released = 0;
								button4.byFlagBtn1Press = 0;
							}else
							{
								button4.buttonEven = checkEventButton(button4.byPressCnt);
								button4.byPressCnt = 0;
								button4.byFlagBtn1Press = 0;
								button4.byFlagBtn1Released = 0;
							}
						}
						else if(dwDeltaTime < BUTTON_NORMAL_PRESS_TIME)
						{
							button4.buttonEven = checkEventButton(button4.byPressCnt);
							button4.byPressCnt = 0;
							button4.byFlagBtn1Press = 0;
							button4.byFlagBtn1Released = 0;
						}
					}
				}

				if((button4.byFlagBtn1Hold == 0)&&(button4.byFlagBtn1Press == 0))
				{
					dwDeltaTime = dwCalculatorTime(button4.dwTimeCurrent, dwTimeNow);
					if(dwDeltaTime > BW2PRESS_TIME)
					{
						button4.buttonEven = checkEventButton(button4.byPressCnt);
						button4.byPressCnt = 0;
					}
				}

		}
		dwTimeNow = GetMilSecTick();
		if(button5.buttonEven ==EVENT_OF_BUTTON_NOCLICK)
		{
			//Khi nut nhan duoc nhan
				if(BTN5_GET == 0)
				{
					if(button5.byFlagBtn1Press == 0)
					{
						button5.dwTimeInit = GetMilSecTick();
						button5.byPressCnt++;
						button5.byFlagBtn1Press = 1;
					}

				}
				//Khi nut nhan ko duoc nhan
				if(BTN5_GET!=0)
				{
					if((button5.byFlagBtn1Released == 0)&&(button5.byFlagBtn1Press == 1))
					{
						button5.dwTimeCurrent = GetMilSecTick();
						button5.byFlagBtn1Released = 1;
					}

				}

				//Xu ly khi nhan giu
				if((button5.byFlagBtn1Press == 1 )&&(button5.byFlagBtn1Released == 0))
				{
					dwDeltaTime = dwCalculatorTime(button5.dwTimeInit,dwTimeNow);
					if(dwDeltaTime>BUTTON_LONG_PRESS_TIME)
					{
						button5.buttonEven = EVENT_OF_BUTTON_HOLD_500MS;
						button5.byFlagBtn1Hold = 1;
						button5.byPressCnt = 0;
					}
				}
				//Xu ly khi nhan/nha

				if((button5.byFlagBtn1Press == 1)&&(button5.byFlagBtn1Released == 1))
				{
					if(button5.byFlagBtn1Hold == 1)
					{
						button5.buttonEven = EVENT_OF_BUTTON_NOCLICK;
						button5.byFlagBtn1Press = 0;
						button5.byFlagBtn1Released = 0;
						button5.byFlagBtn1Hold = 0;
					}else
					{
						dwDeltaTime = dwCalculatorTime(button5.dwTimeInit, button5.dwTimeCurrent);
						if((dwDeltaTime > BUTTON_NORMAL_PRESS_TIME)&&(dwDeltaTime < BUTTON_LONG_PRESS_TIME))
						{
								dwDeltaTime = dwCalculatorTime(button5.dwTimeCurrent, dwTimeNow);
							if(dwDeltaTime < BW2PRESS_TIME)
							{
								button5.byFlagBtn1Released = 0;
								button5.byFlagBtn1Press = 0;
							}else
							{
								button5.buttonEven = checkEventButton(button5.byPressCnt);
								button5.byPressCnt = 0;
								button5.byFlagBtn1Press = 0;
								button5.byFlagBtn1Released = 0;
							}
						}
						else if(dwDeltaTime < BUTTON_NORMAL_PRESS_TIME)
						{
							button5.buttonEven = checkEventButton(button5.byPressCnt);
							button5.byPressCnt = 0;
							button5.byFlagBtn1Press = 0;
							button5.byFlagBtn1Released = 0;
						}
					}
				}

				if((button5.byFlagBtn1Hold == 0)&&(button5.byFlagBtn1Press == 0))
				{
					dwDeltaTime = dwCalculatorTime(button5.dwTimeCurrent, dwTimeNow);
					if(dwDeltaTime > BW2PRESS_TIME)
					{
						button5.buttonEven = checkEventButton(button5.byPressCnt);
						button5.byPressCnt = 0;
					}
				}

		}

}

static EventButton_e checkEventButton(u8 pressCnt)
{
	EventButton_e event;
	switch(pressCnt)
	{
	case 1:
		event = EVENT_OF_BUTTON_PRESS_1_TIMES;
		break;
	case 2:
		event = EVENT_OF_BUTTON_PRESS_2_TIMES;
		break;
	case 3:
		event = EVENT_OF_BUTTON_PRESS_3_TIMES;
		break;
	default:
		event = EVENT_OF_BUTTON_NOCLICK;
		break;
	}
	return event;
}
/******************************************************************************/
