
/**************************************************************************************************/
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	
#include "sys.h"

#ifndef _SPI_H_
#define _SPI_H_

#define LCD_SPI						SPI1
#define LCD_SPI_RCC					RCC_APB2Periph_SPI1
#define LCD_GPIO_RCC				RCC_AHB1Periph_GPIOB
#define LCD_SPI_GPIO_MISO			GPIO_Pin_4
#define LCD_SPI_PINSOURCE_MISO		GPIO_PinSource4
#define LCD_SPI_GPIO_MOSI			GPIO_Pin_5
#define LCD_SPI_PINSOURCE_MOSI		GPIO_PinSource5
#define LCD_SPI_GPIO_SCK			GPIO_Pin_3
#define LCD_SPI_PINSOURCE_SCK		GPIO_PinSource3
#define LCD_SPI_PORT				GPIOB
#define LCD_SPI_AF					GPIO_AF_SPI1
 
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte);
void SPI1_Init(void);
void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet);

#endif
