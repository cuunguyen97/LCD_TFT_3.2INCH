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
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

typedef struct  
{										    
	u16 width;
	u16 height;
	u16 id;
	u8  dir;
	u16	 wramcmd;
	u16  setxcmd;
	u16  setycmd;
}_lcd_dev; 	

extern _lcd_dev lcddev;
/////////////////////////////////////HORIZONTAL///////////////////////////////////
#define USE_HORIZONTAL  	 0
//////////////////////////////////////////////////////////////////////////////////	  
#define LCD_W 240
#define LCD_H 320

extern u16  POINT_COLOR;
extern u16  BACK_COLOR;

////////////////////////////////////////////////////////////////////
//-----------------LCD----------------

#define LED_PIN		13
#define LED_GPIO 	GPIO_Pin_13

#define CS_PIN   	15
#define CS_GPIO 	GPIO_Pin_15

#define RS_PIN   	14
#define RS_GPIO 	GPIO_Pin_14

#define RST_PIN  	12
#define RST_GPIO 	GPIO_Pin_12

#define LCD_PORT	GPIOB
#define LCD_RCC		RCC_AHB1Periph_GPIOB

#define	LCD_LED PBout(LED_PIN)
#define LCD_CS  PBout(CS_PIN)
#define LCD_RS  PBout(RS_PIN)
#define LCD_RST PBout(RST_PIN)


#define	LCD_CS_SET  LCD_CS=1 //GPIO_TYPE->BSRRL=1<<LCD_CS
#define	LCD_RS_SET	LCD_RS=1 //GPIO_TYPE->BSRRL=1<<LCD_RS
#define	LCD_RST_SET	LCD_RST=1 //GPIO_TYPE->BSRRL=1<<LCD_RST

 							    
#define	LCD_CS_CLR  LCD_CS=0 //GPIO_TYPE->BSRRH=1<<LCD_CS
#define	LCD_RS_CLR	LCD_RS=0 //GPIO_TYPE->BSRRH=1<<LCD_RS
#define	LCD_RST_CLR	LCD_RST=0 //GPIO_TYPE->BSRRH=1<<LCD_RST

				


//Color
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40
#define BRRED 			0XFC07
#define GRAY  			0X8430
//GUI

#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458

 
#define LIGHTGREEN     	0X841F
#define LIGHTGRAY     	0XEF5B
#define LGRAY 			0XC618

#define LGRAYBLUE      	0XA651
#define LBBLUE          0X2B12
	    															  
void LCD_Init(void);
void LCD_SetColorPoint(u16 color);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);
void LCD_ClearCursor(u16 wXs,u16 wYs,u16 wXe,u16 wYe,u16 wColor);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);
u16  LCD_ReadPoint(u16 x,u16 y);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);		   
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );
				  		 
#endif  
	 
	 



