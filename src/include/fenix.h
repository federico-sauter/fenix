/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     fenix.h - supervisor system calls
   __/ /  \ \____/
   _ \ \__/ / __ \.     FENIX Kernel
    \ \____/ /  \ \
   _/ / __ \ \__/ /     Copyright(C) 2019 by Federico Sauter<f.sauter@gmail.com>
   __/ /  \ \____/        All rights reserved.
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

#if !defined(_FENIX__H_)
#define _FENIX__H_

#include <sys/types.h>

/* FENIX system calls */

/* puts the current process to sleep for the specified time */
void sleep(unsigned seconds);

/* waits for the specified task to complete */
int wait(uint32_t task_id);

/* waits for keyboard input */
void block();

/* puts the current process to sleep for 300ms */
void nap();

/* prints out the task list and its state */
void ps();

/* creates a new task from the specified entry point */
uint32_t create_task(void (*entry)(), const char *name);

/* exits the current task */
void exit_task();

#endif /* _FENIX__H_ */
