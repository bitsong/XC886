$NOMOD51
;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Startup Code for the Infineon XC8xx devices 
;  Copyright (c) 1988-2005 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 1.00
;
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;  STARTUP.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP.OBJ  controls
;
;------------------------------------------------------------------------------
;
;<e> Use off-chip XTAL
;<i> XC8xx series runs by default from on-chip osciallator.
;<i> optionally you may use a off-chip XTAL
XTAL        EQU     1   ; set to 0 On-chip oscillator

; <o> PLL N-Divider
; <0=>  N=10
; <1=>  N=12
; <2=>  N=13
; <3=>  N=14
; <4=>  N=15
; <5=>  N=16
; <6=>  N=17
; <7=>  N=18
; <8=>  N=19
; <9=>  N=20 (9.6 MHz On-Chip XTAL)
; <10=> N=24 (8 MHz Ext XTAL)
; <11=> N=30
; <12=> N=32
; <13=> N=36
; <14=> N=40
; <15=> N=48
NDIV        EQU    10   ; default 9
;</e>
;------------------------------------------------------------------------------
;
;  User-defined <h> Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
;<o> IDATA memory length <0x0-0x100>
;<i> Note: The absolute start-address of IDATA memory is always 0
;<i>       The IDATA space overlaps physically the DATA and BIT areas.
IDATALEN        EQU     0x80
;
; <o> XDATA memory start address <0x0-0xFFFF> 
; <i> absolute start-address of XDATA memory
XDATASTART      EQU     0xF000     
;
; <o> XDATA memory length <0x0-0xFFFF> 
; <i> length of XDATA memory in bytes.
XDATALEN        EQU     0x200      
;
; <o> PDATA memory start address <0x0-0xFFFF> 
; <i> absolute start-address of PDATA memory
PDATASTART      EQU     0H
;
; <o> PDATA memory length <0x0-0xFF> 
; <i> length of PDATA memory in bytes.
PDATALEN        EQU     0H
;
; </h>
;------------------------------------------------------------------------------
;
; <h> Reentrant Stack Initilization
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
; Stack Space for reentrant functions in the SMALL model.
; <e> Activate reentrant Stack (SMALL model)
IBPSTACK        EQU     0       ; set to 1 if small reentrant is used.
; <o> top of stack <0x0-0xFF> 
; <i> set top of stack to highest location+1 
IBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </e>
;
;  Stack Space for reentrant functions in the LARGE model.      
; <e> Activate reentrant Stack (LARGE model)
XBPSTACK        EQU     0       ; set to 1 if large reentrant is used.
; <o> top of stack <0x0-0xFFFF> 
; <i> set top of stack to highest location+1.
XBPSTACKTOP     EQU     0xFFFF +1   ; default 0FFFFH+1 
; </e>
;
;  Stack Space for reentrant functions in the COMPACT model.    
; <e> Activate reentrant Stack (COMPACT model)
PBPSTACK        EQU     0       ; set to 1 if compact reentrant is used.
;
; <o> top of stack <0x0-0xFF> 
; <i> set top of stack to highest location+1.
PBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </e>
; </h>
;------------------------------------------------------------------------------
;
;  <e>Set Memory Page for Using the Compact Model with 64 KByte xdata RAM
;
;  <i>Define the xdata page used for pdata variables. 
;  <i>PPAGE must conform with the PPAGE set in the linker invocation.
;
; Enable pdata memory page initalization
PPAGEENABLE     EQU     0       ; set to 1 if pdata object are used.
;
; <o> PPAGE number <0x0-0xFF> 
; <i> uppermost 256-byte address of the page used for pdata variables.
PPAGE           EQU     0xF0
;
; <o> SFR address which supplies uppermost address byte <0x0-0xFF> 
; <i> most 8051 variants use P2 as uppermost address byte
PPAGE_SFR       DATA    0A0H
;
; </e>
;------------------------------------------------------------------------------

