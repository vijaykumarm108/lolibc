;
; (c) Copyright 2008, MuThink Inc.  This source code is protected by
; license agreement and copyright.  It is property of MuThink Inc. and can not be used in
; any way without an express license agreement with MuThink Inc.  Modification of source
; code is also not allowed unless a license is purchased permitting changes.  Derived
; code must contain this notice and cannot be sold or released in source code form without
; permission from MuThink Inc.

   .386
   .model flat
   
	public  __fltused
 __fltused        equ     9876h

   .code
   ; Code bounces to MSVCRT.DLL

   ; MSVCRT.DLL
   extrn __imp____CxxFrameHandler:dword  ; external memory addr

public  ___CxxFrameHandler3 
___CxxFrameHandler3 proc near

   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp____CxxFrameHandler  ; Trampoline bounce 
___CxxFrameHandler3 endp

public  ___CxxFrameHandler4
___CxxFrameHandler4 proc near

   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp____CxxFrameHandler  ; Trampoline bounce 
___CxxFrameHandler4 endp

	extrn __imp___CxxThrowException:dword
public __CxxThrowException@8
__CxxThrowException@8 proc near
   jmp  __imp___CxxThrowException  ; Trampoline bounce 
__CxxThrowException@8 endp

	extrn __imp___except_handler3:dword
public __except_handler4
__except_handler4	proc	near
	jmp	__imp___except_handler3
__except_handler4	endp

; Bounce _ftol2_sse --> __imp___ftol
   extrn __imp___ftol:dword  ; external memory addr
public  __ftol2_sse 
__ftol2_sse proc near
   ; Jump indirect: Jumps to (*__ftol2 )
   jmp  __imp___ftol  ; Trampoline bounce 
__ftol2_sse endp 

public __ftol
__ftol proc near
	fistp    DWORD PTR [esp-12]
	mov		 eax, DWORD PTR [esp-12]
	mov		 ecx, DWORD PTR [esp-8]
	ret
__ftol endp

; __imp____iob_func -->
   extrn __imp___iob:dword	; external memory addr
public  __imp____iob_func 
__imp____iob_func proc near
   mov eax,[DWORD PTR __imp___iob]
   ret
__imp____iob_func endp

public  ___iob_func
___iob_func proc near
   mov eax,[DWORD PTR __imp___iob]
   ret
___iob_func endp


; __imp____mb_cur_max_func -->
   extrn __imp____p___mb_cur_max:dword	; external memory addr
public  __imp_____mb_cur_max_func 
__imp_____mb_cur_max_func proc near
	mov	eax, DWORD PTR __imp____p___mb_cur_max		; Returns the static value here.
	ret
__imp_____mb_cur_max_func endp


   extrn __imp___fstat:dword  ; external memory addr
public  __imp___fstat32 
__imp___fstat32 proc near
   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp___fstat  ; Trampoline bounce 
__imp___fstat32 endp


   extrn __imp___stat:dword  ; external memory addr
public  __imp___stat32 
__imp___stat32 proc near
   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp___stat  ; Trampoline bounce 
__imp___stat32 endp

   extrn __imp__localtime:dword  ; external memory addr
public  __imp___localtime32 
__imp___localtime32 proc near
   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp__localtime  ; Trampoline bounce 
__imp___localtime32 endp

   extrn __imp__mktime:dword  ; external memory addr
public  __imp___mktime32 
__imp___mktime32 proc near
   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp__mktime  ; Trampoline bounce 
__imp___mktime32 endp

   extrn __imp__time:dword  ; external memory addr
public  __imp___time32 
__imp___time32 proc near
   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp__time  ; Trampoline bounce 
__imp___time32 endp

;	extrn __invalid_parameter:dword
;public __imp___invalid_parameter
;__imp___invalid_parameter	proc	near
;	jmp	__invalid_parameter
;__imp___invalid_parameter	endp

public __imp___invalid_parameter_noinfo
__imp___invalid_parameter_noinfo proc near
	ret
__imp___invalid_parameter_noinfo endp

;	extrn _malloc:dword
;public __imp__malloc
;__imp__malloc proc near
;	jmp	_malloc
;__imp__malloc endp

;	extrn _free:dword
;public __imp__free
;__imp__free proc near
;	jmp	_free
;__imp__free endp




;***
;ullshr - long shift right
;
;Purpose:
;       Does a unsigned Long Shift Right
;       Shifts a long right any number of bits.
;
;Entry:
;       EDX:EAX - long value to be shifted
;       CL    - number of bits to shift by
;
;Exit:
;       EDX:EAX - shifted value
;
;Uses:
;       CL is destroyed.
;
;Exceptions:
;
;*******************************************************************************
page
	public	__aullshr
__aullshr	proc

;
; Handle shifts of 64 bits or more (if shifting 64 bits or more, the result
; depends only on the high order bit of edx).
;
        cmp     cl,64
        jae     short RETZERO

;
; Handle shifts of between 0 and 31 bits
;
        cmp     cl, 32
        jae     short MORE32
        shrd    eax,edx,cl
        shr     edx,cl
        ret

