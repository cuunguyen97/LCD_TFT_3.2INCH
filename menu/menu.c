
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
 * File name: menu.c
 *
 * Description:
 *
 * Author: CuuNV
 *
 * Last Changed By:  $Author: CuuNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Feb 10, 2023
 *
 * Code sample:
 ******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <button-v1-1.h>
#include <GUI.h>
#include <stdio.h>
#include <lcd.h>
#include <led.h>
#include <valve.h>
#include <current-sensor.h>
#include <proximity-sensor.h>
#include <menu.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static upDateDataStopHandle pUpdateDataStopHandle;


static u32 pData[5];
//-------------------------------MENU LEVEL 1----------------------------------
static char pMenuMain[5][20] = {
		"MENU",
		"Information",
		"Prepare",
		"Setup&Run",
		"Sleep"
};
//-------------------------------MENU LEVEL 2----------------------------------

//-------------------------------MENU LEVEL 3----------------------------------
Action_e action = NONE_ACTION;
static Option_e option = MENU_OPTION;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void HMI(uint32_t dwCountMax,\
		uint32_t dwCounting,\
		uint32_t dwCountMiss,\
		uint32_t Thold,\
		uint8_t State);

uint8_t processMainMenu(uint32_t dwCountMax,\
						uint32_t dwCounting,\
						uint32_t dwCountMiss,\
						uint32_t Thold);

uint8_t getChooseMainMenu(uint8_t byNumOfRows,\
				uint8_t bySizeOfRow,\
				char pStrInterface[][20],\
				uint8_t bySize);
Action_e getChooseInformation(uint8_t stateRestart);

Action_e getChoosePrepare(void);

Action_e getChooseSetAndRun(u32 dwCountMax,\
		u32 dwTimeHold);

uint8_t getOptionMainMenu(void);

Action_e processInfomationOption(uint32_t dwCountMax,\
							uint32_t dwCounting,\
							uint32_t dwCountMiss,\
							uint32_t Thold);

Action_e processPrepareOption(void);

Action_e processSetUpAndRunOption(u32 dwCountMax,\
		u32 dwTimeHold);

Action_e processSleepOption(void);

void updateDataStopHandleCallBack(upDateDataStopHandle pHandle);

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
void updateDataStopHandleCallBack(upDateDataStopHandle pHandle)
{
	pUpdateDataStopHandle = pHandle;
}

