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
 * File name: menu.h
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

#ifndef SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_MENU_MENU_H_
#define SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_MENU_MENU_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <string.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
typedef enum{
	MENU_OPTION,
	INFORMATION_OPTION,
	PREPARE_OPTION,
	SETUP_AND_RUN_OPTION,
	SLEEP_OPTION
}Option_e;
typedef enum{
	NONE_ACTION,
	RETURN_ACTION,
	SELECT_ACTION
}Action_e;
typedef void(*upDateDataStopHandle)(void*);
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
uint8_t processMainMenu(uint32_t dwCountMax,\
						uint32_t dwCounting,\
						uint32_t dwCountMiss,\
						uint32_t Thold);

uint8_t getChooseMainMenu(uint8_t byNumOfRows,\
				uint8_t bySizeOfRow,\
				char pStrInterface[][20],\
				uint8_t bySize);
Action_e getChooseInformation(uint8_t stateRestart);

uint8_t getOptionMainMenu(void);

Action_e getChooseSetAndRun(u32 dwCountMax,\
		u32 dwTimeHold);

Action_e processInfomationOption(uint32_t dwCountMax,\
							uint32_t dwCounting,\
							uint32_t dwCountMiss,\
							uint32_t Thold);

Action_e processPrepareOption(void);

Action_e processSetUpAndRunOption(u32 dwCountMax,\
		u32 dwTimeHold);

void HMI(uint32_t dwCountMax,\
		uint32_t dwCounting,\
		uint32_t dwCountMiss,\
		uint32_t Thold,\
		uint8_t State);

Action_e processSleepOption(void);

void updateDataStopHandleCallBack(upDateDataStopHandle pHandle);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/


#endif /* SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_MENU_MENU_H_ */
