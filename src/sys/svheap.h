/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     svheap.h - heap management
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

#if !defined(_FENIX_SYS_SVHEAP__H_)
#define _FENIX_SYS_SVHEAP__H_

typedef unsigned int sv_size_t;

void sv_heap_init();

void *sv_malloc(sv_size_t size);

void *sv_realloc(void *ptr, sv_size_t size);

void sv_free(void *ptr);

#endif /* _FENIX_SYS_SVHEAP__H_ */
