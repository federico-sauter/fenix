;
;    \ \____/ /  \ \
;   _/ / __ \ \__/ /     ia32irqs.asm - interrupt service request handlers for IA-32
;   __/ /  \ \____/
;   _ \ \__/ / __ \.     FENIX Kernel
;    \ \____/ /  \ \
;   _/ / __ \ \__/ /     Copyright(C) 2019 by Federico Sauter<f.sauter@gmail.com>
;   __/ /  \ \____/
;   _ \ \__/ / __ \.
;
;    This file is part of the FENIX Kernel.
;
;    The FENIX Kernel is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation, either version 3 of the License, or
;    (at your option) any later version.
;
;    The FENIX Kernel is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with the FENIX Kernel.  If not, see <http://www.gnu.org/licenses/>.
;

%include "ia32macros.asm"

[BITS 32]

;==============================================================================
;==============================================================================
ENTRY ia32_remap_irq
    mov al, 0x11
    out 0x20, al
    mov al, 0x11
    out 0xA0, al
    mov al, 0x20
    out 0x21, al
    mov al, 0x28
    out 0xA1, al
    mov al, 0x04
    out 0x21, al
    mov al, 0x02
    out 0xA1, al
    mov al, 0x01
    out 0x21, al
    mov al, 0x01
    out 0xA1, al
    mov al, 0x00
    out 0x21, al
    mov al, 0x00
    out 0xA1, al
    ret

;==============================================================================
;==============================================================================
extern sv_handle_keybd_irq
ENTRY sv_irq_handle_irq1
    cli
    SAVE_CTX
    mov eax, sv_handle_keybd_irq
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq2
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq3
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq4
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq5
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq6
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq7
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq8
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq9
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq10
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq11
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq12
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq13
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq14
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_idt_handle_irq_glbl
ENTRY sv_irq_handle_irq15
    cli
    SAVE_CTX
    mov ebx, 0
    push ebx
    push ebx
    mov eax, sv_idt_handle_irq_glbl
    call eax
    RETR_CTX
    iret

;==============================================================================
; The return code is stored in 
;==============================================================================
extern _ecx, _edx
extern sv_syscall_dispatch
extern syscall_rc
ENTRY sv_irq_handle_syscall_irq
    SAVE_CTX
    cli
    cld

    ; system call arguments
    mov eax, [_edx]
    push eax
    mov eax, [_ebx]
    push eax
    mov eax, [_ecx]
    push eax

    call sv_syscall_dispatch
    mov [syscall_rc], eax
    RETR_CTX
    sti
    iret
