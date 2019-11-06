;
;    \ \____/ /  \ \
;   _/ / __ \ \__/ /     ia32traps.asm - CPU faults and traps handlers
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
extern sv_handle_divide_error
ENTRY sv_idt_handle_e0
    cli
    SAVE_CTX
    mov eax, sv_handle_divide_error
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_debug
ENTRY sv_idt_handle_e1
    cli
    SAVE_CTX
    mov eax, sv_handle_debug
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_nmi
ENTRY sv_idt_handle_e2
    cli
    SAVE_CTX
    mov eax, sv_handle_nmi
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_breakpoint
ENTRY sv_idt_handle_e3
    cli
    SAVE_CTX
    mov eax, sv_handle_breakpoint
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_overflow
ENTRY sv_idt_handle_e4
    cli
    SAVE_CTX
    mov eax, sv_handle_overflow
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_bounds
ENTRY sv_idt_handle_e5
    cli
    SAVE_CTX
    mov eax, sv_handle_bounds
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_invalid_op
ENTRY sv_idt_handle_e6
    cli
    SAVE_CTX
    mov eax, sv_handle_invalid_op
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_device_not_avaiable
ENTRY sv_idt_handle_e7
    cli
    SAVE_CTX
    mov eax, sv_handle_device_not_avaiable
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_double_fault
ENTRY sv_idt_handle_e8
    cli
    SAVE_CTX
    mov eax, sv_handle_double_fault
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_coproc_seg_overrun
ENTRY sv_idt_handle_e9
    cli
    SAVE_CTX
    mov eax, sv_handle_coproc_seg_overrun
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_inv_tss
ENTRY sv_idt_handle_e10
    cli
    SAVE_CTX
    mov eax, sv_handle_inv_tss
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_seg_not_present
ENTRY sv_idt_handle_e11
    cli
    SAVE_CTX
    mov eax, sv_handle_seg_not_present
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_ss
ENTRY sv_idt_handle_e12
    cli
    SAVE_CTX
    mov eax, sv_handle_ss
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_gp
ENTRY sv_idt_handle_e13
    cli
    SAVE_CTX
    mov eax, sv_handle_gp
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_pf
ENTRY sv_idt_handle_e14
    cli
    SAVE_CTX
    mov eax, sv_handle_pf
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_fpe
ENTRY sv_idt_handle_e16
    cli
    SAVE_CTX
    mov eax, sv_handle_fpe
    call eax
    RETR_CTX
    iret

;==============================================================================
;==============================================================================
extern sv_handle_alignment_check
ENTRY sv_idt_handle_e17
    cli
    SAVE_CTX
    mov eax, sv_handle_alignment_check
    call eax
    RETR_CTX
    iret

