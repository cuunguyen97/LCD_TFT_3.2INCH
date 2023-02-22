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
 * File name: serial-uart.h
 *
 * Description:
 *
 * Author: CuuNV
 *
 * Last Changed By:  $Author: CuuNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Feb 21, 2023
 *
 * Code sample:
 ******************************************************************************/

#ifndef MIDDLE_SERIAL_UART_SERIAL_UART_H_
#define MIDDLE_SERIAL_UART_SERIAL_UART_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stm32f401re_rcc.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_usart.h>
#include <buff.h>
#include <misc.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
//define of USART6
#define USART6_BAUDRATE			115200
#define USART6_PIN_RX			GPIO_Pin_12
#define USART6_PINSOURCE_RX		GPIO_PinSource12
#define USART6_PORT				GPIOA
#define USART6_GPIO_RCC			RCC_AHB1Periph_GPIOA
#define USART6_RCC				RCC_APB2Periph_USART6
#define USART6_AF				GPIO_AF_USART6

//define of serial
#define BYTE_START_1							0x4C
#define BYTE_START_2							0x4D
//define of other
#define SIZE_BUFF_DATA_RX		256
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

// enum of uart
typedef enum {
	RX_STATE_START_1_BYTE,
	RX_STATE_START_2_BYTE,
	RX_STATE_DATA_BYTES,
	RX_STATE_CXOR_BYTE
}RxState_e;
typedef enum {
	UART_STATE_IDLE,
	UART_STATE_DATA_RECEIVED,
	UART_STATE_ACK_RECEIVED,
	UART_STATE_NACK_RECEIVED,
	UART_STATE_ERROR,
	UART_STATE_RX_TIMEOUT
}UsartState_e;



typedef void (* serial_handle_event)(void *);
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void SerialHandleEventCallback(serial_handle_event pSerialEvent);
void serialUartInit(void);
void processSerialUartReceiver(void);
void resetBuffer(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

#endif /* MIDDLE_SERIAL_UART_SERIAL_UART_H_ */
