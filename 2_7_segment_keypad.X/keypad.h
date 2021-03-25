/* 
 * File:   keypad.h
 * Author: FranciscoSaavedra
 *
 * Created on March 17, 2021, 10:28 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initKeyPad (void);
    void delay_1millisecond (void);
    void delay(int x);
    char readKeyPadRAW();

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