;
; Handle shifts of between 32 and 63 bits
;
MORE32:
        mov     eax,edx
        xor     edx,edx
        and     cl,31
        shr     eax,cl
        ret

;
; return 0 in edx:eax
;
RETZERO:
        xor     eax,eax
        xor     edx,edx
        ret

__aullshr        endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

page
;***
;_chkstk - check stack upon procedure entry
;
;Purpose:
;       Provide stack checking on procedure entry. Method is to simply probe
;       each page of memory required for the stack in descending order. This
;       causes the necessary pages of memory to be allocated via the guard
;       page scheme, if possible. In the event of failure, the OS raises the
;       _XCPT_UNABLE_TO_GROW_STACK exception.
;
;       NOTE:  Currently, the (EAX < _PAGESIZE_) code path falls through
;       to the "lastpage" label of the (EAX >= _PAGESIZE_) code path.  This
;       is small; a minor speed optimization would be to special case
;       this up top.  This would avoid the painful save/restore of
;       ecx and would shorten the code path by 4-6 instructions.
;
;Entry:
;       EAX = size of local frame
;
;Exit:
;       ESP = new stackframe, if successful
;
;Uses:
;       EAX
;
;Exceptions:
;       _XCPT_GUARD_PAGE_VIOLATION - May be raised on a page probe. NEVER TRAP
;                                    THIS!!!! It is used by the OS to grow the
;                                    stack on demand.
;       _XCPT_UNABLE_TO_GROW_STACK - The stack cannot be grown. More precisely,
;                                    the attempt by the OS memory manager to
;                                    allocate another guard page in response
;                                    to a _XCPT_GUARD_PAGE_VIOLATION has
;                                    failed.
;
;*******************************************************************************

_PAGESIZE_      equ     1000h

	public __chkstk

__chkstk proc

	public	_alloca_probe
_alloca_probe    =  __chkstk

        push    ecx

; Calculate new TOS.

        lea     ecx, [esp] + 8 - 4      ; TOS before entering function + size for ret value
        sub     ecx, eax                ; new TOS

; Handle allocation size that results in wraparound.
; Wraparound will result in StackOverflow exception.

        sbb     eax, eax                ; 0 if CF==0, ~0 if CF==1
        not     eax                     ; ~0 if TOS did not wrapped around, 0 otherwise
        and     ecx, eax                ; set to 0 if wraparound

        mov     eax, esp                ; current TOS
        and     eax, not ( _PAGESIZE_ - 1) ; Round down to current page boundary

cs10:
        cmp     ecx, eax                ; Is new TOS
        jb      short cs20              ; in probed page?
        mov     eax, ecx                ; yes.
        pop     ecx
        xchg    esp, eax                ; update esp
        mov     eax, dword ptr [eax]    ; get return address
        mov     dword ptr [esp], eax    ; and put it at new TOS
        ret

; Find next lower page and probe
cs20:
        sub     eax, _PAGESIZE_         ; decrease by PAGESIZE
        test    dword ptr [eax],eax     ; probe page.
        jmp     short cs10

__chkstk endp

   public __alloca_probe_16 
__alloca_probe_16 proc near

arg_0  = dword ptr  8
   push    ecx
   lea     ecx, [esp+arg_0]
   sub     ecx, eax
   and     ecx, 0Fh
   add     eax, ecx
   sbb     ecx, ecx
   or      eax, ecx
   pop     ecx
   jmp     near ptr __chkstk

__alloca_probe_16 endp

   public __alloca_probe_8
__alloca_probe_8 proc near
arg_0           = dword ptr  8
   push    ecx
   lea     ecx, [esp+arg_0]
   sub     ecx, eax
   and     ecx, 7
   add     eax, ecx
   sbb     ecx, ecx
   or      eax, ecx
   pop     ecx
   jmp     near ptr __chkstk

__alloca_probe_8 endp


DAT_ADDR_SZ =   4
BDAT_ADDR_SZ =  2

TXT_ADDR_SZ =   4

; Big/Little Endian Definitions for Long Integers

ifdef   bigend                  ; Big Endian (hi word at low address)
LOWORD  equ     [4]
HIWORD  equ     [0]
else                            ; Little Endian (low word at low address)
LOWORD  equ     [0]
HIWORD  equ     [4]
endif


; All Model Definitions

BPARGBAS equ    TXT_ADDR_SZ+4   ; offset from BP to first argument


;***
;llmul - long multiply routine
;
;Purpose:
;       Does a long multiply (same for signed/unsigned)
;       Parameters are not changed.
;
;Entry:
;       Parameters are passed on the stack:
;               1st pushed: multiplier (QWORD)
;               2nd pushed: multiplicand (QWORD)
;
;Exit:
;       EDX:EAX - product of multiplier and multiplicand
;       NOTE: parameters are removed from the stack
;
;Uses:
;       ECX
;
;Exceptions:
;
;*******************************************************************************

	public	__allmul
__allmul PROC NEAR

A       EQU     [esp + 4]       ; stack address of a
B       EQU     [esp + 12]      ; stack address of b

