/* 
 * File:   display.h
 * Author: FranciscoSaavedra
 *
 * Created on March 17, 2021, 10:26 AM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

    enum DIGIT {
        LSB,
        MSB
    };
    
    void init7seg(void);
    void showChar7seg(char myChar, enum DIGIT myDigit);
    void delay_1millisecond (void);
    void delay(int x);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */