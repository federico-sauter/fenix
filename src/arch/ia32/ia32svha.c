/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     svha.c - supervisor hardware abstraction
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

#include <sv/svha.h>

extern uint32_t ia32_do_syscall(unsigned, unsigned, unsigned);
extern void ia32_halt();

static struct svha ha = { .do_syscall = ia32_do_syscall, .halt = ia32_halt };

const struct svha *sv_get_ha()
{
  return &ha;
}