;
;       AHI, BHI : upper 32 bits of A and B
;       ALO, BLO : lower 32 bits of A and B
;
;             ALO * BLO
;       ALO * BHI
; +     BLO * AHI
; ---------------------
;

        mov     eax,HIWORD(A)
        mov     ecx,HIWORD(B)
        or      ecx,eax         ;test for both hiwords zero.
        mov     ecx,LOWORD(B)
        jnz     short hard      ;both are zero, just mult ALO and BLO

        mov     eax,LOWORD(A)
        mul     ecx

        ret     16              ; callee restores the stack

hard:
        push    ebx

; must redefine A and B since esp has been altered

A2      EQU     [esp + 8]       ; stack address of a
B2      EQU     [esp + 16]      ; stack address of b

        mul     ecx             ;eax has AHI, ecx has BLO, so AHI * BLO
        mov     ebx,eax         ;save result

        mov     eax,LOWORD(A2)
        mul     dword ptr HIWORD(B2) ;ALO * BHI
        add     ebx,eax         ;ebx = ((ALO * BHI) + (AHI * BLO))

        mov     eax,LOWORD(A2)  ;ecx = BLO
        mul     ecx             ;so edx:eax = ALO*BLO
        add     edx,ebx         ;now edx has all the LO*HI stuff

        pop     ebx

        ret     16              ; callee restores the stack

__allmul ENDP


;***
;lldiv - signed long divide
;
;Purpose:
;       Does a signed long divide of the arguments.  Arguments are
;       not changed.
;
;Entry:
;       Arguments are passed on the stack:
;               1st pushed: divisor (QWORD)
;               2nd pushed: dividend (QWORD)
;
;Exit:
;       EDX:EAX contains the quotient (dividend/divisor)
;       NOTE: this routine removes the parameters from the stack.
;
;Uses:
;       ECX
;
;Exceptions:
;
;*******************************************************************************
	public __alldiv
__alldiv PROC NEAR

        push    edi
        push    esi
        push    ebx

; Set up the local stack and save the index registers.  When this is done
; the stack frame will look as follows (assuming that the expression a/b will
; generate a call to lldiv(a, b)):
;
;               -----------------
;               |               |
;               |---------------|
;               |               |
;               |--divisor (b)--|
;               |               |
;               |---------------|
;               |               |
;               |--dividend (a)-|
;               |               |
;               |---------------|
;               | return addr** |
;               |---------------|
;               |      EDI      |
;               |---------------|
;               |      ESI      |
;               |---------------|
;       ESP---->|      EBX      |
;               -----------------
;

DVND    equ     [esp + 16]      ; stack address of dividend (a)
DVSR    equ     [esp + 24]      ; stack address of divisor (b)


; Determine sign of the result (edi = 0 if result is positive, non-zero
; otherwise) and make operands positive.

        xor     edi,edi         ; result sign assumed positive

        mov     eax,HIWORD(DVND) ; hi word of a
        or      eax,eax         ; test to see if signed
        jge     short L1        ; skip rest if a is already positive
        inc     edi             ; complement result sign flag
        mov     edx,LOWORD(DVND) ; lo word of a
        neg     eax             ; make a positive
        neg     edx
        sbb     eax,0
        mov     HIWORD(DVND),eax ; save positive value
        mov     LOWORD(DVND),edx
L1:
        mov     eax,HIWORD(DVSR) ; hi word of b
        or      eax,eax         ; test to see if signed
        jge     short L2        ; skip rest if b is already positive
        inc     edi             ; complement the result sign flag
        mov     edx,LOWORD(DVSR) ; lo word of a
        neg     eax             ; make b positive
        neg     edx
        sbb     eax,0
        mov     HIWORD(DVSR),eax ; save positive value
        mov     LOWORD(DVSR),edx
L2:

;
; Now do the divide.  First look to see if the divisor is less than 4194304K.
; If so, then we can use a simple algorithm with word divides, otherwise
; things get a little more complex.
;
; NOTE - eax currently contains the high order word of DVSR
;

        or      eax,eax         ; check to see if divisor < 4194304K
        jnz     short L3        ; nope, gotta do this the hard way
        mov     ecx,LOWORD(DVSR) ; load divisor
        mov     eax,HIWORD(DVND) ; load high word of dividend
        xor     edx,edx
        div     ecx             ; eax <- high order bits of quotient
        mov     ebx,eax         ; save high bits of quotient
        mov     eax,LOWORD(DVND) ; edx:eax <- remainder:lo word of dividend
        div     ecx             ; eax <- low order bits of quotient
        mov     edx,ebx         ; edx:eax <- quotient
        jmp     short L4        ; set sign, restore stack and return

;
; Here we do it the hard way.  Remember, eax contains the high word of DVSR
;

L3:
        mov     ebx,eax         ; ebx:ecx <- divisor
        mov     ecx,LOWORD(DVSR)
        mov     edx,HIWORD(DVND) ; edx:eax <- dividend
        mov     eax,LOWORD(DVND)
L5:
        shr     ebx,1           ; shift divisor right one bit
        rcr     ecx,1
        shr     edx,1           ; shift dividend right one bit
        rcr     eax,1
        or      ebx,ebx
        jnz     short L5        ; loop until divisor < 4194304K
        div     ecx             ; now divide, ignore remainder
        mov     esi,eax         ; save quotient

