.equ __P24FJ64GA002,1 ;required "boilerplate" (BP)
.include "p24Fxxxx.inc" ;BP
#include "xc.inc" ;BP
.text ;BP (put the following data in ROM(program memory))
; This is a library, thus it can *not* contain a _main function: the C file will
; deine main(). However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _fifty_microsec_delay, _one_millisec_delay

_write_0:
inc LATA
repeat #3
nop
clr LATA
repeat #6
nop
return

_write_1:
inc LATA
repeat #9
nop
clr LATA
nop
nop
return

_fifty_microsec_delay:
repeat #793
nop
return

_one_millisec_delay:
repeat #15993
nop
return