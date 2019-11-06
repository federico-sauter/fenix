/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     sv.c - FENIX supervisor
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

#include <svsched.h>
#include <sys/ccio.h>
#include <sys/svsyscalls.h>

extern void command_shell_task();

volatile extern unsigned _esp;
volatile uint32_t syscall_rc;

/******************************************************************************/
/* This function is the entry point for system calls. It is called by the IRQ
 * handler when a system call is performed.
 */
uint32_t sv_syscall_dispatch(unsigned id, unsigned arg0, unsigned arg1)
/******************************************************************************/
{
  switch (id) {
    case SV_SYSCALL_SLEEP:
      sv_sleep(arg0);
      break;
    case SV_SYSCALL_WAIT:
      sv_wait_for_task(arg0);
      break;
    case SV_SYSCALL_BLOCK:
      sv_wait_for_keyboard_input();
      break;
    case SV_SYSCALL_PS:
      sv_print_tasks();
      break;
    case SV_SYSCALL_TASK_CREATE:
      return sv_task_create((void (*)(void))arg0, (const char *)arg1);
      break;
    case SV_SYSCALL_TASK_EXIT:
      sv_task_exit();
      break;
    default:
      cc_printf("\nKernel error: Invalid system call (%x)!\n\n", id);
      break;
  }
  return 0x00;
}

/******************************************************************************/
/* Higher-level supervisor initialization. This function is called after the
 * hardware initialization has completed. When the function completes, the
 * control reaches the scheduler.
 */
void sv_init()
/******************************************************************************/
{
  sv_sched_init();
  if (sv_task_create(command_shell_task, "[shell]") == 0) {
    cc_printf("ERROR!\n");
  }
}
