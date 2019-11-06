/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     shell.c -- simple command shell implementation
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

#include <fenix.h>
#include <sys/ccio.h>

/******************************************************************************/
void task1()
/******************************************************************************/
{
  cc_cpos_set(5, 2);
  cc_printf("task1:");
  for (unsigned x = 0;; ++x) {
    cc_cpos_set(13, 2);
    cc_printf("%x", x);
    sleep(1);
  }
}

/******************************************************************************/
void task2()
/******************************************************************************/
{
  cc_cpos_set(5, 4);
  cc_printf("task2:");
  for (unsigned x = (unsigned)-1;; --x) {
    cc_cpos_set(13, 4);
    cc_printf("%x", x);
    sleep(2);
  }
}

/******************************************************************************/
void task3()
/******************************************************************************/
{
  cc_cpos_set(5, 6);
  cc_printf("task2:");
  for (unsigned x = 8;; x += 4) {
    cc_cpos_set(13, 6);
    cc_printf("%x", x);
    sleep(4);
  }
}

/******************************************************************************/
void pstask()
/******************************************************************************/
{
  for (;;) {
    cc_cpos_set(0, 8);
    ps();
    sleep(1);
  }
}

void ticks()
{
  char t[] = { '-', '/', '*', '\\' };
  for (unsigned x = 0;;) {
    for (unsigned i = 2; i < 8; i += 2) {
      cc_cpos_set(24, i);
      cc_printch(t[x++ % 4]);
    }
    nap();
  }
}

/******************************************************************************/
void demo_command(int argc, char **argv)
/******************************************************************************/
{
  cc_clear();
  create_task(task1, "task1");
  create_task(task2, "task2");
  create_task(task3, "task3");
  create_task(ticks, "ticks");
  create_task(pstask, "ps");
  for (;;) {
    sleep(3600);
  }
}