;
; We may be off by one, so to check, we will multiply the quotient
; by the divisor and check the result against the orignal dividend
; Note that we must also check for overflow, which can occur if the
; dividend is close to 2**64 and the quotient is off by 1.
;

        mul     dword ptr HIWORD(DVSR) ; QUOT * HIWORD(DVSR)
        mov     ecx,eax
        mov     eax,LOWORD(DVSR)
        mul     esi             ; QUOT * LOWORD(DVSR)
        add     edx,ecx         ; EDX:EAX = QUOT * DVSR
        jc      short L6        ; carry means Quotient is off by 1

;
; do long compare here between original dividend and the result of the
; multiply in edx:eax.  If original is larger or equal, we are ok, otherwise
; subtract one (1) from the quotient.
;

        cmp     edx,HIWORD(DVND) ; compare hi words of result and original
        ja      short L6        ; if result > original, do subtract
        jb      short L7        ; if result < original, we are ok
        cmp     eax,LOWORD(DVND) ; hi words are equal, compare lo words
        jbe     short L7        ; if less or equal we are ok, else subtract
L6:
        dec     esi             ; subtract 1 from quotient
L7:
        xor     edx,edx         ; edx:eax <- quotient
        mov     eax,esi

;
; Just the cleanup left to do.  edx:eax contains the quotient.  Set the sign
; according to the save value, cleanup the stack, and return.
;

L4:
        dec     edi             ; check to see if result is negative
        jnz     short L8        ; if EDI == 0, result should be negative
        neg     edx             ; otherwise, negate the result
        neg     eax
        sbb     edx,0

;
; Restore the saved registers and return.
;

L8:
        pop     ebx
        pop     esi
        pop     edi

        ret     16

__alldiv ENDP


	public __alldvrm
__alldvrm PROC NEAR

        push    edi
        push    esi
        push    ebp

; Set up the local stack and save the index registers.  When this is done
; the stack frame will look as follows (assuming that the expression a/b will
; generate a call to alldvrm(a, b)):
;
;               -----------------
;               |               |
;               |---------------|
;               |               |
;               |--divisor (b)--|
;               |               |
;               |---------------|
;               |               |
;               |--dividend (a)-|
;               |               |
;               |---------------|
;               | return addr** |
;               |---------------|
;               |      EDI      |
;               |---------------|
;               |      ESI      |
;               |---------------|
;       ESP---->|      EBP      |
;               -----------------
;

DVND    equ     [esp + 16]      ; stack address of dividend (a)
DVSR    equ     [esp + 24]      ; stack address of divisor (b)


; Determine sign of the quotient (edi = 0 if result is positive, non-zero
; otherwise) and make operands positive.
; Sign of the remainder is kept in ebp.

        xor     edi,edi         ; result sign assumed positive
        xor     ebp,ebp         ; result sign assumed positive

        mov     eax,HIWORD(DVND) ; hi word of a
        or      eax,eax         ; test to see if signed
        jge     short L1        ; skip rest if a is already positive
        inc     edi             ; complement result sign flag
        inc     ebp             ; complement result sign flag
        mov     edx,LOWORD(DVND) ; lo word of a
        neg     eax             ; make a positive
        neg     edx
        sbb     eax,0
        mov     HIWORD(DVND),eax ; save positive value
        mov     LOWORD(DVND),edx
L1:
        mov     eax,HIWORD(DVSR) ; hi word of b
        or      eax,eax         ; test to see if signed
        jge     short L2        ; skip rest if b is already positive
        inc     edi             ; complement the result sign flag
        mov     edx,LOWORD(DVSR) ; lo word of a
        neg     eax             ; make b positive
        neg     edx
        sbb     eax,0
        mov     HIWORD(DVSR),eax ; save positive value
        mov     LOWORD(DVSR),edx
L2:

;
; Now do the divide.  First look to see if the divisor is less than 4194304K.
; If so, then we can use a simple algorithm with word divides, otherwise
; things get a little more complex.
;
; NOTE - eax currently contains the high order word of DVSR
;

        or      eax,eax         ; check to see if divisor < 4194304K
        jnz     short L3        ; nope, gotta do this the hard way
        mov     ecx,LOWORD(DVSR) ; load divisor
        mov     eax,HIWORD(DVND) ; load high word of dividend
        xor     edx,edx
        div     ecx             ; eax <- high order bits of quotient
        mov     ebx,eax         ; save high bits of quotient
        mov     eax,LOWORD(DVND) ; edx:eax <- remainder:lo word of dividend
        div     ecx             ; eax <- low order bits of quotient
        mov     esi,eax         ; ebx:esi <- quotient
;
; Now we need to do a multiply so that we can compute the remainder.
;
        mov     eax,ebx         ; set up high word of quotient
        mul     dword ptr LOWORD(DVSR) ; HIWORD(QUOT) * DVSR
        mov     ecx,eax         ; save the result in ecx
        mov     eax,esi         ; set up low word of quotient
        mul     dword ptr LOWORD(DVSR) ; LOWORD(QUOT) * DVSR
        add     edx,ecx         ; EDX:EAX = QUOT * DVSR
        jmp     short L4        ; complete remainder calculation

