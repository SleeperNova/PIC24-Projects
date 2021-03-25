#include <p24Fxxxx.h>
#include "xc.h"
#include "display.h"


void init7seg(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISB &= 0xf003;
    LATB = 0;
}

void showChar7seg(char myChar, enum DIGIT myDigit ){ 
    if(myDigit ==MSB){
         LATBbits.LATB10=1;
        switch(myChar)
        {
            case '0':
              //  LATBbits.LATB10=1;
                LATB = 0xf40b;
                break;
            case '1':
               // LATBbits.LATB10=1;
                LATB = 0xf67f;
                break;
            case '2':
              //  LATBbits.LATB10=1;
                LATB = 0xf493;
                break;
            case '3':
               // LATBbits.LATB10=1;
                LATB = 0xf433;
                break;
            case '4':
               // LATBbits.LATB10=1;
                LATB = 0xf663;
                break;
            case '5':
                LATBbits.LATB10=1;
                LATB = 0xf523;
                break;
            case '6':
                LATBbits.LATB10=1;
                LATB = 0xf503;
                break;
            case '7':
                LATBbits.LATB10=1;
                LATB = 0xf47b;
                break;
            case '8':
                LATBbits.LATB10=1;
                LATB = 0xf403;
                break;
            case '9':
              //  LATBbits.LATB10=1;
                LATB = 0xf463;
                break;
            case 'a':
             //   LATBbits.LATB10=1;
                LATB = 0xf413;
                break;
            case 'b':
                LATB = 0xf703;
                break;
            case 'c':
                LATB = 0xf58b;
                break;
            case 'd':
                LATB = 0xf613;
                break;
            case 'e':
                LATB = 0xf483;
                break;
            case 'f':
                LATB = 0xf5c3;
                break;       
        }
    }
    else
    {
       LATBbits.LATB11=1;
       switch(myChar)
       {
           case '0':
                LATB = 0xf80b;
                break;
            case '1':
                LATB = 0xfa7b;
                break;
            case '2':
                LATB = 0xf893;
                break;
            case '3':
                LATB = 0xf833;
                break;
            case '4':
                LATB = 0xfa63;
                break;
            case '5':
                LATB = 0xf923;
                break;
            case '6':
                LATB = 0xf903;
                break;
            case '7':
                LATB = 0xf87b;
                break;
            case '8':
                LATB = 0xf803;
                break;
            case '9':
                LATB = 0xf863;
                break;
            case 'a':
                LATB = 0xf813;
                break;
            case 'b':
                LATB = 0x0b03;
                break;
            case 'c':
                LATB = 0xf98b;
                break;
            case 'd':
                LATB = 0xfa13;
                break;
            case 'e':
                LATB = 0xf883;
                break;
            case 'f':
                LATB = 0xf9c3;
                break;  
       } 
    }
}