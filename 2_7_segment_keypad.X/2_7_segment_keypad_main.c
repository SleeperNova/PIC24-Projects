/*
 * File:   2_7_segment_keypad_main.c
 * Author: FranciscoSaavedra
 *
 * Created on March 16, 2021, 10:57 PM
 */

#include <p24Fxxxx.h>
#include "xc.h"
#include "stdint.h"
#include "display.h"
#include "keypad.h"

// PIC24FJ64GA002 Configuration Bit Settings
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled.
// Primary Oscillator refers to an external osc connected to the OSC1 and OSC2 pins)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // OSC2/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled,
// Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL  // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#define PERIOD 
#define TIME 
#define NOKEY 255


int main(void){
    init7seg();
    initKeyPad();
    char new;
    char store_1;
    char store_2;
    char last_key = 'x';
    int count = 0;
    
    store_1 = 'x';
    store_2 = 'x';
    
    while(1)
    {
            showChar7seg(store_2,MSB);
            delay(1);
            showChar7seg(store_1,LSB);
            delay(1);
            count++;
        
            new = readKeyPadRAW();
            
           
            if(new != 'x' && last_key == 'x')
            {
                store_2 = store_1;
                store_1 = new; 
                
                count = 0;
            }
            
            last_key = new;
           
            showChar7seg(store_2,MSB);
            delay(8);
            showChar7seg(store_1,LSB);
            delay(3);
    }
}
