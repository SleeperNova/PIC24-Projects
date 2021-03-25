.include "xc.inc"
.text ;BP (put the following data in ROM(program memory))
; This is a library, thus it can *not* contain a _main function: the C file will
; deine main(). However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading
; underscore (_) and be included in a comment delimited list below.
.global _example_public_function, _second_public_function
.global _delay_50us , _delay_1millisecond 
      
_delay_50us:
    repeat #800
    nop
    return
    
_delay_1millisecond:
    repeat #15993
    nop
    return
   