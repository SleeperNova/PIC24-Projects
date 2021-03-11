/* 
 * File:   Color_Wheel_RGB_Assembly.h
 * Author: FranciscoSaavedra
 *
 * Created on March 4, 2021, 2:45 PM
 */

#ifndef COLOR_WHEEL_RGB_ASSEMBLY_H
#define	COLOR_WHEEL_RGB_ASSEMBLY_H

#ifdef	__cplusplus
extern "C" {
#endif
void fifty_microsec_delay(void);
void write_0(void);
void write_1(void);
void one_millisec_delay(void);
void writeColor(int r, int g, int b);
void delay(int delay_in_ms);
void drawFrame(int frame);
uint32_t Wheel(int WheelPos);
void writePacCol(uint32_t PackedColor);
int getB(uint32_t RGBval);
int getG(uint32_t RGBval);
int getR(uint32_t RGBval);
uint32_t packColor(int Red, int Blue, int Green);
#ifdef	__cplusplus
}
#endif

#endif	/* COLOR_WHEEL_RGB_ASSEMBLY_H */

