;
;    \ \____/ /  \ \
;   _/ / __ \ \__/ /     ia32syscall.asm - system call interface implementation
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

[BITS 32]

%include "ia32macros.asm"

;==============================================================================
;   Performs a system call using the INT 0x80.
;   The calling convention is:
;       ecx -> system call code
;       ebx -> argument0
;       edx -> argument1
;
;   The return value is placed into eax by the IRQ handler
;==============================================================================
extern syscall_rc
ENTRY ia32_do_syscall
    push ebp

    mov ebp, esp
    mov ecx, [ebp + 8]
    mov ebx, [ebp + 12]
    mov edx, [ebp + 16]

    int 0x80

    pop ebp
    mov eax, [syscall_rc]
    ret
