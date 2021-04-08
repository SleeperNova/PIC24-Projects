/* 
 * File:   LCD_Display_main.c
 * Author: FranciscoSaavedra
 *
 * Created on April 8, 2021, 11:00 AM
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include <p24FJ64GA002.h>
#include "LCD_Display_assembly.h" 

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
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

char _CONTRAST = 0b100000; //0b1111100;//01110101

int initialX = 0;
char state1Index = 0;

void setup(void)
{
    CLKDIVbits.RCDIV = 0;
    
    AD1PCFG = 0xffff;
    
    TRISB = 0;
    TRISBbits.TRISB3 = 1;
    TRISA = 0;
    
    I2C2CONbits.I2CEN = 0;
    
    //Sets the Baud Rate to 100 kHz
    I2C2BRG = 157; 
    I2C2CONbits.I2CEN = 1;
    IFS3bits.MI2C2IF = 0; 
}

//Function which writes a command packet
void lcd_cmd(char command)
{
    I2C2CONbits.SEN = 1;
    
    while(I2C2CONbits.SEN == 1);
    
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01111100;
             
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b00000000;
    
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = command;
    
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    
    while(I2C2CONbits.PEN == 1);
}

//Function which initializes LCD values via commands
void lcd_init(void)
{
    int i = 0;
    
    for(;i < 50; i++)
    {
        one_millisec_delay();
    }
    
    lcd_cmd(0b00111000);    //function set, normal instruction mode
    lcd_cmd(0b00111001);    //function set, extended instruction mode
    lcd_cmd(0b00010100);    //interval osc
    //lcd_cmd(_CONTRAST);    //contrast C3-C0
    lcd_cmd(0x70 | (_CONTRAST & 0xf)); // contrast C3-C0     
    lcd_cmd(0x54 | ((_CONTRAST >> 4) & 3));//C5-C4, Ion, Bon
    //lcd_cmd(0b01011101);    //C5-C4, Ion, Bon
    lcd_cmd(0b01101100);    //follower control
    
    i = 0;
    
    for(; i < 200; i++)
    {
        one_millisec_delay();
    }
    
    lcd_cmd(0b00111000);    //function set, normal instruction mode
    lcd_cmd(0b00001100);    //Display On
    lcd_cmd(0b00000001);    //Clear Display
}

//Function which sets the cursor on the LCD
void lcd_setCursor(char x, char y)
{   
    char address = 0b10000000;
    
    address += ((0x40)*x) + y;
    
    lcd_cmd(address);
}

//Function which prints a single character to
//wherever the cursor is located
void lcd_printChar(char myChar)
{
    I2C2CONbits.SEN = 1;
    
    while(I2C2CONbits.SEN == 1);
    
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01111100;
             
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01000000;
    
    while(IFS3bits.MI2C2IF == 0);
    
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = myChar;
    
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    
    while(I2C2CONbits.PEN == 1);
}

//Function which animates a string at the given row
void lcd_animate(const char *s, char row, int size)
{
    static int cursorX = 0;
    
    //Variable for how the word should be animated
    //0 --> just move the word across and off the LCD
    //1 --> bring the word in from the left
    static int cursorState = 0;
    
    //Just need to move the word over and off LCD
    if(cursorState == 0)
    {
        //Set the cursor 
        lcd_setCursor(row, cursorX);
        
        //The word is offscreen
        if(cursorX > 7)
            cursorState = 1;
    
        //Reset the cursorX index
        if(cursorX > 8)
            cursorX = 0;
        
        //Set the cursor again just to be safe
        lcd_setCursor(row, cursorX);
    
        //Start word print
        if(cursorX == 0)
            lcd_printStr(s);
        
        //Add spaces in front as the word moves
        else
        {
            int j = 0;
            for(j = 0; j < cursorX; j++)
            {
                lcd_setCursor(row, j);
                lcd_printChar(' ');
            }
        
            lcd_printStr(s);
        }   
    
        lcd_setCursor(row, cursorX);
    
        cursorX++;
    }
    
    //Word must be reconstructed from the left
    else if(cursorState == 1)
    {
        //Word backwards index
        static int n = 1;
        
        if(n > size)
        {
            n = 1;
        }
        
        //Cursor location (constant 0))
        int cursorXState1 = 0;
        
        lcd_setCursor(row, cursorXState1);
        
        char new[9];
        
        //Word index
        int j = size - n;
        int k = 0;
        
        //Fill in the letters and spaces as needed
        while(k < 9)
        {
            if(k < n)
            {
                new[k] = s[j];
            }
            else
            {
                new[k] = ' ';
            }
            
            k++;
            j++;
        }
        
        lcd_setCursor(row, cursorXState1);
        lcd_printStr(new);
        
        n++;
        
        //Word is done being reconstructed so go
        //back to moving the word over
        if(n > size -1)
        {
            cursorState = 0;
        }   
    }
    
    //250 ms delay
    int i = 0;
    for(i = 0; i < 250;i++)
        one_millisec_delay();
}

//Function which prints a string of characters
void lcd_printStr(const char *s)
{
    int stringIndex = 0;
    
    I2C2CONbits.SEN = 1;
    
    while(I2C2CONbits.SEN == 1);
    
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01111100;
             
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    while(s[stringIndex + 1] != 0)
    {
        I2C2TRN = 0b11000000;
    
        while(IFS3bits.MI2C2IF == 0);
    
        IFS3bits.MI2C2IF = 0;
        
        I2C2TRN = s[stringIndex];
    
        while(IFS3bits.MI2C2IF == 0);
    
        IFS3bits.MI2C2IF = 0;
    
        stringIndex++;
    }
    
    I2C2TRN = 0b01000000;
    
    while(IFS3bits.MI2C2IF == 0);
    
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = s[stringIndex];
    
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    
    while(I2C2CONbits.PEN == 1);
}

int main(void) 
{
    setup();   
    lcd_init();
    
    while(1)
    {
        //lcd_setCursor(0,0); // not moving
        //lcd_printStr("Hello"); //not moving
        //lcd_setCursor(1,2); //not moving
        //lcd_printStr("World!"); //not moving
        
        lcd_animate("Hello", 0, 5); //moving
        //lcd_setCursor(0,0); // not moving
        //lcd_printStr("Hello"); //not moving
        lcd_animate("World!", 1, 6); //moving
    }

    return 0;
}