;
; Here we do it the hard way.  Remember, eax contains the high word of DVSR
;

L3:
        mov     ebx,eax         ; ebx:ecx <- divisor
        mov     ecx,LOWORD(DVSR)
        mov     edx,HIWORD(DVND) ; edx:eax <- dividend
        mov     eax,LOWORD(DVND)
L5:
        shr     ebx,1           ; shift divisor right one bit
        rcr     ecx,1
        shr     edx,1           ; shift dividend right one bit
        rcr     eax,1
        or      ebx,ebx
        jnz     short L5        ; loop until divisor < 4194304K
        div     ecx             ; now divide, ignore remainder
        mov     esi,eax         ; save quotient

;
; We may be off by one, so to check, we will multiply the quotient
; by the divisor and check the result against the orignal dividend
; Note that we must also check for overflow, which can occur if the
; dividend is close to 2**64 and the quotient is off by 1.
;

        mul     dword ptr HIWORD(DVSR) ; QUOT * HIWORD(DVSR)
        mov     ecx,eax
        mov     eax,LOWORD(DVSR)
        mul     esi             ; QUOT * LOWORD(DVSR)
        add     edx,ecx         ; EDX:EAX = QUOT * DVSR
        jc      short L6        ; carry means Quotient is off by 1

;
; do long compare here between original dividend and the result of the
; multiply in edx:eax.  If original is larger or equal, we are ok, otherwise
; subtract one (1) from the quotient.
;

        cmp     edx,HIWORD(DVND) ; compare hi words of result and original
        ja      short L6        ; if result > original, do subtract
        jb      short L7        ; if result < original, we are ok
        cmp     eax,LOWORD(DVND) ; hi words are equal, compare lo words
        jbe     short L7        ; if less or equal we are ok, else subtract
L6:
        dec     esi             ; subtract 1 from quotient
        sub     eax,LOWORD(DVSR) ; subtract divisor from result
        sbb     edx,HIWORD(DVSR)
L7:
        xor     ebx,ebx         ; ebx:esi <- quotient

L4:
;
; Calculate remainder by subtracting the result from the original dividend.
; Since the result is already in a register, we will do the subtract in the
; opposite direction and negate the result if necessary.
;

        sub     eax,LOWORD(DVND) ; subtract dividend from result
        sbb     edx,HIWORD(DVND)

;
; Now check the result sign flag to see if the result is supposed to be positive
; or negative.  It is currently negated (because we subtracted in the 'wrong'
; direction), so if the sign flag is set we are done, otherwise we must negate
; the result to make it positive again.
;

        dec     ebp             ; check result sign flag
        jns     short L9        ; result is ok, set up the quotient
        neg     edx             ; otherwise, negate the result
        neg     eax
        sbb     edx,0

;
; Now we need to get the quotient into edx:eax and the remainder into ebx:ecx.
;
L9:
        mov     ecx,edx
        mov     edx,ebx
        mov     ebx,ecx
        mov     ecx,eax
        mov     eax,esi

;
; Just the cleanup left to do.  edx:eax contains the quotient.  Set the sign
; according to the save value, cleanup the stack, and return.
;

        dec     edi             ; check to see if result is negative
        jnz     short L8        ; if EDI == 0, result should be negative
        neg     edx             ; otherwise, negate the result
        neg     eax
        sbb     edx,0

;
; Restore the saved registers and return.
;

L8:
        pop     ebp
        pop     esi
        pop     edi

        ret     16

__alldvrm ENDP


page
;***
;llshl - long shift left
;
;Purpose:
;       Does a Long Shift Left (signed and unsigned are identical)
;       Shifts a long left any number of bits.
;
;Entry:
;       EDX:EAX - long value to be shifted
;       CL    - number of bits to shift by
;
;Exit:
;       EDX:EAX - shifted value
;
;Uses:
;       CL is destroyed.
;
;Exceptions:
;
;*******************************************************************************

;.code

	public __allshl
__allshl proc

;
; Handle shifts of 64 or more bits (all get 0)
;
        cmp     cl, 64
        jae     short RETZERO

;
; Handle shifts of between 0 and 31 bits
;
        cmp     cl, 32
        jae     short MORE32
        shld    edx,eax,cl
        shl     eax,cl
        ret

;
; Handle shifts of between 32 and 63 bits
;
MORE32:
        mov     edx,eax
        xor     eax,eax
        and     cl,31
        shl     edx,cl
        ret

;
; return 0 in edx:eax
;
RETZERO:
        xor     eax,eax
        xor     edx,edx
        ret

__allshl endp

page
;***
;ulldiv - unsigned long divide
;
;Purpose:
;       Does a unsigned long divide of the arguments.  Arguments are
;       not changed.
;
;Entry:
;       Arguments are passed on the stack:
;               1st pushed: divisor (QWORD)
;               2nd pushed: dividend (QWORD)
;
;Exit:
;       EDX:EAX contains the quotient (dividend/divisor)
;       NOTE: this routine removes the parameters from the stack.
;
;Uses:
;       ECX
;
;Exceptions:
;
;*******************************************************************************

