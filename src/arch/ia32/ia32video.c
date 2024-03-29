/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     ia32video.c - kernel video memory driver for IA-32
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

#include <string.h>
#include <sys/video.h>

#define VIDEO_MEM_ADDR 0xB8000

/*  read/write to hardware ports    */
extern void ia32_outb(unsigned short p, unsigned char c);

static volatile unsigned char *ia32_video_mem_ppos =
  (volatile unsigned char *)VIDEO_MEM_ADDR;

/**************************************************************************************************/
void ia32_video_clear(unsigned char bg)
/**************************************************************************************************/
{
  int i;
  ia32_video_mem_ppos = (volatile unsigned char *)VIDEO_MEM_ADDR;
  for (i = 0; i < ia32_video_get_screen_len() * ia32_video_get_line_len() * 2;
       i += 2) {
    *ia32_video_mem_ppos++ = 0;
    *ia32_video_mem_ppos++ = bg;
  }
  ia32_video_move_ppos(0, 0);
  ia32_video_upd_cursor(0, 0);
}

/**************************************************************************************************/
void ia32_video_scroll(unsigned char bg)
/**************************************************************************************************/
{
  int scroll_area_b; /*  byte size of the scroll area */
  int line_b;        /*  byte size of one line */
  int last_line;
  unsigned short blank = 0 | (bg << 8);

  ia32_video_mem_ppos = (volatile unsigned char *)VIDEO_MEM_ADDR;

  last_line = (ia32_video_get_screen_len() - 1) * ia32_video_get_line_len() *
              2 * sizeof(unsigned char);
  line_b = ia32_video_get_line_len() * 2 * sizeof(unsigned char);
  scroll_area_b = ia32_video_get_screen_len() * ia32_video_get_line_len() * 2 *
                    sizeof(unsigned char) -
                  line_b;

  memmove((void *)ia32_video_mem_ppos,
          ((void *)ia32_video_mem_ppos) + line_b,
          scroll_area_b);
  memset(((void *)ia32_video_mem_ppos + last_line), blank, line_b);

  ia32_video_move_ppos(0, ia32_video_get_screen_len() - 1);
}

/**************************************************************************************************/
void ia32_video_move_ppos(unsigned short x, unsigned short y)
/**************************************************************************************************/
{
  ia32_video_mem_ppos = (volatile unsigned char *)VIDEO_MEM_ADDR;

  /* parameter validation */
  x = (x > ia32_video_get_line_len() - 1) ? ia32_video_get_line_len() - 1 : x;
  y =
    (y > ia32_video_get_screen_len() - 1) ? ia32_video_get_screen_len() - 1 : y;

  ia32_video_mem_ppos += (y * 2 * ia32_video_get_line_len()) + (x * 2);
  ia32_video_upd_cursor(x, y);
}

/**************************************************************************************************/
void ia32_outb(unsigned short p, unsigned char c)
/**************************************************************************************************/
{
  __asm__ __volatile__("outb %1, %0" : : "dN"(p), "a"(c));
}

/**************************************************************************************************/
void ia32_video_upd_cursor(unsigned short x, unsigned short y)
/**************************************************************************************************/
{
  unsigned int offset = y * ia32_video_get_line_len() + x;

  ia32_outb(0x3d4, 14);
  ia32_outb(0x3d5, offset >> 8);
  ia32_outb(0x3d4, 15);
  ia32_outb(0x3d5, offset);
}

/**************************************************************************************************/
unsigned int ia32_video_getcolor(unsigned char fg, unsigned char bg)
/**************************************************************************************************/
{
  return (bg << 4) | (fg & 0x0f);
}

/**************************************************************************************************/
void ia32_video_printch(unsigned char c, int color)
/**************************************************************************************************/
{
  /*  write character */
  *ia32_video_mem_ppos++ = c;
  *ia32_video_mem_ppos++ = color;
}