; Standard SFR Symbols 
ACC     DATA    0E0H
B       DATA    0F0H
SP      DATA    81H
DPL     DATA    82H
DPH     DATA    83H

; XC8xx specific SFR Symbols used in STARTUP code
sfr  SCU_PAGE = 0xBF
sfr  PLL_CON  = 0xB7
sfr  OSC_CON  = 0xB6
sfr  PASSWD   = 0xBB


                NAME    ?C_STARTUP


?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

                RSEG    ?STACK
                DS      1

                EXTRN CODE (?C_START)
                PUBLIC  ?C_STARTUP

                CSEG    AT      0
?C_STARTUP:     LJMP    STARTUP1

                RSEG    ?C_C51STARTUP

STARTUP1:

IF XTAL <> 0
                                        ; switch to external XTAL
                MOV     SCU_PAGE,#1
                ORL     PLL_CON, #0x04  ; OSCDISC = 1   _ _ _ NDIV, VCOBYP, OSCDISC, RESLD, LOCK
                ORL     OSC_CON, #0x04  ; OSCSS = 1     0, 0, 0, OSCPD, XPD, OSCSS, ORDRES, OSCR
                ANL     OSC_CON, #0xF7  ; XPD = 0       power xtal
                                
                MOV     R0,#10          ; delay around 1.5 ms
DelayXTAL:
                DJNZ    R1,$
                DJNZ    R0,DelayXTAL
                                        ; redetection of osc
OSCR_NOTSET:
                ORL     OSC_CON, #0x02  ; ORDRES = 1
WAIT_ORDRES_0:
                MOV     A,OSC_CON
                JB      ACC.1,WAIT_ORDRES_0
                JNB     ACC.0,OSCR_NOTSET
        
                                        ; VCOBYP to change N-Divider
                ORL     PLL_CON, #0x08  ; VCOBYP = 1
                ANL     PLL_CON, #0xFB  ; OSCDISC = 0
                MOV     PASSWD,  #0x98  ; open access to writing protected bit
                ANL     PLL_CON, #0x0F
                ORL     PLL_CON, #NDIV*16

                ORL     PLL_CON, #0x02  ; detect PLL lock
WAIT_LOCK:
                MOV     A, PLL_CON
                JNB     ACC.0, WAIT_LOCK
                     ; reconnect to PLL
                ANL     PLL_CON, #0xF7  ; VCOBYP = 0
                MOV     SCU_PAGE,#0
ENDIF

IF IDATALEN <> 0
                MOV     R0,#IDATALEN - 1
                CLR     A
IDATALOOP:      MOV     @R0,A
                DJNZ    R0,IDATALOOP
ENDIF

IF XDATALEN <> 0
                MOV     DPTR,#XDATASTART
                MOV     R7,#LOW (XDATALEN)
  IF (LOW (XDATALEN)) <> 0
                MOV     R6,#(HIGH (XDATALEN)) +1
  ELSE
                MOV     R6,#HIGH (XDATALEN)
  ENDIF
                CLR     A
XDATALOOP:      MOVX    @DPTR,A
                INC     DPTR
                DJNZ    R7,XDATALOOP
                DJNZ    R6,XDATALOOP
ENDIF

IF PPAGEENABLE <> 0
                MOV     PPAGE_SFR,#PPAGE
ENDIF

IF PDATALEN <> 0
                MOV     R0,#LOW (PDATASTART)
                MOV     R7,#LOW (PDATALEN)
                CLR     A
PDATALOOP:      MOVX    @R0,A
                INC     R0
                DJNZ    R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

                MOV     ?C_IBP,#LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

                MOV     ?C_XBP,#HIGH XBPSTACKTOP
                MOV     ?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
                MOV     ?C_PBP,#LOW PBPSTACKTOP
ENDIF

                MOV     SP,#?STACK-1

                LJMP    ?C_START

; Overwrite ?C?DPSEL address for XC866 Device
PUBLIC ?C?DPSEL
?C?DPSEL DATA 0A2H   ; DPSEL address for Mentor M8051EW

                END

