;
;    \ \____/ /  \ \
;   _/ / __ \ \__/ /     ia32init.asm - system initialization for IA-32
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
; constants
;==============================================================================
; This is the size for the initial stack for the supervisor process
STACKSIZE equ 65536

;==============================================================================
; multiboot header
;==============================================================================
FLAGS       equ  0x00
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .text
ALIGN 4
mbheader:
   dd MAGIC
   dd FLAGS
   dd CHECKSUM

;==============================================================================
; This is the entry point to the supervisor, the first function called upon
; booting up.
; Initializes the low-level hardware settings and then calls the sv_init
; to finish setting up the scheduler and other higher-level data structures.
; Finally, control is transfered to the idle task.
;==============================================================================
extern sv_init
extern ia32_gdt_init
extern ia32_idt_init
extern ia32_remap_irq
extern ia32_irq_init
extern ia32_setup_pli
extern ia32_idle_task

ENTRY sv_startup
    mov  esp, sv_stack              ; set up the stack
    cli                             ; disable interrupts during initialization
                                    ; interrupts are reenabled in sv_task()
    ; GDT initialization
    call ia32_gdt_init
    call ia32_gdt_load_gdtreg

    ; IDT initialization
    call ia32_idt_init
    call ia32_idt_load_idtreg

    ; IRQ remapping and initialization
    call ia32_remap_irq
    call ia32_irq_init
    call ia32_setup_pli

    ; hardware setup finished - initialize the high-level supervisor state
    call sv_init

    mov ax, SV_DATA_SEG_SEL
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, esp
    push SV_CODE_SEG_SEL
    push dword ia32_idle_task

    retf

;==============================================================================
; load the GDT register from the location at gdt_ptr (external variable)
;==============================================================================
extern gdt_ptr
ENTRY ia32_gdt_load_gdtreg
    lgdt [gdt_ptr]

    mov ax, SV_DATA_SEG_SEL  ; set all segment registers
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp SV_CODE_SEG_SEL:r0  ; far jump to set CS to the new code segment selector
r0:
    ret

;==============================================================================
; load the IDT register from the location at idt_ptr
;==============================================================================
extern idt_ptr
ENTRY ia32_idt_load_idtreg
    lidt [idt_ptr]
    ret

;==============================================================================
; Halts the system
;==============================================================================
ENTRY ia32_halt
    cli
loop0:
    hlt
    jmp loop0

;==============================================================================
; supervisor stack
;==============================================================================
SECTION .bss
align 4
   resb STACKSIZE
sv_stack:

