/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     ia32syscalls.c - system call interface to the supervisor
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

#include <svha.h>
#include <sys/svsyscalls.h>

void sleep(unsigned seconds)
{
  /* The Programmable Interval Timer (PIT) frequency is set at 100Hz,
   * see the subroutine ia32_setup_pli in ia32tasks.asm
   */
  sv_get_ha()->do_syscall(SV_SYSCALL_SLEEP, seconds * 100, 0x00);
}

int wait(uint32_t task_id)
{
  if (task_id == 0)
    return -1;
  sv_get_ha()->do_syscall(SV_SYSCALL_WAIT, task_id, 0x00);
  return 0;
}

void block()
{
  sv_get_ha()->do_syscall(SV_SYSCALL_BLOCK, 0x00, 0x00);
}

void nap()
{
  sv_get_ha()->do_syscall(SV_SYSCALL_SLEEP, 0x07, 0x00);
}

void ps()
{
  sv_get_ha()->do_syscall(SV_SYSCALL_PS, 0x00, 0x00);
}

uint32_t create_task(void (*entry)(), const char *name)
{
  return sv_get_ha()->do_syscall(
    SV_SYSCALL_TASK_CREATE, (unsigned)entry, (unsigned)name);
}

void exit_task()
{
  sv_get_ha()->do_syscall(SV_SYSCALL_TASK_EXIT, 0x00, 0x00);
}
