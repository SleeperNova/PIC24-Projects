#include <p24Fxxxx.h>
#include "xc.h"
#include "keypad.h"

void initKeyPad (void){
    CLKDIVbits.RCDIV = 0;
    
    AD1PCFG = 0x9fff; // all digital
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    
    CNPU1bits.CN2PUE = 1;
    CNPU1bits.CN3PUE = 1;
    CNPU2bits.CN30PUE = 1;
    CNPU2bits.CN29PUE = 1;
    
    TRISBbits.TRISB12=0;
    TRISBbits.TRISB13=0;
    TRISBbits.TRISB14=0;
    TRISBbits.TRISB15=0;   
}

char readKeyPadRAW(){
        LATB &= 0x0fff;  
        LATB |= 0xe000;
        
        delay(1); 
        
            switch(PORTA & 0xf) //0 0 0 1
            { 
                case 0xe: //1 1 1 0
                    return 'a';
                    break;
                case 0xd: //1 1 0 1
                    return '3';
                    break;
                case 0xb:// 1 0 1 1                  
                    return '2';
                    break;
                case 0x7:// 0 1 1 1
                    return '1';
                    break;            
            }
            
        LATB &= 0x0fff;  //reset LATB
        LATB |= 0xd000;
       //  if(LATBbits.LATB13== 0)
         delay(1);
        
            switch(PORTA & 0xf)
            {
                case 0xe:
                    return 'b';
                    break;
                case 0xd:
                    return '6';
                    break;
                case 0xb:
                    return '5';
                    break;
                case 0x7:
                    return '4';
                    break;
            }
            
        LATB &= 0x0fff;  //reset LATB
        LATB |= 0xb000;
            delay(1);
       // if(LATBbits.LATB14 == 0)
        
            switch(PORTA & 0xf)
            {
                case 0xe:
                    return 'c';
                    break;
                case 0xd:
                    return '9';
                    break;
                case 0xb:
                    return '8';
                    break;
                case 0x7:
                    return '7';
                    break;
            }
            
        LATB &= 0x0fff;  //reset LATB
        LATB |= 0x7000;
         
         delay(1);
        
            switch(PORTA & 0xf)
            {
                case 0xe:
                    return 'd';
                    break;
                case 0xd:
                    return 'f';
                    break;
                case 0xb:
                    return '0';
                    break;
                case 0x7:
                    return 'e';
                    break;       
            }
     
       return 'x'; // if the "if" statement isn't taken it will return the a dummy 'x' value; 
                   // x is used to show no key pad entry is made 
}

void delay (int x){
    int i;
    for(i=0;i<x;i++)
        delay_1millisecond();
}