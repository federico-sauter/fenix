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
#include <string.h>
#include <sv/svha.h>
#include <sys/ccio.h>
#include <sys/svsyscalls.h>
#include <tinysh.h>

/******************************************************************************/
/* This function is required for the tinysh integration */
void tinysh_char_out(unsigned char c)
/******************************************************************************/
{
  cc_printch((char)c);
}

/******************************************************************************/
static void version_command(int argc, char **argv)
/******************************************************************************/
{
  cc_printf("FENIX Version 0.2\n");
}

/******************************************************************************/
static void clear_command(int argc, char **argv)
/******************************************************************************/
{
  cc_clear();
  cc_cpos_set(0, 0);
}

/******************************************************************************/
static void ps_command(int argc, char **argv)
/******************************************************************************/
{
  ps();
}

void test_task() {
  cc_printf("\n");
  for (int i = 0; i < 5; ++i) {
    cc_printf(".");
    sleep(1);
  }
  cc_printf("\nexiting task...\n");
  exit_task();
}

/******************************************************************************/
static void testexit_command(int argc, char **argv)
/******************************************************************************/
{
  uint32_t task_id = create_task(test_task, "test task");
  cc_printf("task_id = %x\n", task_id);
  if (argc == 2 && strcmp(argv[1], "wait") == 0) {
    wait(task_id);
  }
}

/******************************************************************************/
extern void demo_command(int argc, char **argv);
/******************************************************************************/

static tinysh_cmd_t version_cmd = {
    0, "ver", "show the operating system version", "[args]", version_command, 0,
    0, 0};

static tinysh_cmd_t clear_cmd = {
    0, "clear", "clear the console", "[args]", clear_command, 0, 0, 0};

static tinysh_cmd_t ps_cmd = {
    0, "ps", "print the task list and state", "[args]", ps_command, 0, 0, 0};

static tinysh_cmd_t demo_cmd = {
    0, "demo", "multitasking demo", "[args]", demo_command, 0, 0, 0};

static tinysh_cmd_t exit_test_cmd = {
    0, "exit-test", "exit-test [wait]", "[args]", testexit_command, 0, 0, 0};

extern unsigned char cc_getch();

/******************************************************************************/
void command_shell_task()
/******************************************************************************/
{
  cc_clear();

  cc_printf("FENIX Interactive Shell\n");
  cc_printf("Version 0.2\n");
  cc_printf("Copyright(C) 1995-2019 by Federico Sauter\n\n");

  tinysh_set_prompt("> ");
  tinysh_add_command(&version_cmd);
  tinysh_add_command(&clear_cmd);
  tinysh_add_command(&ps_cmd);
  tinysh_add_command(&demo_cmd);
  tinysh_add_command(&exit_test_cmd);

  for (;;) {
    tinysh_char_in(cc_getch());
  }

  cc_printf("\nNote: Interactive shell exited by the user. System halted.");
  sv_get_ha()->halt();
}