void HMI(uint32_t dwCountMax,\
		uint32_t dwCounting,\
		uint32_t dwCountMiss,\
		uint32_t Thold,\
		uint8_t State)
{
	//ValueKey_e key = NOKEY ;
	static u8 Flag = 0;
	const u16 lengthNum = 10;
	const u16 size = 16;
	const u16 widthStr = 100;
	u16 widthBox = lengthNum*(size/2);
	const u16 heightBox = 20;

	const u16 xEditNumCntMax = 70;
	const u16 yEditNumCntMax = 50;
	const u16 xEditNumThold = 70;
	const u16 yEditNumThold = 80;

	const u16 xEditNumCntMiss = 70;
	const u16 yEditNumCntMiss = 110;
	const u16 xEditNumCnting = 70;
	const u16 yEditNumCnting = 140;


	u16 XsBoxCntMax = xEditNumCntMax + widthStr -1;
	u16 YsBoxCntMax = yEditNumCntMax -1;
	u16 XeBoxCntMax = XsBoxCntMax + widthBox;
	u16 YeBoxCntMax = YsBoxCntMax + heightBox;

	u16 XsBoxThold = xEditNumThold + widthStr -1;
	u16 YsBoxThold = yEditNumThold - 1;
	u16 XeBoxThold = XsBoxThold + widthBox;
	u16 YeBoxThold = YsBoxThold + heightBox;

	u16 XsBoxCnting = xEditNumCnting + widthStr -1;
	u16 YsBoxCnting = yEditNumCnting - 1;
	u16 XeBoxCnting = XsBoxCnting + widthBox;
	u16 YeBoxCnting = YsBoxCnting + heightBox;

	u16 XsBoxCntMiss = xEditNumCntMiss + widthStr -1;
	u16 YsBoxCntMiss = yEditNumCntMiss - 1;
	u16 XeBoxCntMiss = XsBoxCntMiss + widthBox;
	u16 YeBoxCntMiss = YsBoxCntMiss + heightBox;

	u16 XsBoxProcess = 5;
	u16 YsBoxProcess = YeBoxCnting +20;
	u16 XeBoxProcess = 315;
	u16 YeBoxProcess = YsBoxProcess + heightBox;

	u16 XsUpdateBoxProcess = XsBoxProcess + 5;
	u16 YsUpdateBoxProcess = YsBoxProcess + 5;
	static u16 XeUpdateBoxProcess ;
	u16 YeUpdateBoxProcess = YeBoxProcess - 5;

	const u16 widthProcess1Unit = 3;

	u16 valuePosition = 0,ratioProcess = 0;
	static u16 lastRatioProcess = 0;
	if(State == 0 && Flag == 0)
		{
			LCD_Clear(WHITE);
			//Print Titel
			LCD_ShowTitle(heightBox, WHITE, BLUE, (u8*)"TEST JIG SOCKET", 16, 1);
			LCD_ShowEditNum(xEditNumCntMax, yEditNumCntMax,(u8*)"Count Max", lengthNum);
			LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMax);
			LCD_ShowEditNum(xEditNumThold, yEditNumThold,(u8*)"Time Hold", lengthNum);
			LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, Thold);

			LCD_ShowEditNum(xEditNumCnting, yEditNumCnting,(u8*)"Counting", lengthNum);
			LCD_UpdateEditNum(XsBoxCnting, YsBoxCnting, XeBoxCnting, YeBoxCnting, dwCounting);
			LCD_ShowEditNum(xEditNumCntMiss, yEditNumCntMiss,(u8*)"Count Miss", lengthNum);
			LCD_UpdateEditNum(XsBoxCntMiss, YsBoxCntMiss, XeBoxCntMiss, YeBoxCntMiss, dwCountMiss);

			LCD_DrawRectangle(XsBoxProcess,YsBoxProcess,XeBoxProcess,YeBoxProcess);
			LCD_Fill(XsUpdateBoxProcess, YsUpdateBoxProcess, XeBoxProcess - 5, YeUpdateBoxProcess, WHITE);
			LCD_ShowNum(XeBoxProcess-5*8, YeBoxProcess+10, 0, 3, 16);
			LCD_ShowString(XeBoxProcess-3*8, YeBoxProcess+10, 16,(u8*) "%", 1);
			//LCD_ShowChar(XeBoxProcess-3*8, YeBoxProcess+10, BLACK, WHITE, 37, 16, 1);
			lastRatioProcess = 0;
			XeUpdateBoxProcess = XsUpdateBoxProcess;
			Flag = 1;
		}
	if(State == 1)
	{
			//LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMax);
			LCD_UpdateEditNum(XsBoxCnting, YsBoxCnting, XeBoxCnting, YeBoxCnting, dwCounting);
			LCD_UpdateEditNum(XsBoxCntMiss, YsBoxCntMiss, XeBoxCntMiss, YeBoxCntMiss, dwCountMiss);
			//LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, Thold);
			Flag = 0;

			//Update process
			ratioProcess = (u16)(dwCounting*100/(dwCountMax));
			LCD_ShowNum(XeBoxProcess-3*8, YeBoxProcess+10, ratioProcess, 3, 16);
			if(lastRatioProcess != ratioProcess)
			{
				valuePosition = ratioProcess - lastRatioProcess;
				valuePosition *= widthProcess1Unit;
				XeUpdateBoxProcess += valuePosition ;
				LCD_Fill(XsUpdateBoxProcess, YsUpdateBoxProcess, XeUpdateBoxProcess, YeUpdateBoxProcess, BLACK);
				LCD_ShowNum(XeBoxProcess-3*8, YeBoxProcess+10, ratioProcess, 3, 16);
				lastRatioProcess = ratioProcess;

			}



	}

}
uint8_t processMainMenu(uint32_t dwCountMax,\
						uint32_t dwCounting,\
						uint32_t dwCountMiss,\
						uint32_t Thold)
{
	uint8_t state = 0;
	uint8_t byOptionChoose = 0;


	switch(option)
	{
	case MENU_OPTION:
		byOptionChoose = getOptionMainMenu();
		if( byOptionChoose == 1)
		{
			option = INFORMATION_OPTION;
		}else if(byOptionChoose == 2)
		{
			option = PREPARE_OPTION;
		}else if(byOptionChoose == 3)
		{
			option = SETUP_AND_RUN_OPTION;
		}else if(byOptionChoose == 4)
		{
			option = SLEEP_OPTION;
		}else
		{
			option = MENU_OPTION;
		}
		break;
	case INFORMATION_OPTION:
		action = processInfomationOption(dwCountMax,dwCounting,dwCountMiss,Thold);
		if(action == RETURN_ACTION)
		{
			option = MENU_OPTION;
		}
		if(action == SELECT_ACTION)
		{
			//Restart
			option = MENU_OPTION;
			state = 1;
		}
		break;
	case PREPARE_OPTION:
		action = processPrepareOption();
		if(action == RETURN_ACTION)
		{
			option = MENU_OPTION;
		}else if(action == SELECT_ACTION)
		{
			//save&run
			option = MENU_OPTION;
			state = 1;
		}else
		{
			option = PREPARE_OPTION;
		}
		break;
	case SETUP_AND_RUN_OPTION:
		action = processSetUpAndRunOption(dwCountMax,Thold);
		if(action == RETURN_ACTION)
		{
			option = MENU_OPTION;
		}else if(action == SELECT_ACTION)
		{
			//save&run
			option = MENU_OPTION;
			state = 1;
		}else
		{
			option = SETUP_AND_RUN_OPTION;
		}
		break;
	case SLEEP_OPTION:
		action = processSleepOption();
		if(action == SELECT_ACTION)
		{
			//
			option = SLEEP_OPTION;
		}else
		{
			option = MENU_OPTION;
		}
		state = 1;
		break;
	default:
		option = MENU_OPTION;
		break;
	}

	return state;
}

