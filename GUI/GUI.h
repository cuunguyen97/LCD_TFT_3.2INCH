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
#ifndef __GUI_H__
#define __GUI_H__
#include "stm32f401re.h"

void GUI_DrawPoint(u16 x,u16 y,u16 color);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void Draw_Circle(u16 x0,u16 y0,u16 fc,u8 r);
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);

void LCD_ShowTitle(u16 sizeBox,u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
u16 LCD_ShowOption(u16 sizeBox,u16 y,u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode);
void LCD_ShowNumAndStr(u16 x,u16 y,u8 size,char *pStr1,u8 lengthStr,u32 num,u8 lengthNum,u8 mode);
void LCD_ShowStrAndStr(u16 x,u16 y,u8 size,char *pStr1,u8 length1,char *pStr2,u8 length2,u8 mode);
void showimage(const unsigned char *p);

void LCD_ShowButton(u16 x,u16 y,u16 width,u16 height,u8 *pStr,u8 state);
u16 LCD_ShowDevice(u16 x,u16 y,u16 r,u8 *pStr,u8 state);
void LCD_UpdateDeviceState(u16 x,u16 y,u16 r,u8 state);

void LCD_ShowEditNum(u16 x,u16 y,u8 *pStr,u8 lengthNum);
void LCD_UpdateEditNum(u16 xS,u16 yS,u16 xE,u16 yE,u32 num);

void LCD_ShowBtnUpDown(u16 x0,u16 y0,u16 width,u16 height);
void LCD_UpdateBtnUpDown(u16 x0,u16 y0,u16 width,u16 height,u8 event);

void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p); //��ʾ40*40 QQͼƬ
void gui_circle(int xc, int yc,u16 c,int r, int fill);
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void Gui_StrCenterV2(u16 x, u16 y,u16 width,u16 height, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
#endif

