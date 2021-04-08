/* 
 * File:   LCD_Display_assembly.h
 * Author: FranciscoSaavedra
 *
 * Created on April 8, 2021, 11:00 AM
 */

#ifndef LCD_DISPLAY_ASSEMBLY_H
#define	LCD_DISPLAY_ASSEMBLY_H

#ifdef	__cplusplus
extern "C" {
#endif

void one_millisec_delay(void);
void setup(void);
void lcd_cmd(char command);
void lcd_init(void);
void lcd_setCursor(char x, char y);
void lcd_printChar(char myChar);
void lcd_animate(const char *s, char row, int size);
void lcd_printStr(const char *s);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_DISPLAY_ASSEMBLY_H */

