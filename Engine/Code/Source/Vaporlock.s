	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.export		_VaporlockSetup
	.export		_Vaporlock

;   *****************************************
;   *                                       *
;   *            -< VAPORLOCK >-            *
;   *                                       *
;   *      (FAST AND EXACT FIELD SYNC)      *
;   *                                       *
;   *       VERSION 1.0 ($SAFF-$88C7)       *
;   *    for the APPLE II+ and APPLE lIe    *
;   *                                       *
;   *               10-12-83                *
;   *.......................................*
;   *                                       *
;   *          COPYRIGHT C 1983 BY          *
;   *                                       *
;   *     DON LANCASTER AND SYNERGETICS     *
;   *     BOX 1300, THATCHER AZ., 85552     *
;   *             (602) 428-4073            *
;   *                                       *
;   *     ALL COMMERCIAL RIGHTS RESERVED    *
;   *                                       *
;   *****************************************

;             *** WHAT IT DOES ***

;   This subroutine gives you a fast and exact field
;   sync that locks to the video screen in as few as
;   nine scan lines. No hardware mods are needed.
;
;   The same code works on the Apple II+ or IIe.
;
;   The vaporlock, with suitable support software,
;   lets you mix and match HIRES, LORES, and text
;   anywhere on the screon, provides for glitchless
;   animation, simplifies light pens, allows grey
;   scaler text-over-color, professional video wipes,
;   and offers many other new visual display tricks
;   that seem "impossible" to do on a stock Apple.
;
;   Typical displays are totally free from any
;   glitches or jitter.

;            *** GOTCHAS ***

;  This code only runs on "real" Apples.
;
;  Franklins, clones, and look-alikes may have
;  different timing that requires special code.
;
;  Certain oddball plug-in cards might interfere
;  with operation on the II+. Such interference
;  is unlikley on the IIe.
;
;  Parts of the code have very critical timing
;  and must not cross a page boundary. If you
;  relocate the code, put it all on one page.
;

;            *** ENHANCEMENTS ***

;  You can make a `phasing` adjustment by adding
;  or removing NOPS and branches in the PHASE code.
;  code.  Note that a NOP or a branch not taken uses
;  two clock cycles, while a branch taken needs three
;
;  You can preset the soft switches at the top of
;  the screen with suitable pokes to SHOW.
;
;  VAPORLK object code is relocatable, if you put
;  it all on one page of memory.  Be sure to protect
;  memory and link to your first or second address.
;

;            *** RANDOM COMMENTS ***

;  The accumulator and all flags are saved to the
;  stack. No use is made of the X or Y registers
;
;  The vaporlock exact field sync may be used in
;  your commercial programs provided fair credit
;  is prominently given.
;
;  VAPORLK may be loaded as the highest HRCG
;  character set.
;
;  This version must be called with the appropriate
;  graphics mode already setup.


;            *** HOOKS ***

SNIFF   =   $C020    ; FLOATING DATA BUS READ ADDRESS

;           *** CONSTANTS ***

ID0     =   $DB     ; ID BYTES FOR SYNC PATCH
IDl     =   $24     ;  (ALL SHOULD BE RARELY USED)
ID2     =   $B6     ;
ID3     =   $49     ;
ID4     =   $88     ;
ID5     =   $F3     ; THIS BYTE MUST BE ODD VALUE!

WAIT:   SEC
WAIT2:  PHA
WAIT3:  SBC   #1
        BNE   WAIT3
        PLA
        SBC   #1
        BNE   WAIT2
        RTS

; ---------------------------------------------------------------
; void __near__ VaporlockSetup (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_VaporlockSetup: near

.segment	"CODE"

        PHP            ; SAVE FLAGS
        PHA            ; SAVE ACCUMULATOR

        LDA   #ID0     ; WRITE ID PATCH
        STA   $3FF8    ;  TO LINE $255
        STA   $3FF9    ;
        STA   $3FFA    ;
        STA   $3FFB    ;
        STA   $3FFC    ;
        STA   $3FFD    ;
        STA   $3FFE    ;

        LDA   #IDl     ;  TO LINE #256
        STA   $2BF8    ;
        STA   $2BF9    ;
        STA   $2BFA    ;
        STA   $2BFB    ;
        LDA   #ID2     ;
        STA   $2BFC    ;
        STA   $2BFD    ;
        STA   $2BFE    ;

        LDA   #ID3     ;  TO LINE 257
        STA   $2FF8    ;
        STA   $2FF9    ;
        LDA   #ID4     ;
        STA   $2FFA    ;
        STA   $2FFB    ;

        LDA   #ID5     ; AND FINALLY TO LINE 258
        STA   $33F8    ;
        LDA   #ID5-1   ;
        STA   $33F9    ;

        PLA            ; RESTORE ACCUMULATOR AND FLAGS
        PLP            ;

	rts

.endproc

; ---------------------------------------------------------------
; void __near__ Vaporlock (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_Vaporlock: near

.segment	"CODE"

        PHP            ; SAVE FLAGS
        PHA            ; SAVE ACCUMULATOR

LOCK:   LDA   #ID0     ; LOOK FOR FIRST PATCH ID VALUE
RETRY1: CMP   SNIFF    ;
        BNE   RETRY1   ;
        LDA   #02      ; DELAY FOR EXACTLY 57 CYCLES
        JSR   WAIT     ; (HLINE-BNE-LDA#-LDA)
        PHA            ;
        PLA            ;
        LDA   SNIFF    ; GET SECOND PATCH ID VALUE
        CMP   #ID2     ; JITTER 4,5,OR 6?
        BEQ   MORE1    ;
        CMP   #IDl     ; JITTER 0,1,2, OR 3?
        BEQ   MORE1    ; OK TO CONTINUE
        BNE   LOCK     ; MISSED, TRY AGAIN

MORE1:  LDA   #02      ; DELAY FOR EXACTLY 50 CYCLES
        JSR   WAIT     ;  (HLINE-4-CMP#-BEQ-LDA#-LDA)
        LDA   SNIFF    ; GET THIRD PATCH ID VALUE
        CMP   #ID4     ; JITTER 2 OR 3?
        BEQ   MORE2    ; YES
        CMP   #ID3     ; JITTER 0 OR 1
        BEQ   MORE3    ; ONLY WANT 2 CLOCK CORRECTION

MORE2:  BNE   LOCK     ; CURSES! FOILED AGAIN!
MORE3:  LDA   #$02     ; DELAY FOR EXACTLY 50 CYCLES
        JSR   WAIT     ;  (HLINE-2-CMP#-BEQ-SNE-LDA#-LDA)
        LDA   SNIFF    ; GET FOURTH PATCH ID VALUE
        LSR   A        ; SHIFT INTO CARRY
        BCS   MORE4    ; TO EQUALIZE ONE COUNT

MORE4:  CMP   #ID5/2   ; FINAL VALIDITY CHECK
        BNE   LOCK     ; BACK TO SQUARE ONE

        PLA            ; RESTORE ACCUMULATOR AND FLAGS
        PLP            ;

	rts

.endproc
