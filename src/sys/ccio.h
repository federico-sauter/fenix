/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     ccio.h - definitions for the console controller io
   functions
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

#if !defined(_FENIX_SYS_CCIO__H_)
#define _FENIX_SYS_CCIO__H_

/* constants */
/* ASCII special keys */
#define CC_KEY_ESC 0x1B   /* escape */
#define CC_KEY_BS 0x0E    /* backspace */
#define CC_KEY_TAB 0x09   /* tab */
#define CC_KEY_LF 0x0A    /* enter */
#define CC_KEY_SPACE 0x20 /* spacebar*/

/* extended function keys */
#define CC_KEY_CTRL (0xFF + 1)
#define CC_KEY_LSHIFT (0xFF + 2)
#define CC_KEY_RSHIFT (0xFF + 3)
#define CC_KEY_ALT (0xFF + 4)
#define CC_KEY_CAPSL (0xFF + 5)
#define CC_KEY_F1 (0xFF + 6)
#define CC_KEY_F2 (0xFF + 7)
#define CC_KEY_F3 (0xFF + 8)
#define CC_KEY_F4 (0xFF + 9)
#define CC_KEY_F5 (0xFF + 10)
#define CC_KEY_F6 (0xFF + 11)
#define CC_KEY_F7 (0xFF + 12)
#define CC_KEY_F8 (0xFF + 13)
#define CC_KEY_F9 (0xFF + 14)
#define CC_KEY_F10 (0xFF + 15)
#define CC_KEY_F11 (0xFF + 28) // BUG
#define CC_KEY_F12 (0xFF + 29) // BUG

#define CC_KEY_NUML (0xFF + 16)
#define CC_KEY_SCRLL (0xFF + 17)
#define CC_KEY_HOME (0xFF + 18)
#define CC_KEY_UP (0xFF + 19)
#define CC_KEY_PGUP (0xFF + 20) // BUG
#define CC_KEY_LEFT (0xFF + 21)
#define CC_KEY_RIGHT (0xFF + 22)
#define CC_KEY_END (0xFF + 23)
#define CC_KEY_DOWN (0xFF + 24)
#define CC_KEY_PGDOWN (0xFF + 25)
#define CC_KEY_INS (0xFF + 26)
#define CC_KEY_DEL (0xFF + 27)
#define CC_KEY_UNDEFINED (0xFF + 0xFF - 1)

#define is_special_key(x) (x <= 0xff)

/*  screen colors   */
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

/*  clears the screen  */
void cc_clear();

/* obtains the current position of the cursor */
void cc_cpos_get(unsigned short *x, unsigned short *y);

/*  moves the cursor position to the specified coordinates  */
void cc_cpos_set(unsigned short x, unsigned short y);

/*  sets the current color  */
void cc_color_set(unsigned char fg, unsigned char bg);

/******************************************************************************/
/* proto-printf, supporting the following format sequences: */
/*    %x : unsigned hex numbers (with filling leading zeroes) */
/*    %c : character */
/*    %s : string */
/* DO NOT call with a single % within the format string, as it does not handle
 * errors at all!     */
int cc_printf(const char *format, ...);

/* Prints a single character to the console. */
void cc_printch(char c);

/*  writes at the specified screen location without moving the current position
   or cursor to the write location   */
void cc_print_abs(unsigned short x, unsigned short y, const char *s);

#endif /*_FENIX_SYS_CCIO__H_*/
