;
; (c) Copyright 2012, MuThink Inc.  This source code is protected by
; license agreement and copyright.  It is property of MuThink Inc. and can not be used in
; any way without an express license agreement with MuThink Inc.  Modification of source
; code is also not allowed unless a license is purchased permitting changes.  Derived
; code must contain this notice and cannot be sold or released in source code form without
; permission from MuThink Inc.

.DATA

	PUBLIC  _fltused
 _fltused			EQU	9876h
 
.CODE

;-------------------- { TRAMPOLINE CALLS } --------------------------
   EXTRN __imp___CxxFrameHandler:qword  ; external memory addr

; TRAMPOLINE TO MSVCRT.DLL
   PUBLIC  __CxxFrameHandler3 
__CxxFrameHandler3 proc
   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp___CxxFrameHandler  ; Trampoline bounce 
__CxxFrameHandler3 endp

; TRAMPOLINE TO MSVCRT.DLL
PUBLIC  __CxxFrameHandler4
__CxxFrameHandler4 proc

   ; Jump indirect: Jumps to (*__imp__CxxFrameHandler)
   jmp  __imp___CxxFrameHandler  ; Trampoline bounce 
__CxxFrameHandler4 endp

END

