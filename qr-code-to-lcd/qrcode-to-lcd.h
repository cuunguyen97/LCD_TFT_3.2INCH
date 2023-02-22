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
 * File name: qrcode-to-lcd.h
 *
 * Description:
 *
 * Author: CuuNV
 *
 * Last Changed By:  $Author: CuuNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jan 28, 2023
 *
 * Code sample:
 ******************************************************************************/
#ifndef SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_QR_CODE_TO_LCD_ST7735S_QRCODE_TO_LCD_H_
#define SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_QR_CODE_TO_LCD_ST7735S_QRCODE_TO_LCD_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <qrcode.h>
#include <lcd.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
//1. define for LCD
#define WIDTH_LCD			240u
#define HEIGHT_LCD			240u
#define SCALE_ONE_PIXEL		3

//2. define for Qr_code
	// Level of error correction(0-3): 0~ 7%,1~ 15%, 2 ~25%, 3 ~ 30%
#define ECC_LEVEL			0
	// Version of Qrcode (MAX 6)
#define VERSION_OF_QR		6

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/


uint8_t checkDataLength(uint8_t byDataLength, uint8_t byEccLevel, uint8_t byVersion);
void generateQRCode(u8 byX,u8 byY,char *pByData,uint8_t byDataLength);
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/


#endif /* SDK_1_0_3_NUCLEO_F401RE_SHARED_MIDDLE_QR_CODE_TO_LCD_ST7735S_QRCODE_TO_LCD_H_ */