;.code

	public	__aulldiv
__aulldiv        proc

        push    ebx
        push    esi

; Set up the local stack and save the index registers.  When this is done
; the stack frame will look as follows (assuming that the expression a/b will
; generate a call to uldiv(a, b)):
;
;               -----------------
;               |               |
;               |---------------|
;               |               |
;               |--divisor (b)--|
;               |               |
;               |---------------|
;               |               |
;               |--dividend (a)-|
;               |               |
;               |---------------|
;               | return addr** |
;               |---------------|
;               |      EBX      |
;               |---------------|
;       ESP---->|      ESI      |
;               -----------------
;

DVND    equ     [esp + 12]      ; stack address of dividend (a)
DVSR    equ     [esp + 20]      ; stack address of divisor (b)

;
; Now do the divide.  First look to see if the divisor is less than 4194304K.
; If so, then we can use a simple algorithm with word divides, otherwise
; things get a little more complex.
;

        mov     eax,HIWORD(DVSR) ; check to see if divisor < 4194304K
        or      eax,eax
        jnz     short L1        ; nope, gotta do this the hard way
        mov     ecx,LOWORD(DVSR) ; load divisor
        mov     eax,HIWORD(DVND) ; load high word of dividend
        xor     edx,edx
        div     ecx             ; get high order bits of quotient
        mov     ebx,eax         ; save high bits of quotient
        mov     eax,LOWORD(DVND) ; edx:eax <- remainder:lo word of dividend
        div     ecx             ; get low order bits of quotient
        mov     edx,ebx         ; edx:eax <- quotient hi:quotient lo
        jmp     short L2        ; restore stack and return

;
; Here we do it the hard way.  Remember, eax contains DVSRHI
;

L1:
        mov     ecx,eax         ; ecx:ebx <- divisor
        mov     ebx,LOWORD(DVSR)
        mov     edx,HIWORD(DVND) ; edx:eax <- dividend
        mov     eax,LOWORD(DVND)
L3:
        shr     ecx,1           ; shift divisor right one bit; hi bit <- 0
        rcr     ebx,1
        shr     edx,1           ; shift dividend right one bit; hi bit <- 0
        rcr     eax,1
        or      ecx,ecx
        jnz     short L3        ; loop until divisor < 4194304K
        div     ebx             ; now divide, ignore remainder
        mov     esi,eax         ; save quotient

;
; We may be off by one, so to check, we will multiply the quotient
; by the divisor and check the result against the orignal dividend
; Note that we must also check for overflow, which can occur if the
; dividend is close to 2**64 and the quotient is off by 1.
;

        mul     dword ptr HIWORD(DVSR) ; QUOT * HIWORD(DVSR)
        mov     ecx,eax
        mov     eax,LOWORD(DVSR)
        mul     esi             ; QUOT * LOWORD(DVSR)
        add     edx,ecx         ; EDX:EAX = QUOT * DVSR
        jc      short L4        ; carry means Quotient is off by 1

;
; do long compare here between original dividend and the result of the
; multiply in edx:eax.  If original is larger or equal, we are ok, otherwise
; subtract one (1) from the quotient.
;

        cmp     edx,HIWORD(DVND) ; compare hi words of result and original
        ja      short L4        ; if result > original, do subtract
        jb      short L5        ; if result < original, we are ok
        cmp     eax,LOWORD(DVND) ; hi words are equal, compare lo words
        jbe     short L5        ; if less or equal we are ok, else subtract
L4:
        dec     esi             ; subtract 1 from quotient
L5:
        xor     edx,edx         ; edx:eax <- quotient
        mov     eax,esi

;
; Just the cleanup left to do.  edx:eax contains the quotient.
; Restore the saved registers and return.
;

L2:

        pop     esi
        pop     ebx

        ret     16

__aulldiv        endp


;***
;ullrem - unsigned long remainder
;
;Purpose:
;       Does a unsigned long remainder of the arguments.  Arguments are
;       not changed.
;
;Entry:
;       Arguments are passed on the stack:
;               1st pushed: divisor (QWORD)
;               2nd pushed: dividend (QWORD)
;
;Exit:
;       EDX:EAX contains the remainder (dividend%divisor)
;       NOTE: this routine removes the parameters from the stack.
;
;Uses:
;       ECX
;
;Exceptions:
;
;*******************************************************************************

;.code
	public	__aullrem
__aullrem        proc

        push    ebx

; Set up the local stack and save the index registers.  When this is done
; the stack frame will look as follows (assuming that the expression a%b will
; generate a call to ullrem(a, b)):
;
;               -----------------
;               |               |
;               |---------------|
;               |               |
;               |--divisor (b)--|
;               |               |
;               |---------------|
;               |               |
;               |--dividend (a)-|
;               |               |
;               |---------------|
;               | return addr** |
;               |---------------|
;       ESP---->|      EBX      |
;               -----------------
;

DVND    equ     [esp + 8]       ; stack address of dividend (a)
DVSR    equ     [esp + 16]      ; stack address of divisor (b)

; Now do the divide.  First look to see if the divisor is less than 4194304K.
; If so, then we can use a simple algorithm with word divides, otherwise
; things get a little more complex.
;

        mov     eax,HIWORD(DVSR) ; check to see if divisor < 4194304K
        or      eax,eax
        jnz     short L1        ; nope, gotta do this the hard way
        mov     ecx,LOWORD(DVSR) ; load divisor
        mov     eax,HIWORD(DVND) ; load high word of dividend
        xor     edx,edx
        div     ecx             ; edx <- remainder, eax <- quotient
        mov     eax,LOWORD(DVND) ; edx:eax <- remainder:lo word of dividend
        div     ecx             ; edx <- final remainder
        mov     eax,edx         ; edx:eax <- remainder
        xor     edx,edx
        jmp     short L2        ; restore stack and return

;
; Here we do it the hard way.  Remember, eax contains DVSRHI
;

L1:
        mov     ecx,eax         ; ecx:ebx <- divisor
        mov     ebx,LOWORD(DVSR)
        mov     edx,HIWORD(DVND) ; edx:eax <- dividend
        mov     eax,LOWORD(DVND)
L3:
        shr     ecx,1           ; shift divisor right one bit; hi bit <- 0
        rcr     ebx,1
        shr     edx,1           ; shift dividend right one bit; hi bit <- 0
        rcr     eax,1
        or      ecx,ecx
        jnz     short L3        ; loop until divisor < 4194304K
        div     ebx             ; now divide, ignore remainder

;
; We may be off by one, so to check, we will multiply the quotient
; by the divisor and check the result against the orignal dividend
; Note that we must also check for overflow, which can occur if the
; dividend is close to 2**64 and the quotient is off by 1.
;

        mov     ecx,eax         ; save a copy of quotient in ECX
        mul     dword ptr HIWORD(DVSR)
        xchg    ecx,eax         ; put partial product in ECX, get quotient in EAX
        mul     dword ptr LOWORD(DVSR)
        add     edx,ecx         ; EDX:EAX = QUOT * DVSR
        jc      short L4        ; carry means Quotient is off by 1

;
; do long compare here between original dividend and the result of the
; multiply in edx:eax.  If original is larger or equal, we're ok, otherwise
; subtract the original divisor from the result.
;

        cmp     edx,HIWORD(DVND) ; compare hi words of result and original
        ja      short L4        ; if result > original, do subtract
        jb      short L5        ; if result < original, we're ok
        cmp     eax,LOWORD(DVND) ; hi words are equal, compare lo words
        jbe     short L5        ; if less or equal we're ok, else subtract
L4:
        sub     eax,LOWORD(DVSR) ; subtract divisor from result
        sbb     edx,HIWORD(DVSR)
L5:

;
; Calculate remainder by subtracting the result from the original dividend.
; Since the result is already in a register, we will perform the subtract in
; the opposite direction and negate the result to make it positive.
;

        sub     eax,LOWORD(DVND) ; subtract original dividend from result
        sbb     edx,HIWORD(DVND)
        neg     edx             ; and negate it
        neg     eax
        sbb     edx,0

;
; Just the cleanup left to do.  dx:ax contains the remainder.
; Restore the saved registers and return.
;

L2:

        pop     ebx

        ret     16

__aullrem        endp


;***
;llshr - long shift right
;
;Purpose:
;       Does a signed Long Shift Right
;       Shifts a long right any number of bits.
;
;Entry:
;       EDX:EAX - long value to be shifted
;       CL    - number of bits to shift by
;
;Exit:
;       EDX:EAX - shifted value
;
;Uses:
;       CL is destroyed.
;
;Exceptions:
;
;*******************************************************************************

;.code
	public __allshr
__allshr	proc

;
; Handle shifts of 64 bits or more (if shifting 64 bits or more, the result
; depends only on the high order bit of edx).
;
        cmp     cl,64
        jae     short RETSIGN

;
; Handle shifts of between 0 and 31 bits
;
        cmp     cl, 32
        jae     short MORE32
        shrd    eax,edx,cl
        sar     edx,cl
        ret

;
; Handle shifts of between 32 and 63 bits
;
MORE32:
        mov     eax,edx
        sar     edx,31
        and     cl,31
        sar     eax,cl
        ret

;
; Return double precision 0 or -1, depending on the sign of edx
;
RETSIGN:
        sar     edx,31
        mov     eax,edx
        ret

__allshr endp


;***
;llrem - signed long remainder
;
;Purpose:
;       Does a signed long remainder of the arguments.  Arguments are
;       not changed.
;
;Entry:
;       Arguments are passed on the stack:
;               1st pushed: divisor (QWORD)
;               2nd pushed: dividend (QWORD)
;
;Exit:
;       EDX:EAX contains the remainder (dividend%divisor)
;       NOTE: this routine removes the parameters from the stack.
;
;Uses:
;       ECX
;
;Exceptions:
;
;*******************************************************************************

;.code

	public	__allrem
__allrem	proc

        push    ebx
        push    edi

