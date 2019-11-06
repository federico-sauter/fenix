/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     ia32sysinit.c - supervisor initialization
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

#include "ds.h"

#include <string.h>

/**************************************************************************************************/
/* the GDT */
/**************************************************************************************************/
#define GDT_LEN 3

gdt_elem_t gdt[GDT_LEN];
load_ptr_t gdt_ptr;

/**************************************************************************************************/
void ia32_gdt_init_elem(gdt_elem_t *gdt_elem, unsigned base, unsigned limit)
/**************************************************************************************************/
{
  memset(gdt_elem, 0, sizeof(gdt_elem_t));

  /* base address */
  gdt_elem->base_l = base & 0xffff;
  gdt_elem->base_m = (base >> 16) & 0xff;
  gdt_elem->base_h = (base >> 24) & 0xff;

  /* segment limit */
  gdt_elem->limit_l = limit & 0xffff;
  gdt_elem->limit_h = (limit >> 16) & 0xf;

  /* common attributes */
  gdt_elem->system = 1;      /* normal code or data segment */
  gdt_elem->ring = 0;        /* kernel mode  */
  gdt_elem->seg_present = 1; /* segment is always present in memory */
  gdt_elem->avl = 0;         /* unused */
  gdt_elem->reserved = 0;    /* must be set to zero */
  gdt_elem->offset_len = 1;  /* 32-bit offset */
  gdt_elem->granularity = 1; /* size expressed in pages */
}

/**************************************************************************************************/
void ia32_gdt_init()
/**************************************************************************************************/
{
  gdt_elem_t *p_curr_elem = gdt;

  /*
          GDT layout

      +------+-----------------------------+
      | 0x00 | NULL descriptor             |
      +------+-----------------------------+
      | 0x08 | Supervisor code segment     |
      +------+-----------------------------+
      | 0x10 | Supervisor data segment     |
      +------+-----------------------------+
  */

  memset(gdt, 0, sizeof(gdt_elem_t) * GDT_LEN);

  /* NULL segment descriptor */
  ++p_curr_elem;

  /* code segment descriptor */
  ia32_gdt_init_elem(p_curr_elem, 0x0, 0xffffffff);
  p_curr_elem->type = CODE_SEGMENT_R_X;
  ++p_curr_elem;

  /* data segment descriptor */
  ia32_gdt_init_elem(p_curr_elem, 0x0, 0xffffffff);
  p_curr_elem->type = DATA_SEGMENT_RW_;
  ++p_curr_elem;

  /* set the pointer to the GDT */
  gdt_ptr.base = (unsigned)gdt;
  gdt_ptr.limit = (sizeof(gdt_elem_t) * GDT_LEN) - 1;
}
