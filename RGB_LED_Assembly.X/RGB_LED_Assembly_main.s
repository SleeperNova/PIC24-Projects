.equ __P24FJ64GA002,1        ;required "boiler-plate" (BP)
.include "p24Fxxxx.inc"      ;BP

#include "xc.inc"            ;BP

;the next two lines set up the actual chip for operation - required
config __CONFIG2, POSCMOD_EC & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSECME & FNOSC_FRCPLL & SOSCSEL_LPSOSC & WUTSEL_FST & IESO_OFF
config __CONFIG1, WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & BKBUG_ON & GWRP_ON & GCP_ON & JTAGEN_OFF

      .bss                   ;put the following labels in RAM
counter:
      .space 2               ; a variable that takes two bytes (we won?t use
                             ; it for now, but put here to make this a generic
                             ; template to be used later).
stack:
      .space 32              ;this will be our stack area, needed for func calls
.text                        ;BP (put the following data in ROM(program memory))

;because we are using the C compiler to assemble our code, we need a "_main" label
;somewhere. (There's a link step that looks for it.)
.global _main                ;BP

delay_100us: ;n= 100us/62.5ns = 1600cycles ---call func. is 2 cycles
repeat #1593  ;1598 cycles here
nop
return
	
delay_1ms:  ;n= 1us/62.5ns = 16000cycles ---call func. is 2 cycles
repeat #15993 ;15998 cycles here
nop
return    

write_0: ;20cycles; 6 on 14 off
inc LATA ;1
repeat #3 ; 1
nop ; 1+3
clr LATA ; 1
repeat #8 ;1
nop ;8+1
return ;3

write_1: ;20cycles; 11 on 9 off
inc LATA ;1
repeat #8 ; 1
nop ; 1+8
clr LATA ;1
repeat #3 ;1
nop ;1+3
return ;3
    
_main:
bclr CLKDIV,#8               ;BP
nop
mov  #0xffff, w0
mov  w0, AD1PCFG	     ;set all pins to digital mode
mov  #0b1111111111111110, w0
mov  w0, TRISA		     ;set pin RA0 to output
mov  #0x0001, w0
mov  w0, LATA		     ;set pin RA0 to high ;break point

foreverLoop:
clr LATA 
call delay_100us 
    
call write_1		     ;24 bit color R G B
call write_1
call write_1
call write_1
call write_1
call write_1
call write_1
call write_1
    
call write_0
call write_0
call write_0
call write_0
call write_0
call write_0
call write_0
call write_0
    
call write_0
call write_0
call write_0
call write_0
call write_0
call write_0
call write_0
call write_0
    
bra foreverLoop