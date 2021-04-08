.equ __P24FJ64GA002,1 ;required "boilerplate" (BP)
.include "p24Fxxxx.inc" ;BP
#include "xc.inc" ;BP
.text ;BP (put the following data in ROM(program memory))
; This is a library, thus it can *not* contain a _main function: the C file will
; deine main(). However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading
; underscore (_) and be included in a comment delimited list below.
.global _one_millisec_delay

_one_millisec_delay:
    repeat #15999
    nop
    return