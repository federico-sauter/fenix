/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     string.h - standard string utility functions
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

#if !defined(_FENIX_SYS_STRING__H_)
#define _FENIX_SYS_STRING__H_

typedef unsigned int size_t;

#define memmove(dest, src, n) memcpy(dest, src, n)

/* Function descriptions taken from: The C Programming Language 2nd ed, by
 * Kerningham & Ritchie
 */

/*  copy string ct to string s, including '\0'; return s  */
char *strcpy(char *s, const char *ct);

/*  concatenate string ct to end of string s; return s  */
char *strcat(char *s, const char *ct);

/*  compare string cd to string ct; return <0 if cs<ct, o if cs==ct, or >0 if
 * cs>ct */
int strcmp(const char *cs, const char *ct);

/*  return length of cs */
size_t strlen(const char *cs);

/*  copy n characters from ct to s, and return s    */
void *memcpy(void *s, const void *ct, size_t n);

/*  compare the first n characters of cs with ct; return as with strcmp */
int memcmp(const void *cs, const void *ct, size_t n);

/*  place character c into first n characters of s, return s  */
void *memset(void *s, unsigned char c, size_t n);

#endif
