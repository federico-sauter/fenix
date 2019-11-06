/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     svsyscalls.h - system call constants
   __/ /  \ \____/
   _ \ \__/ / __ \.     FENIX Kernel
    \ \____/ /  \ \
   _/ / __ \ \__/ /     Copyright(C) 2019 by Federico Sauter<f.sauter@gmail.com>
   __/ /  \ \____/
   _ \ \__/ / __ \.

    This file is part of the FENIX Kernel.

    The FENIX Kernel is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The FENIX Kernel is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the FENIX Kernel.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(_SV_SYSCALLS__H_)
#define _SV_SYSCALLS__H_

#define SV_SYSCALL_SLEEP 0x01
#define SV_SYSCALL_WAIT 0x02
#define SV_SYSCALL_BLOCK 0x03
#define SV_SYSCALL_PS 0x04
#define SV_SYSCALL_TASK_CREATE 0x05
#define SV_SYSCALL_TASK_EXIT 0x06

#endif /* _SV_SYSCALLS__H_ */
