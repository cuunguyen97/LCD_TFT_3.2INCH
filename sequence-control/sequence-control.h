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
 * File name: sequence-control.h
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
#ifndef MIDDLE_SEQUENCE_CONTROL_SEQUENCE_CONTROL_H_
#define MIDDLE_SEQUENCE_CONTROL_SEQUENCE_CONTROL_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define BW2CHANGE_STATE_TIME 			500u
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
typedef enum{
PUSH_UP,
PUSH_UP_DONE,
PUSH_DOWN,
PUSH_DOWN_DONE,
CHECK_CURRENT_SENSOR
}EventProcessDevice_e;
typedef void(*upDateDataRunHandle)(void*);
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


#endif /* MIDDLE_SEQUENCE_CONTROL_SEQUENCE_CONTROL_H_ */
