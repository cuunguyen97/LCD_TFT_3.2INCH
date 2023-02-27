
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
#include <GUI.h>
#include <lcd.h>
#include <button-v1-1.h>
#include <menu.h>
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
TestSwMode_e getModeTest(void);

uint8_t getChooseRows(uint8_t byNumOfRows,\
				uint8_t bySizeOfRow,\
				char pStrInterface[][20],\
				uint8_t bySize);
void prinfPoint(uint8_t bySizeOfRows,\
		uint8_t byChooseRow,\
		uint8_t bySize,\
		ValueKey_e key);


/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
TestSwMode_e getModeTest(void)
{
	TestSwMode_e modeTemp;
	uint8_t byChooseRow = 0;
	while(byChooseRow == 0)
	{
		byChooseRow = getChooseRows(3, 20, pMenuMain, 16);
	}

	//lcdPrintText(pMenuMain[byChooseRow], 0, 15, ucg_font_10x20_mr);
	switch(byChooseRow)
	{
	case 1:
		byChooseRow = 0;
		modeTemp = DUAL_MODE;
		break;
	case 2:
		byChooseRow = 0;
		modeTemp = ZIGBEE_MODE;
		break;
	case 3:
		byChooseRow = 0;
		modeTemp = BLE_MODE;
		break;
	default:
		break;
	}
	return modeTemp;

}
uint8_t getChooseRows(uint8_t byNumOfRows,\
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
		LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp],230,cursorOfOptionBox[byRowTemp]+bySizeOfRow);
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
			LCD_DrawRectangle(10,cursorOfOptionBox[0],230,cursorOfOptionBox[0]+bySizeOfRow);
		}else
		{
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp+1],230,cursorOfOptionBox[byRowTemp+1]+bySizeOfRow);
		}
		LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp],230,cursorOfOptionBox[byRowTemp]+bySizeOfRow);
		key = NOKEY;
		break;
	case DOWN:
		byRowTemp++;
		if(byRowTemp == byNumOfRows)
		{
			byRowTemp = 0;
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[byNumOfRows-1],230,cursorOfOptionBox[byNumOfRows-1]+bySizeOfRow);
		}else
		{
			LCD_SetColorPoint(CYAN);
			LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp-1],230,cursorOfOptionBox[byRowTemp-1]+bySizeOfRow);
		}
		LCD_DrawRectangle(10,cursorOfOptionBox[byRowTemp],230,cursorOfOptionBox[byRowTemp]+bySizeOfRow);
		key = NOKEY;
		break;
	case SELECT:
		//lcdClear();
		LCD_Fill(10, cursorOfOptionBox[byRowTemp], 230, cursorOfOptionBox[byRowTemp], RED);
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
void prinfPoint(uint8_t bySizeOfRows,\
		uint8_t byChooseRow,\
		uint8_t bySize,\
		ValueKey_e key)
{

	if(key == UP)
	{

	}else if(key == DOWN)
	{
		//lcdPrintText(" ", 110, bySizeOfRows * (byChooseRow-1), font);
		//lcdPrintText("<", 110, byChooseRow*bySizeOfRows, font);

	}

}
/******************************************************************************/
