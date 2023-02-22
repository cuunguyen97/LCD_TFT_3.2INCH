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
 * File name: serial-uart.c
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
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include <serial-uart.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define RX_MAX_INDEX_BYTE	256
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static serial_handle_event pSerialHandleEvent;

static RxState_e g_eRxState = RX_STATE_START_1_BYTE;
static uint8_t g_pbyRxDataByte[RX_MAX_INDEX_BYTE];
static uint8_t g_byRxCheckXor;
static uint8_t g_byRxIndexByte;
static uint8_t g_byRxNumByte;

static uint8_t g_pBuffDataRx[SIZE_BUFF_DATA_RX] = {0};
static buffqueue_t g_pUartRxQueue = {0};
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
void SerialHandleEventCallback(serial_handle_event pSerialEvent);
void serialUartInit(void);
static UsartState_e PollRxBuff(void);
void processSerialUartReceiver(void);
void resetBuffer(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
void resetBuffer(void)
{
	uint8_t temp;
	while((bufNumItems(&g_pUartRxQueue) !=0))
	{
		bufDeDat(&g_pUartRxQueue, &temp);
	};
}
/**
 * @func   processSerialUartReceiver
 * @brief  Xu ly ban tin nhan duoc tu UART
 * @param  None
 * @retval None
 */
void processSerialUartReceiver(void)
{
	static UsartState_e uartState;
	uartState = PollRxBuff();

	if(uartState != UART_STATE_IDLE)
	{
		switch(uartState)
		{
		case UART_STATE_DATA_RECEIVED:
		{
			pSerialHandleEvent((void *)&g_pbyRxDataByte[1]);
			g_eRxState = RX_STATE_START_1_BYTE;
			break;
		}
		case UART_STATE_ERROR:
			uartState = UART_STATE_IDLE;
			g_eRxState = RX_STATE_START_1_BYTE;
			break;
		default:
			break;
		}
	}
}
/**
 * @func   PollRxBuff
 * @brief  Phan tich ban tin UART nhan duoc, loai bo cac ban tin loi.
 * @param  void *arg
 * @retval None
 */
static UsartState_e PollRxBuff(void)
{
	//1. Khai bao bien chua data lieu lay tu hang doi
	uint8_t byRxDataTemp;
	UsartState_e eUartState = (uint8_t)UART_STATE_IDLE;



	//2. Tao vong lap den khi het du lieu trong hang doi
	while((bufNumItems(&g_pUartRxQueue) !=0) && (eUartState == UART_STATE_IDLE)){
		//2.0 Lay 1 phan tu trong hang doi
		bufDeDat(&g_pUartRxQueue, &byRxDataTemp);
		switch(g_eRxState)
		{
		//2.1 Uart state- Start byte: 0xb1
		case RX_STATE_START_1_BYTE:
		{
			//2.1.1 TH: byte du lieu lay ra la byte start 1 0x4C
			if(byRxDataTemp == BYTE_START_1)
			{
				/*
				 * Neu la byte start thi se khoi tao
				 * 1. Bien check xor = 0xff
				 * 2. Khoi tao so byte data doc duoc
				 * 3. Khoi tao g_eRxState sang trang thai bat dau doc du lieu
				 */
				g_eRxState = RX_STATE_START_2_BYTE;
			}
			//2.1.4 TH: con lai
			else
			{
				eUartState = UART_STATE_ERROR;
			}
			break;
		}
		case RX_STATE_START_2_BYTE:
				{
					//2.1.1 TH: byte du lieu lay ra la byte start 2
					if(byRxDataTemp == BYTE_START_2)
					{
						/*
						 * Neu la byte start thi se khoi tao
						 * 1. Bien check xor = 0xff
						 * 2. Khoi tao so byte data doc duoc
						 * 3. Khoi tao g_eRxState sang trang thai bat dau doc du lieu
						 */
						g_byRxCheckXor = 0;
						g_byRxIndexByte = 0;
						g_eRxState = RX_STATE_DATA_BYTES;
					}
					//2.1.4 TH: con lai
					else
					{
						g_eRxState = RX_STATE_START_1_BYTE;
						eUartState = UART_STATE_ERROR;
					}
					break;
				}
		//2.2 Uart state- Data byte
		case RX_STATE_DATA_BYTES:
		{
			/*
			 * Trong qua trinh doc du lieu:
			 * 1. Luu du lieu vao  mang de xu ly tiep
			 * 2. Tinh toan check Xor de xac nhan toan ven cua data da nhan duoc
			 * 3. Neu so byte doc duoc lon hon gia tri ma mang co the luu thi reset va bao loi
			 */
			if(g_byRxIndexByte < RX_MAX_INDEX_BYTE)
			{
				g_pbyRxDataByte[g_byRxIndexByte] = byRxDataTemp;
				if(g_byRxIndexByte >0)
				{
					g_byRxCheckXor ^= byRxDataTemp;
				}
				// Neu la byte cuoi cung thi se chuyen sang check xor
				// Sau byte start la byte chua do dai du lieu
				if(++g_byRxIndexByte == g_pbyRxDataByte[0])
				{
					g_eRxState = RX_STATE_CXOR_BYTE;
				}
			}else
			{
				g_eRxState = RX_STATE_START_1_BYTE;
				eUartState = UART_STATE_ERROR;
			}
			break;
		}
		//2.3 Uart state- XOR byte
		case RX_STATE_CXOR_BYTE:
			/*
			 * Neu byte check xor gui toi bang gia tri tinh duoc thi data duoc chap nhan
			 * Nguoc lai thi bao loi
			 */
			//USART_SendData(USARTx, RxDataTemp);
			//USART_SendData(USARTx, g_byRxCheckXor);
			if(byRxDataTemp == g_byRxCheckXor) {
				eUartState = UART_STATE_DATA_RECEIVED;
				return eUartState;
			} else {
				eUartState = UART_STATE_ERROR;
			}

			break;
		//2.1 Default
		default:
			g_eRxState = RX_STATE_START_1_BYTE;
			break;
		}

	}
	return eUartState;
}
/**
 * @func   SerialHandleEventCallback
 * @brief  None
 * @param  None
 * @retval None
 */
void
SerialHandleEventCallback(
	serial_handle_event pSerialEvent
) {
	pSerialHandleEvent = pSerialEvent;
}
/**
 * @func   serialUartInit
 * @brief  Usart & Buffer initialization
 * @param  None
 * @retval None
 */
/**
 * @func   usart6Init
 * @brief  Usart initialization
 * @param  None
 * @retval None
 */
static void usartInit(void)
{
	/*
		 * USART: USART6
		 * RX: PA12
		 */
		GPIO_InitTypeDef	GPIO_InitStruct;
		USART_InitTypeDef	USART_InitStruct;
		NVIC_InitTypeDef	NVIC_InitStruct;

		//1. Configuare GPIO & AF
		RCC_AHB1PeriphClockCmd(USART6_GPIO_RCC, ENABLE);

		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

		GPIO_InitStruct.GPIO_Pin = USART6_PIN_RX;
		GPIO_Init(USART6_PORT, &GPIO_InitStruct);

		GPIO_PinAFConfig(USART6_PORT, USART6_PINSOURCE_RX, USART6_AF);
		//2. Configuare USART6: Bus APB2
		RCC_APB2PeriphClockCmd(USART6_RCC, ENABLE);

		USART_InitStruct.USART_BaudRate = USART6_BAUDRATE;
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Mode = USART_Mode_Rx;
		USART_InitStruct.USART_Parity = USART_Parity_No;
		USART_InitStruct.USART_StopBits = USART_StopBits_1;
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;

		USART_Init(USART6,&USART_InitStruct);

		//3. Enable USART6 Receive intterupt
		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

		//4. Configuare NVIC
		NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

		NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
		NVIC_Init(&NVIC_InitStruct);

		USART_Cmd(USART6, ENABLE);
}

void serialUartInit(void)
{
	//1. Khoi tao bo dem chua du lieu gui ve
	bufInit(g_pBuffDataRx, &g_pUartRxQueue, sizeof(g_pBuffDataRx[0]), SIZE_BUFF_DATA_RX);

	//2. Khoi tao ket noi USART2
	usartInit();
}

/**
 * @func   USART6x_IRQHandler
 * @brief
 * @param  None
 * @retval None
 */
void USART6_IRQHandler(void)
{
	uint8_t byData;
	if((USART_GetITStatus(USART6, USART_IT_RXNE) == SET))
	{
		byData = USART_ReceiveData(USART6);
		g_byRxNumByte++;
		bufEnDat(&g_pUartRxQueue,&byData);
	}
	USART_ClearITPendingBit(USART6, USART_IT_RXNE);
}

