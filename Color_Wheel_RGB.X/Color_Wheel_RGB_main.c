/*
 * File:   Color_Wheel_RGB_main.c
 * Author: FranciscoSaavedra
 *
 * Created on March 4, 2021, 2:41 PM
 */

#include "xc.h"
#include "stdint.h"
#include <p24Fxxxx.h>
#include "Color_Wheel_RGB_Assembly.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)
// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = OFF // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
// Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#define FRAME_PER 25

void setup(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISA = 0b1111111111111110;
    LATA = 0x0001;
}

void delay(int delay_ms){
    int i = 0;

    for(i = 0; i < delay_ms; i++)
    {
     one_millisec_delay();
    }
}

void writeColor(int r, int g, int b){
    int i = 0;

    for(i = 0; i <= 7; i++)//red
    {
     if(0b1000000 & r)
     write_1();
      else
      write_0();
      r = r << 1;
    }

    for(i = 0; i <= 7; i++)//green
    {
     if(0b1000000 & g)
     write_1();
      else
      write_0();
      g = g << 1;
    }

    for(i = 0; i <= 7; i++)//blue
    {
     if(0b1000000 & b)
     write_1();
      else
      write_0();
      b = b << 1;
    }
}

void drawFrame(int frame){
    writeColor(frame, 0 , 255 - frame);
}

uint32_t packColor(int Red, int Blue, int Green){//color packer
    unsigned long int RGBval = 0;
    RGBval = ((long) Red << 16) | ((long) Green << 8) | ((long) Blue);
    return RGBval;
}

int getR(uint32_t RGBval){//red unpacker
    int Red = 0;
    Red = (int) (RGBval >> 16);
    return Red;
}

int getG(uint32_t RGBval){//green unpacker
    int Green = 0;
    Green = (int) (RGBval >> 8);
    return Green;
}

int getB(uint32_t RGBval){//blue unpacker
    int Blue = 0;
    Blue = (int) (RGBval >> 0);
    return Blue;
}

void writePacCol(uint32_t PackedColor){
    int i = 0;

    int redVal = getR(PackedColor); //red
    for (i = 0; i <= 7; i++)
    {
     if(0b10000000 & redVal)
     write_1();
      else
      write_0();
      redVal = redVal << 1;
    }

    int greenVal = getG(PackedColor); //green
    for (i = 0; i <= 7; i++)
    {
     if(0b10000000 & greenVal)
     write_1();
      else
      write_0();
      greenVal = greenVal << 1;
    }

    int blueVal = getB(PackedColor); //blue
    for (i = 0; i <= 7; i++)
    {
     if(0b10000000 & blueVal)
     write_1();
      else
      write_0();
      blueVal = blueVal << 1;
    }
}

uint32_t Wheel(int WheelPos){ //wheel function
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85)
    {
     return packColor(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170)
    {
     WheelPos -= 85;
     return packColor(0, WheelPos * 3, 255 - WheelPos * 3);
    }
     WheelPos -= 170;
     return packColor(WheelPos * 3, 255 - WheelPos * 3, 0);
}
int main(void){
    setup();
    int i = 0;
    int j = 0;
    
    while(1){
    for(j = 0; j <= 255; j++) //packed color writer
    {
     uint32_t packedColor = Wheel(j);
     writePacCol(packedColor);
     delay(FRAME_PER);
    }
    }
     return 0;
}