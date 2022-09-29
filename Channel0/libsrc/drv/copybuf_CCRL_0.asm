;/* -------------------------------------------------------------------- */
;/* Copyright(c) 2009-2016 Renesas Electronics Corporation               */
;/* -------------------------------------------------------------------- */
;/* File name: copybuf_CCRL.asm                                          */
;/* Version:   0.02                                                      */
;/* Date:      2016/06/13                                                */
;/* Author:    A.Kondo, S.Sugawara                                       */
;/* -------------------------------------------------------------------- */

;/* -------------------------------------------------------------------- */
;/* History                                                              */
;/*   V0.01: 2013.01.18  1st creation.                                   */
;/*   V0.02: 2016.06.13  CS+ CC-RL support.                              */
;/* -------------------------------------------------------------------- */

;/* -------------------------------------------------------------------- */
;/* Description : Memory copy                                            */
;/* Parameters  : pu1tDst = destination pointer for copy                 */
;/*               pu1tSrc = source pointer for copy                      */
;/*               u1tSize = copy size (LSB:1[bytes])                     */
;/* Return value: Nothing                                                */
;/* Misc.       : Nothing                                                */
;/* -------------------------------------------------------------------- */
; void LDrvSCom_vogCopyBuf(u1 *pu1tDst, const u1* pu1tSrc, u1 u1tSize)

$IFDEF __LIN_MEMCOPY_ASM__

$IFDEF __LIN_CH0_P1__
    .public _LDrvSCom_vogCopyBuf_0
$ENDIF  ; /* __LIN_CH0_P1__ */
$IFDEF __LIN_CH0_P4__
    .public _LDrvSCom_vogCopyBuf_0
$ENDIF  ; /* __LIN_CH0_P4__ */

$IFDEF __LIN_CH1_P1__
    .public _LDrvSCom_vogCopyBuf_1
$ENDIF  ; /* __LIN_CH1_P1__ */
$IFDEF __LIN_CH1_P10__
    .public _LDrvSCom_vogCopyBuf_1
$ENDIF  ; /* __LIN_CH1_P10__ */


.CSEG   TEXTF


$IFDEF __LIN_CH0_P1__
_LDrvSCom_vogCopyBuf_0:
$ENDIF  ; /* __LIN_CH0_P1__ */
$IFDEF __LIN_CH0_P4__
_LDrvSCom_vogCopyBuf_0:
$ENDIF  ; /* __LIN_CH0_P4__ */

$IFDEF __LIN_CH1_P1__
_LDrvSCom_vogCopyBuf_1:
$ENDIF  ; /* __LIN_CH1_P1__ */
$IFDEF __LIN_CH1_P10__
_LDrvSCom_vogCopyBuf_1:
$ENDIF  ; /* __LIN_CH1_P10__ */

;/* --------------------------------------------------------------------------- */
;/*  Argument       Use register    Variable    Description                     */
;/* --------------------------------------------------------------------------- */
;/*  1st argument   AX register     pu1tDst     Destination pointer for copy    */
;/*  2nd argument   BC register     pu1tSrc     Source pointer for copy         */
;/*  3rd argument    E register     u1tSize     Copy size                       */
;/* --------------------------------------------------------------------------- */

;/* --------------------------------------------------------------------------- */
;/*  The registers used in the function and stack area                          */
;/* --------------------------------------------------------------------------- */
;/*  Register/Stack aera      Size       Use contents                           */
;/* --------------------------------------------------------------------------- */
;/*  AX register             16bit       Register for move instruction          */
;/*  B register               8bit       No use                                 */
;/*  C register               8bit       Copy size                              */
;/*  DE register             16bit       Destination address for copy           */
;/*  HL register             16bit       Register for SP area reference,        */
;/*                                      Source address for copy                */
;/* --------------------------------------------------------------------------- */
;/*  (*1) Offset reference from the SP value stored to the HL register.         */
;/*  SP+0h                   16bit       Source address for copy                */
;/*                                      (temporarily stored)                   */
;/*  SP+2h                   16bit       Destination address for copy           */
;/*                                      (temporarily stored)                   */
;/* --------------------------------------------------------------------------- */

    push    AX                          ; SP <- SP + 2
                                        ; Push AX (Destination Address)
    push    BC                          ; SP <- SP + 2
                                        ; Push BC (Source Address)
    movw    HL, SP                      ; HL <- SP (*1)

    mov     A, E                        ;  A <- E (Copy Size)
    mov     C, A                        ;  C <- A (Copy Size)

    movw    AX, [HL + 2]                ; AX <- SP_2h (Destination Address)
    movw    DE, AX                      ; DE <- AX    (Destination Address)

    movw    AX, [HL + 0]                ; AX <- SP_0h (Source Address)
    movw    HL, AX                      ; HL <- AX    (Source Address)

    cmp0    C                           ; Check "Copy Size"
    bz      $finish                     ; If "Copy Size" is "00H" then it returns to the parent function.

loop:
    mov     A, [HL]                     ;  A <- [Source Address]
    mov     [DE], A                     ; [Destination Address] <- A
    incw    HL                          ; HL <- HL + 1 (Source Address)
    incw    DE                          ; DE <- DE + 1 (Destination Address)
    dec     C                           ;  C <-  C - 1 (Copy Size)
    bnz     $loop                       ; If "Copy Size" is not "00H" then it goes to label "loop".

finish:
    pop     BC                          ; SP <- SP - 2
                                        ; Pop BC
    pop     AX                          ; SP <- SP - 2
                                        ; Pop AX
    ret                                 ; Returns to the parent function

$ENDIF  ; /* __LIN_MEMCOPY_ASM__ */