; Set up the local stack and save the index registers.  When this is done
; the stack frame will look as follows (assuming that the expression a%b will
; generate a call to lrem(a, b)):
;
;               -----------------
;               |               |
;               |---------------|
;               |               |
;               |--divisor (b)--|
;               |               |
;               |---------------|
;               |               |
;               |--dividend (a)-|
;               |               |
;               |---------------|
;               | return addr** |
;               |---------------|
;               |       EBX     |
;               |---------------|
;       ESP---->|       EDI     |
;               -----------------
;

DVND    equ     [esp + 12]      ; stack address of dividend (a)
DVSR    equ     [esp + 20]      ; stack address of divisor (b)


; Determine sign of the result (edi = 0 if result is positive, non-zero
; otherwise) and make operands positive.

        xor     edi,edi         ; result sign assumed positive

        mov     eax,HIWORD(DVND) ; hi word of a
        or      eax,eax         ; test to see if signed
        jge     short L1        ; skip rest if a is already positive
        inc     edi             ; complement result sign flag bit
        mov     edx,LOWORD(DVND) ; lo word of a
        neg     eax             ; make a positive
        neg     edx
        sbb     eax,0
        mov     HIWORD(DVND),eax ; save positive value
        mov     LOWORD(DVND),edx
L1:
        mov     eax,HIWORD(DVSR) ; hi word of b
        or      eax,eax         ; test to see if signed
        jge     short L2        ; skip rest if b is already positive
        mov     edx,LOWORD(DVSR) ; lo word of b
        neg     eax             ; make b positive
        neg     edx
        sbb     eax,0
        mov     HIWORD(DVSR),eax ; save positive value
        mov     LOWORD(DVSR),edx
L2:

;
; Now do the divide.  First look to see if the divisor is less than 4194304K.
; If so, then we can use a simple algorithm with word divides, otherwise
; things get a little more complex.
;
; NOTE - eax currently contains the high order word of DVSR
;

        or      eax,eax         ; check to see if divisor < 4194304K
        jnz     short L3        ; nope, gotta do this the hard way
        mov     ecx,LOWORD(DVSR) ; load divisor
        mov     eax,HIWORD(DVND) ; load high word of dividend
        xor     edx,edx
        div     ecx             ; edx <- remainder
        mov     eax,LOWORD(DVND) ; edx:eax <- remainder:lo word of dividend
        div     ecx             ; edx <- final remainder
        mov     eax,edx         ; edx:eax <- remainder
        xor     edx,edx
        dec     edi             ; check result sign flag
        jns     short L4        ; negate result, restore stack and return
        jmp     short L8        ; result sign ok, restore stack and return

;
; Here we do it the hard way.  Remember, eax contains the high word of DVSR
;

L3:
        mov     ebx,eax         ; ebx:ecx <- divisor
        mov     ecx,LOWORD(DVSR)
        mov     edx,HIWORD(DVND) ; edx:eax <- dividend
        mov     eax,LOWORD(DVND)
L5:
        shr     ebx,1           ; shift divisor right one bit
        rcr     ecx,1
        shr     edx,1           ; shift dividend right one bit
        rcr     eax,1
        or      ebx,ebx
        jnz     short L5        ; loop until divisor < 4194304K
        div     ecx             ; now divide, ignore remainder

;
; We may be off by one, so to check, we will multiply the quotient
; by the divisor and check the result against the orignal dividend
; Note that we must also check for overflow, which can occur if the
; dividend is close to 2**64 and the quotient is off by 1.
;

        mov     ecx,eax         ; save a copy of quotient in ECX
        mul     dword ptr HIWORD(DVSR)
        xchg    ecx,eax         ; save product, get quotient in EAX
        mul     dword ptr LOWORD(DVSR)
        add     edx,ecx         ; EDX:EAX = QUOT * DVSR
        jc      short L6        ; carry means Quotient is off by 1

;
; do long compare here between original dividend and the result of the
; multiply in edx:eax.  If original is larger or equal, we are ok, otherwise
; subtract the original divisor from the result.
;

        cmp     edx,HIWORD(DVND) ; compare hi words of result and original
        ja      short L6        ; if result > original, do subtract
        jb      short L7        ; if result < original, we are ok
        cmp     eax,LOWORD(DVND) ; hi words are equal, compare lo words
        jbe     short L7        ; if less or equal we are ok, else subtract
L6:
        sub     eax,LOWORD(DVSR) ; subtract divisor from result
        sbb     edx,HIWORD(DVSR)
L7:

;
; Calculate remainder by subtracting the result from the original dividend.
; Since the result is already in a register, we will do the subtract in the
; opposite direction and negate the result if necessary.
;

        sub     eax,LOWORD(DVND) ; subtract dividend from result
        sbb     edx,HIWORD(DVND)

;
; Now check the result sign flag to see if the result is supposed to be positive
; or negative.  It is currently negated (because we subtracted in the 'wrong'
; direction), so if the sign flag is set we are done, otherwise we must negate
; the result to make it positive again.
;

        dec     edi             ; check result sign flag
        jns     short L8        ; result is ok, restore stack and return
L4:
        neg     edx             ; otherwise, negate the result
        neg     eax
        sbb     edx,0

;
; Just the cleanup left to do.  edx:eax contains the quotient.
; Restore the saved registers and return.
;

L8:
        pop     edi
        pop     ebx

        ret     16

__allrem endp

end

