/*
 * File:   logic_analyzer_simulator_main.c
 * Author: FranciscoSaavedra
 *
 * Created on February 15, 2021, 3:39 PM
 */


#include "xc.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)
// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
// Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void)
{
    //clock speed to max
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M 
    AD1PCFG = 0x9fff; // all digital pins
    TRISA = 0b0000000000011111; //tells the direction, determines whether the pin is input or output
    TRISB = 0b0000000000000011; //read from the port, write to the latch
    LATA = 0xffff;// latch
    LATB = 0xffff; //displays the output
}

int main(void) {
    unsigned short int count = 0; //16 bytes
    unsigned long int delay = 0; //32 bytes
    
    setup();
   
    while(1) {
        //execute repeatedly forever and ever and ever...
        count++; //increment count ;add break point to see period in simulator
        LATB = count << 2; //assign shift by 2 digits
        delay = 40;
        while(delay--); 
        asm("nop"); //assembly "no operation" -- wastes 1 cycle
        asm("nop");
    }
   
    return 0;
}