uint8_t getOptionMainMenu(void)
{
	uint8_t byOption = 0;
	while(byOption == 0)
	{
		byOption = getChooseMainMenu(4, 20, pMenuMain, 16);
	}
	return byOption;
}
Action_e processInfomationOption(uint32_t dwCountMax,\
							uint32_t dwCounting,\
							uint32_t dwCountMiss,\
							uint32_t Thold)
{
	Action_e action = NONE_ACTION;
	//void LCD_ShowNumAndStr(u16 x,u16 y,u8 size,char *pStr1,u8 lengthStr,u32 num,u8 lengthNum,u8 mode)
	LCD_ShowStrAndStr(20, 40, 16, "NAME", 150, "VALUE", 64, 1);
	LCD_ShowNumAndStr(20, 60,16,"COUNT_MAX  ",150,dwCountMax,64,1);
	LCD_ShowNumAndStr(20, 80,16,"COUTING    ",150,dwCounting,64,1);
	LCD_ShowNumAndStr(20, 100,16,"COUNTMISS  ",150,dwCountMiss,64,1);
	LCD_ShowNumAndStr(20, 120,16,"T_HOLD     ",150,Thold,64,1);
	if(dwCounting<dwCountMax)
	{
		action = getChooseInformation(1);
	}else
	{
		action = getChooseInformation(0);
	}
	//In ra thong tin da luu
	//Get tuy chon Restart/Return

	return action;
}
Action_e processPrepareOption(void)
{
	Action_e action = NONE_ACTION;
	Show_Str(20, 25, BLACK, GREEN, (u8*)"SENSOR", 16, 1);
	LCD_DrawLine(20, 50, 220, 50);

	LCD_DrawLine(220, 20, 220, 240);


	while(action == NONE_ACTION)
	{
		action = getChoosePrepare();
	}
	return action;
}
Action_e processSetUpAndRunOption(u32 dwCountMax,\
		u32 dwTimeHold)
{
	Action_e action = NONE_ACTION;
	while(action == NONE_ACTION)
	{
		action = getChooseSetAndRun(dwCountMax,dwTimeHold);
	}
	return action;
}
Action_e processSleepOption(void)
{
	Action_e action = NONE_ACTION;
	while(action == NONE_ACTION)
	{
		action = getChooseMainMenu(4, 20, pMenuMain, 16);
	}

	return action;
}
Action_e getChooseSetAndRun(u32 dwCountMax,\
		u32 dwTimeHold)
{
	Action_e action = NONE_ACTION;
	static u8 flag = 0;
	static u8 Row = 0;
	u16 lengthNum = 10;
	u16 size = 16;
	u16 widthStr = 100;
	u16 widthBox = lengthNum*(size/2);
	u16 heightBox = 20;

	u16 heightButton = 20;
	u16 widthButton = 120;


	u16 heightButtonUpDown = 50;
	u16 widthButtonUpDown = 30;
	//Position of Button,edit-Number
	u16 xEditNumCntMax = 70;
	u16 yEditNumCntMax = 53;

	u16 xEditNumThold = 70;
	u16 yEditNumThold = 120;

	u16 XsButtonRun = 320/2 - (widthButton/2);
	u16 YsButtonRun = 240-(heightButton*2+20+10);



	u16 XsBoxCntMax = xEditNumCntMax + widthStr -1;
	u16 YsBoxCntMax = yEditNumCntMax -1;
	u16 XeBoxCntMax = XsBoxCntMax + widthBox;
	u16 YeBoxCntMax = YsBoxCntMax + heightBox;

	u16 XsBoxThold = xEditNumThold + widthStr -1;
	u16 YsBoxThold = yEditNumThold - 1;
	u16 XeBoxThold = XsBoxThold + widthBox;
	u16 YeBoxThold = YsBoxThold + heightBox;

	u16 XeButtonRun = XsButtonRun + widthButton;
	u16 YeButtonRun = YsButtonRun + heightButton;

	u16 XsButtonReturn = XsButtonRun;
	u16 XeButtonReturn = XsButtonReturn + widthButton;
	u16 YsButtonReturn = YeButtonRun  + 20;
	u16 YeButtonReturn = YsButtonReturn + heightButton;

	u16 XsButtonUpDownCntMax = XeBoxCntMax+10;
	u16 YsButtonUpDownCntMax = YeBoxCntMax-heightBox/2-heightButtonUpDown/2;
	u16 XeButtonUpDownCntMax = XsButtonUpDownCntMax + widthButtonUpDown;
	u16 YeButtonUpDownCntMax = YsButtonUpDownCntMax + heightButtonUpDown;

	u16 XsButtonUpDownTimeHold = XeBoxThold+10;
	u16 YsButtonUpDownTimeHold = YeBoxThold-heightBox/2-heightButtonUpDown/2;
	u16 XeButtonUpDownTimeHold = XsButtonUpDownTimeHold + widthButtonUpDown;
	u16 YeButtonUpDownTimeHold = YsButtonUpDownTimeHold + heightButtonUpDown;

	key_t key = NOKEY;
	static u32 dwCountMaxTemp;
	dwCountMaxTemp = dwCountMax;
	static u32 dwTimeHoldTemp;
	dwTimeHoldTemp = dwTimeHold;

	if(flag == 0)
	{
		LCD_ShowEditNum(xEditNumCntMax, yEditNumCntMax,(u8*)"Count Max", lengthNum);
		LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
		LCD_ShowEditNum(xEditNumThold, yEditNumThold,(u8*)"Time Hold", lengthNum);
		LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
		LCD_ShowButton(XsButtonRun,YsButtonRun,widthButton,heightButton,(u8*)"Save And Run",1);
		LCD_ShowButton(XsButtonReturn,YsButtonReturn,widthButton,heightButton,(u8*)"RETURN",1);

		LCD_DrawLine(20,YeBoxThold-heightBox/2-heightButtonUpDown/2 -10,320-20,YeBoxThold-heightBox/2-heightButtonUpDown/2 -10);

		LCD_ShowBtnUpDown(XsButtonUpDownCntMax,YsButtonUpDownCntMax,widthButtonUpDown,heightButtonUpDown);
		LCD_ShowBtnUpDown(XsButtonUpDownTimeHold,YsButtonUpDownTimeHold,widthButtonUpDown,heightButtonUpDown);
		LCD_DrawLine(20,YsButtonRun-10,320-20,YsButtonRun-10);
		LCD_SetColorPoint(BLUE);
		LCD_DrawRectangle(XsButtonUpDownCntMax-1,YsButtonUpDownCntMax-1,XeButtonUpDownCntMax+1,YeButtonUpDownCntMax+1);

		flag = 1;
	}
	while(key == NOKEY)
	{
		key = processEventButton();
	}
	switch(key)
			{
			case UP:
				Row--;
				if(Row == 255)
				{
					Row = 3;
				}
				if(Row == 0)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonUpDownTimeHold-1,YsButtonUpDownTimeHold-1,XeButtonUpDownTimeHold+1,YeButtonUpDownTimeHold+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonUpDownCntMax-1,YsButtonUpDownCntMax-1,XeButtonUpDownCntMax+1,YeButtonUpDownCntMax+1);
				}
				else if(Row == 1)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonRun-1,YsButtonRun-1,XeButtonRun+1,YeButtonRun+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonUpDownTimeHold-1,YsButtonUpDownTimeHold-1,XeButtonUpDownTimeHold+1,YeButtonUpDownTimeHold+1);
				}else if(Row == 2)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonRun-1,YsButtonRun-1,XeButtonRun+1,YeButtonRun+1);

				}else if(Row == 3)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonUpDownCntMax-1,YsButtonUpDownCntMax-1,XeButtonUpDownCntMax+1,YeButtonUpDownCntMax+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
				}
				key = NOKEY;
				break;
			case DOWN:
				Row++;
				if(Row == 4)
				{
					Row = 0;
				}
				if(Row == 0)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonUpDownCntMax-1,YsButtonUpDownCntMax-1,XeButtonUpDownCntMax+1,YeButtonUpDownCntMax+1);
				}
				else if(Row == 1)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonUpDownCntMax-1,YsButtonUpDownCntMax-1,XeButtonUpDownCntMax+1,YeButtonUpDownCntMax+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonUpDownTimeHold-1,YsButtonUpDownTimeHold-1,XeButtonUpDownTimeHold+1,YeButtonUpDownTimeHold+1);
				}else if(Row == 2)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonUpDownTimeHold-1,YsButtonUpDownTimeHold-1,XeButtonUpDownTimeHold+1,YeButtonUpDownTimeHold+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonRun-1,YsButtonRun-1,XeButtonRun+1,YeButtonRun+1);

				}else if(Row == 3)
				{
					LCD_SetColorPoint(WHITE);
					LCD_DrawRectangle(XsButtonRun-1,YsButtonRun-1,XeButtonRun+1,YeButtonRun+1);
					LCD_SetColorPoint(BLUE);
					LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
				}
				key = NOKEY;
				break;
			case SELECT:

				if(Row == 0)
				{
					LCD_SetColorPoint(GREEN);
					Fill_Triangel(XsButtonUpDownCntMax+widthButtonUpDown/4,\
							YsButtonUpDownCntMax + heightButtonUpDown*2/3, \
							XsButtonUpDownCntMax + widthButtonUpDown/2+widthButtonUpDown/4, \
							YsButtonUpDownCntMax + heightButtonUpDown*2/3, \
							XsButtonUpDownCntMax + widthButtonUpDown/2, \
							YsButtonUpDownCntMax + heightButtonUpDown-3);
					Fill_Triangel(XsButtonUpDownCntMax+widthButtonUpDown/2,\
							YsButtonUpDownCntMax + 3,\
							XsButtonUpDownCntMax + widthButtonUpDown/2+widthButtonUpDown/4, \
							YsButtonUpDownCntMax+heightButtonUpDown/3, \
							XsButtonUpDownCntMax + widthButtonUpDown/4, \
							YsButtonUpDownCntMax+heightButtonUpDown/3);

					do{
						key = processEventButton();
						switch(key)
						{
						case UP:
							dwCountMaxTemp ++;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case UP_DOUBLE:
							dwCountMaxTemp +=10;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case UP_TRIPLE:
							dwCountMaxTemp +=100;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case UP_QUADRUPLE:
							dwCountMaxTemp +=1000;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case UP_QUINTUPLE:
							dwCountMaxTemp +=10000;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case UP_HOLD:
							dwCountMaxTemp ++;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case DOWN:
							dwCountMaxTemp --;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case DOWN_DOUBLE:
							dwCountMaxTemp -=10;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case DOWN_TRIPLE:
							dwCountMaxTemp -=100;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case DOWN_QUADRUPLE:
							dwCountMaxTemp -=1000;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case DOWN_QUINTUPLE:
							dwCountMaxTemp -=10000;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case DOWN_HOLD:
							dwCountMaxTemp --;
							if(dwCountMaxTemp > 99999)
							{
								dwCountMaxTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						case SELECT:
							LCD_SetColorPoint(BLACK);
							Fill_Triangel(XsButtonUpDownCntMax+widthButtonUpDown/4,\
									YsButtonUpDownCntMax + heightButtonUpDown*2/3, \
									XsButtonUpDownCntMax + widthButtonUpDown/2+widthButtonUpDown/4, \
									YsButtonUpDownCntMax + heightButtonUpDown*2/3, \
									XsButtonUpDownCntMax + widthButtonUpDown/2, \
									YsButtonUpDownCntMax + heightButtonUpDown-3);
							Fill_Triangel(XsButtonUpDownCntMax+widthButtonUpDown/2,\
									YsButtonUpDownCntMax + 3,\
									XsButtonUpDownCntMax + widthButtonUpDown/2+widthButtonUpDown/4, \
									YsButtonUpDownCntMax+heightButtonUpDown/3, \
									XsButtonUpDownCntMax + widthButtonUpDown/4, \
									YsButtonUpDownCntMax+heightButtonUpDown/3);
							pData[1] = dwCountMaxTemp;

							break;
						case SELECT_DOUBLE:
							dwCountMaxTemp = 0;
							LCD_UpdateEditNum(XsBoxCntMax, YsBoxCntMax, XeBoxCntMax, YeBoxCntMax, dwCountMaxTemp);
							key = NOKEY;
							break;
						}
					}while(key != SELECT);

					key = NOKEY;

				}else if(Row == 1)
				{
					LCD_SetColorPoint(GREEN);
					Fill_Triangel(XsButtonUpDownTimeHold+widthButtonUpDown/2,\
							YsButtonUpDownTimeHold + 3,\
							XsButtonUpDownTimeHold + widthButtonUpDown/2+widthButtonUpDown/4, \
							YsButtonUpDownTimeHold+heightButtonUpDown/3, \
							XsButtonUpDownTimeHold + widthButtonUpDown/4, \
							YsButtonUpDownTimeHold+heightButtonUpDown/3);
					Fill_Triangel(XsButtonUpDownTimeHold+widthButtonUpDown/4,\
							YsButtonUpDownTimeHold + heightButtonUpDown*2/3, \
							XsButtonUpDownTimeHold + widthButtonUpDown/2+widthButtonUpDown/4, \
							YsButtonUpDownTimeHold + heightButtonUpDown*2/3, \
							XsButtonUpDownTimeHold + widthButtonUpDown/2, \
							YsButtonUpDownTimeHold + heightButtonUpDown-3);

					do{
						key = processEventButton();
						switch(key)
						{
						case UP:
							dwTimeHoldTemp ++;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case UP_DOUBLE:
							dwTimeHoldTemp +=10;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case UP_TRIPLE:
							dwTimeHoldTemp +=100;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case UP_QUADRUPLE:
							dwTimeHoldTemp +=1000;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case UP_QUINTUPLE:
							dwTimeHoldTemp +=10000;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case UP_HOLD:
							dwTimeHoldTemp ++;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 1;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case DOWN:
							dwTimeHoldTemp --;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case DOWN_DOUBLE:
							dwTimeHoldTemp -=10;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case DOWN_TRIPLE:
							dwTimeHoldTemp -=100;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case DOWN_QUADRUPLE:
							dwTimeHoldTemp -=1000;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case DOWN_QUINTUPLE:
							dwTimeHoldTemp -=10000;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case DOWN_HOLD:
							dwTimeHoldTemp --;
							if(dwTimeHoldTemp > 99999)
							{
								dwTimeHoldTemp = 99999;
							}
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						case SELECT:

							LCD_SetColorPoint(BLACK);
							Fill_Triangel(XsButtonUpDownTimeHold+widthButtonUpDown/2,\
									YsButtonUpDownTimeHold + 3,\
									XsButtonUpDownTimeHold + widthButtonUpDown/2+widthButtonUpDown/4, \
									YsButtonUpDownTimeHold+heightButtonUpDown/3, \
									XsButtonUpDownTimeHold + widthButtonUpDown/4, \
									YsButtonUpDownTimeHold+heightButtonUpDown/3);
							Fill_Triangel(XsButtonUpDownTimeHold+widthButtonUpDown/4,\
									YsButtonUpDownTimeHold + heightButtonUpDown*2/3, \
									XsButtonUpDownTimeHold + widthButtonUpDown/2+widthButtonUpDown/4, \
									YsButtonUpDownTimeHold + heightButtonUpDown*2/3, \
									XsButtonUpDownTimeHold + widthButtonUpDown/2, \
									YsButtonUpDownTimeHold + heightButtonUpDown-3);
							pData[4] = dwTimeHoldTemp;
							break;
						case SELECT_DOUBLE:
							dwTimeHoldTemp = 0;
							LCD_UpdateEditNum(XsBoxThold, YsBoxThold, XeBoxThold, YeBoxThold, dwTimeHoldTemp);
							key = NOKEY;
							break;
						}
					}while(key != SELECT);

					key = NOKEY;
				}else if(Row == 2)
				{
					pData[0] = STOP;
					pUpdateDataStopHandle((void*)pData);
					pData[0] = RUN;
					pData[2] = 0;
					pData[3] = 0;
					pUpdateDataStopHandle((void*)pData);
					action = SELECT_ACTION;
					flag = 0;
					Row = 0;
				}
				else
				{
					//pData[0] = STOP;
					//pUpdateDataStopHandle((void*)pData);
					action = RETURN_ACTION;
					flag = 0;
					Row = 0;
				}
				//Print Titel
				key = NOKEY;
				break;
			default:
				break;
			}
	return action;
}
uint8_t getChooseMainMenu(uint8_t byNumOfRows,\
				uint8_t bySizeOfRow,\
				char pStrInterface[][20],\
				uint8_t bySize)
{
	ValueKey_e key = NOKEY ;
	uint8_t byRow = 0;
	static uint8_t byRowTemp = 0;
	static uint8_t byFlag = 0;
	static u16 cursorOfOptionBox[10];
	cursorOfOptionBox[0] = 30;
	if(byFlag == 0)
	{
		LCD_Clear(WHITE);
		//Print Titel
		LCD_ShowTitle(bySizeOfRow, WHITE, BLUE, (u8*)pStrInterface[0], 16, 1);

		for(uint8_t i = 1;i<byNumOfRows+1;i++)
		{
			//print interface
			cursorOfOptionBox[i] = LCD_ShowOption(20, cursorOfOptionBox[i-1], BLACK, CYAN, (u8*)pStrInterface[i], 16, 1);
		}
		LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp],310,cursorOfOptionBox[byRowTemp]+bySizeOfRow);
		byFlag = 1;
	}
	while(key == NOKEY)
	{
		key = processEventButton();
	}
	switch(key)
	{
	case UP:
		byRowTemp--;
		if(byRowTemp == 255)
		{
			byRowTemp = byNumOfRows-1;
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[0],310,cursorOfOptionBox[0]+bySizeOfRow);
		}else
		{
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp+1],310,cursorOfOptionBox[byRowTemp+1]+bySizeOfRow);
		}
		LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp],310,cursorOfOptionBox[byRowTemp]+bySizeOfRow);
		key = NOKEY;
		break;
	case DOWN:
		byRowTemp++;
		if(byRowTemp == byNumOfRows)
		{
			byRowTemp = 0;
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[byNumOfRows-1],310,cursorOfOptionBox[byNumOfRows-1]+bySizeOfRow);
		}else
		{
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp-1],310,cursorOfOptionBox[byRowTemp-1]+bySizeOfRow);
		}
		LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp],310,cursorOfOptionBox[byRowTemp]+bySizeOfRow);
		key = NOKEY;
		break;
	case SELECT:
		//lcdClear();
		LCD_Fill(10, cursorOfOptionBox[byRowTemp], 310, cursorOfOptionBox[byRowTemp], RED);
		LCD_Clear(WHITE);
		//Print Titel
		LCD_ShowTitle(bySizeOfRow, WHITE, BLUE, (u8*)pStrInterface[byRowTemp+1], 16, 1);
		key = NOKEY;
		byFlag = 0;
		byRow = byRowTemp+1;
		break;
	default:
		break;
	}
	return byRow;
}
Action_e getChooseInformation(uint8_t stateRestart)
{
	Action_e action = NONE_ACTION;
	const u16 Xs = 10;
	const u16 Y1 = 180;
	const u16 Y2 = 210;

	static u8 Row = 0,flag = 0;
	ValueKey_e key = NOKEY ;

	if(stateRestart == 0)
	{

		if(flag == 0)
		{
			LCD_ShowOption(20, Y2, BLACK, CYAN, (u8*)"RETURN", 16, 1);
			LCD_DrawRectangle(Xs,Y2,310,Y2+20);
			flag = 1;
		}
		while(key == NOKEY)
		{
			key = processEventButton();
		}
		if(key == SELECT)
		{
			action = RETURN_ACTION;
			flag = 0;
		}
	}else
	{

		if(flag == 0)
		{
			LCD_ShowOption(20, Y1, BLACK, CYAN, (u8*)"RETURN", 16, 1);
			LCD_ShowOption(20, Y2, BLACK, CYAN, (u8*)"RESTART", 16, 1);

			LCD_DrawRectangle(Xs,Y1,320-Xs,Y1+20);
			flag = 1;
		}
		while(key == NOKEY)
		{
			key = processEventButton();
		}
		switch(key)
			{
			case UP:
				Row--;
				if(Row == 255)
				{
					Row = 1;
				}
				if(Row == 1)
				{
					LCD_SetColorPoint(CYAN);
					LCD_DrawRectangle(Xs,Y1,320-Xs,Y1+20);
					LCD_DrawRectangle(Xs,Y2,320-Xs,Y2+20);
				}else
				{
					LCD_SetColorPoint(CYAN);
					LCD_DrawRectangle(Xs,Y2,320-Xs,Y2+20);
					LCD_DrawRectangle(Xs,Y1,320-Xs,Y1+20);
				}
				key = NOKEY;
				break;
			case DOWN:
				Row++;
				if(Row == 2)
				{
					Row = 0;

				}
				if(Row == 1)
				{
					LCD_SetColorPoint(CYAN);
					LCD_DrawRectangle(Xs,Y1,320-Xs,Y1+20);
					LCD_DrawRectangle(Xs,Y2,320-Xs,Y2+20);
				}else
				{
					LCD_SetColorPoint(CYAN);
					LCD_DrawRectangle(Xs,Y2,320-Xs,Y2+20);
					LCD_DrawRectangle(Xs,Y1,320-Xs,Y1+20);
				}
				key = NOKEY;
				break;
			case SELECT:
				if(Row == 0)
				{
					action = RETURN_ACTION;
				}else
				{
					action = SELECT_ACTION;
				}

				flag = 0;
				Row = 0;
				//lcdClear();
				LCD_Clear(WHITE);
				//Print Titel
				key = NOKEY;
				break;
			default:
				break;
			}
	}


	return action;
}
Action_e getChoosePrepare(void)
{
	Action_e action = NONE_ACTION;

	u16 widthButton = 20;
	u16 heigthButton = 80;

	u16 XsButtonValve = 230;
	u16 XeButtonValve = XsButtonValve + heigthButton;
	u16 YsButtonValve = 30;
	u16 YeButtonValve = YsButtonValve + widthButton;

	u16 XsButtonReturn = XsButtonValve;
	u16 XeButtonReturn = XsButtonReturn + heigthButton;
	u16 YsButtonReturn = YeButtonValve  + 20;
	u16 YeButtonReturn = YsButtonReturn + widthButton;


	static u8 flag = 0;
	static u8 Row = 0;
	key_t key = NOKEY;


	static u16 xCurrent,xProHigh,xProLow;
	static eventProximitySensor_e eventProximity;
	static u8 stateCurrentSS = 0;

	u16 yCurrent = 80;
	u16 yProHigh = 130;
	u16 yProLow = 180;
	u16 rCircle = 20;
	if(flag == 0)
	{
		xCurrent = LCD_ShowDevice(20, yCurrent, rCircle, (u8*)"Current: ", 0);
		xProHigh = LCD_ShowDevice(20, yProHigh, rCircle, (u8*)"Proximity High: ", 0);
		xProLow = LCD_ShowDevice(20, yProLow, rCircle, (u8*)"Proximity Low: ", 0);

		LCD_ShowButton(XsButtonValve,YsButtonValve,heigthButton,widthButton,(u8*)"VALVE",GetStateValve());
		LCD_ShowButton(XsButtonReturn,YsButtonReturn,heigthButton,widthButton,(u8*)"RETURN",1);

		LCD_DrawRectangle(XsButtonValve-1,YsButtonValve-1,XeButtonValve+1,YeButtonValve+1);
		flag = 1;
	}
	while(key == NOKEY)
	{
		key = processEventButton();

		//Update State Sensor
			//Current-Sensor
		if(stateCurrentSS != currentSensorScan())
		{
			stateCurrentSS = currentSensorScan();
			if(stateCurrentSS == 0)
			{
				LCD_UpdateDeviceState(xCurrent, yCurrent, rCircle, 0);
			}else
			{
				LCD_UpdateDeviceState(xCurrent, yCurrent, rCircle, 1);
			}
		}
		if(eventProximity !=proximitySensorScan())
		{
			eventProximity = proximitySensorScan();
			if(eventProximity == HIGH_LOCATION)
			{
				LCD_UpdateDeviceState(xProHigh, yProHigh, rCircle, 1);
				LCD_UpdateDeviceState(xProLow, yProLow, rCircle, 0);
			}else if(eventProximity == LOW_LOCATION)
			{
				LCD_UpdateDeviceState(xProHigh, yProHigh, rCircle, 0);
				LCD_UpdateDeviceState(xProLow, yProLow, rCircle, 1);
			}else
			{
				LCD_UpdateDeviceState(xProHigh, yProHigh, rCircle, 0);
				LCD_UpdateDeviceState(xProLow, yProLow, rCircle, 0);
			}
		}

			//Proximity-Sensor

	}
	u8 state;
	switch(key)
		{
		case UP:
			Row--;
			if(Row == 255)
			{
				Row = 1;
			}
			if(Row == 1)
			{
				LCD_SetColorPoint(CYAN);
				LCD_DrawRectangle(XsButtonValve-1,YsButtonValve-1,XeButtonValve+1,YeButtonValve+1);
				LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
			}else
			{
				LCD_SetColorPoint(CYAN);
				LCD_SetColorPoint(CYAN);
				LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
				LCD_DrawRectangle(XsButtonValve-1,YsButtonValve-1,XeButtonValve+1,YeButtonValve+1);

			}
			key = NOKEY;
			break;
		case DOWN:
			Row++;
			if(Row == 2)
			{
				Row = 0;

			}
			if(Row == 1)
			{
				LCD_SetColorPoint(CYAN);
				LCD_DrawRectangle(XsButtonValve-1,YsButtonValve-1,XeButtonValve+1,YeButtonValve+1);
				LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
			}else
			{
				LCD_SetColorPoint(CYAN);
				LCD_SetColorPoint(CYAN);
				LCD_DrawRectangle(XsButtonReturn-1,YsButtonReturn-1,XeButtonReturn+1,YeButtonReturn+1);
				LCD_DrawRectangle(XsButtonValve-1,YsButtonValve-1,XeButtonValve+1,YeButtonValve+1);

			}
			key = NOKEY;
			break;
		case SELECT:

			if(Row == 0)
			{
				state = GetStateValve();
				if(state == PISTON_PUSH_UP)
				{
					//state = PISTON_PUSH_DOWN;
					valveControl(PISTON_PUSH_DOWN,VALVE_NUM_1);
					//Update state on LCD
					LCD_ShowButton(XsButtonValve,YsButtonValve,heigthButton,widthButton,(u8*)"VALVE",1);
				}else
				{
					//state = PISTON_PUSH_UP;
					valveControl(PISTON_PUSH_UP,VALVE_NUM_1);
					LCD_ShowButton(XsButtonValve,YsButtonValve,heigthButton,widthButton,(u8*)"VALVE",0);
				}
			}else
			{
				action = RETURN_ACTION;
				flag = 0;
			}


			Row = 0;

			//Print Titel
			key = NOKEY;
			break;
		default:
			break;
		}
	return action;
}
/******************************************************************************/
