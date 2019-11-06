/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     cckeybrd.c - keyboard driver for the console controller
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

#include <sv/svsched.h>
#include <sys/ccio.h>
#include <sys/video.h>

#define KEYBD_PORT 0x60

/*  read/write to hardware ports    */
extern unsigned char ia32_inb(unsigned short p);
extern void ia32_outb(unsigned short p, unsigned char c);

extern volatile unsigned short keybd_last_key;
extern volatile unsigned char keybd_last_scan;

/* keyboard layout table for: us en */
unsigned short kbd_layout_us_en[128] = { 0,
                                         CC_KEY_ESC,
                                         '1',
                                         '2',
                                         '3',
                                         '4',
                                         '5',
                                         '6',
                                         '7',
                                         '8',
                                         '9',
                                         '0',
                                         '-',
                                         '=',
                                         CC_KEY_BS,
                                         CC_KEY_TAB,
                                         'q',
                                         'w',
                                         'e',
                                         'r',
                                         't',
                                         'y',
                                         'u',
                                         'i',
                                         'o',
                                         'p',
                                         '[',
                                         ']',
                                         CC_KEY_LF,
                                         CC_KEY_CTRL,
                                         'a',
                                         's',
                                         'd',
                                         'f',
                                         'g',
                                         'h',
                                         'j',
                                         'k',
                                         'l',
                                         ';',
                                         '\'',
                                         '`',
                                         CC_KEY_LSHIFT,
                                         '\\',
                                         'z',
                                         'x',
                                         'c',
                                         'v',
                                         'b',
                                         'n',
                                         'm',
                                         ',',
                                         '.',
                                         '/',
                                         CC_KEY_RSHIFT,
                                         '*',
                                         CC_KEY_ALT,
                                         ' ',
                                         CC_KEY_CAPSL,
                                         CC_KEY_F1,
                                         CC_KEY_F2,
                                         CC_KEY_F3,
                                         CC_KEY_F4,
                                         CC_KEY_F5,
                                         CC_KEY_F6,
                                         CC_KEY_F7,
                                         CC_KEY_F8,
                                         CC_KEY_F9,
                                         CC_KEY_F10,
                                         CC_KEY_NUML,
                                         CC_KEY_SCRLL,
                                         CC_KEY_HOME,
                                         CC_KEY_UP,
                                         '-',
                                         CC_KEY_LEFT,
                                         0,
                                         CC_KEY_RIGHT,
                                         '+',
                                         CC_KEY_END,
                                         CC_KEY_DOWN,
                                         CC_KEY_PGDOWN,
                                         CC_KEY_INS,
                                         CC_KEY_DEL,
                                         CC_KEY_F11,
                                         CC_KEY_F12,
                                         0 };

/******************************************************************************/
/* TODO move this function to the ia32-specific directory and implement in
 * assembler!             */
unsigned char ia32_inb(unsigned short p)
/******************************************************************************/
{
  unsigned char rc;
  __asm__ __volatile__("inb %1, %0" : "=a"(rc) : "dN"(p));
  return rc;
}

/******************************************************************************/
/* The entry point for the keyboard driver */
void sv_handle_keybd_irq()
/******************************************************************************/
{
  keybd_last_scan = ia32_inb(KEYBD_PORT);
  keybd_last_key = kbd_layout_us_en[keybd_last_scan];
  ia32_outb(0x20, 0x20);
  sv_notify_keyboard_event();
}
