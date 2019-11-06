/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     svheap.c - supervisor memory heap manager
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

#include "sys/svheap.h"

#if defined(_HEAP_UNIT_TEST_)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#else
#include "sys/types.h"
#include <string.h>
#endif

/* 1MB heap for the supervisor */
#define HEAP_LEN 262144
static unsigned int svheap[HEAP_LEN];

/* invariant: chunk_len != 0 && data_len == 0 -> chunk is free and can be split
 */
struct heap_chunk
{
  sv_size_t
    chunk_len; /* length of the chunk (number of elements) incl. header */
  sv_size_t data_len; /* length of the data section known by the caller */
  struct heap_chunk *prev, *next; /* doubly-linked list management */
  unsigned int *data;             /* data pointer returned to the caller */
};

#define HDR_LEN (sizeof(struct heap_chunk) / sizeof(unsigned int))
#define ELEM_SIZE (sizeof(unsigned int))
#define LEN(x) ((x) / sizeof(unsigned int))

static struct heap_chunk *sv_malloc_find_chunk(sv_size_t len);

/**************************************************************************************************/
void sv_heap_init()
/**************************************************************************************************/
{
  struct heap_chunk *p = (struct heap_chunk *)svheap;
  memset(svheap, 0xC, sizeof(svheap));
  p->chunk_len = HEAP_LEN;
  p->data_len = 0;
  p->prev = p->next = NULL;
  p->data = svheap + HDR_LEN;
}

/**************************************************************************************************/
void *sv_malloc(sv_size_t size)
/**************************************************************************************************/
{
  const sv_size_t len = LEN(size) + (size % ELEM_SIZE == 0 ? 0 : 1);
  const sv_size_t chunk_len = HDR_LEN + len;
  struct heap_chunk *chunk = sv_malloc_find_chunk(chunk_len);
  if (chunk == NULL)
    return NULL;

  if (chunk->chunk_len - chunk_len > 3 * HDR_LEN) {
    /* split chunk */
    sv_size_t big_chunk_len = chunk->chunk_len;
    struct heap_chunk *next = chunk->next;
    chunk->chunk_len = chunk_len;
    chunk->data_len = len;

    struct heap_chunk *new =
      (struct heap_chunk *)((unsigned int *)chunk + chunk_len);
    new->chunk_len = big_chunk_len - chunk_len;
    chunk->next = new;
    new->next = next;
    new->prev = chunk;
    new->data = (unsigned int *)new + HDR_LEN;
    new->data_len = 0;
    if (next)
      next->prev = new;
  } else {
    chunk->data_len = len;
  }
  /* the chunk_len may not be updated, and the invariant be broken: chunk_len =
   * HDR_LEN + len */
  return chunk->data;
}

/**************************************************************************************************/
void *sv_realloc(void *ptr, unsigned size)
/**************************************************************************************************/
{
  return NULL;
}

/**************************************************************************************************/
void sv_free(void *ptr)
/**************************************************************************************************/
{
  if (ptr == NULL)
    return;

  struct heap_chunk *p = (struct heap_chunk *)((unsigned int *)ptr - HDR_LEN);
  p->data_len = 0; /* invariant: no caller is using this chunk */
  if (p->next) {
    struct heap_chunk *next = p->next;
    if (next->data_len == 0) {
      /* merge the current entry with the next one */
      p->next = next->next;
      if (p->next)
        p->next->prev = p;
      p->chunk_len += next->chunk_len;
    }
  }
  if (p->prev) {
    struct heap_chunk *prev = p->prev;
    if (prev->data_len == 0) {
      /* merge the previous entry with the current one */
      prev->next = p->next;
      if (p->next)
        p->next->prev = prev;
      prev->chunk_len += p->chunk_len;
      p = prev;
    }
  }
}

/**************************************************************************************************/
static struct heap_chunk *sv_malloc_find_chunk(sv_size_t len)
/**************************************************************************************************/
{
  struct heap_chunk *p, *chunk = NULL;
  for (p = (struct heap_chunk *)svheap; p; p = p->next) {
    if (p->data_len == 0 && p->chunk_len >= len) {
      chunk = p;
      break;
    }
  }
  return chunk;
}

#if defined(_HEAP_UNIT_TEST_)
/**************************************************************************************************/
/* Unit test */
/**************************************************************************************************/
#define MAX_SIZE 8192
#define MAX_SLOTS 8192
#define MAX_TEST_ITER 1024

struct slot
{
  void *ptr;
  void *data;
  sv_size_t size;
};

struct slot slots[MAX_SLOTS];
sv_size_t used_slots;

void heap_dump()
{
  struct heap_chunk *p;
  int must_exit = 0;
  printf("--- heap DUMP: ---\n");
  for (p = (struct heap_chunk *)svheap; p; p = p->next) {
    printf(
      "  %p:  next = %p; prev = %p; len = %8u; data_len = %8u; data_size = "
      "%8u; data = %p;\n",
      p,
      p->next,
      p->prev,
      p->chunk_len,
      p->data_len,
      p->data_len * sizeof(unsigned int),
      p->data);
    if (must_exit)
      exit(32);
    if (p->next) {
      unsigned diff = (unsigned long)p->next - (unsigned long)p->data;
      if (p->data_len && diff < p->data_len * sizeof(unsigned int)) {
        printf("ERROR: diff = %u diff_len = %u\n",
               diff,
               diff / sizeof(unsigned int));
        must_exit = 1;
      }
      unsigned diff2 = (unsigned long)p->next - (unsigned long)p;
      if (diff2 != p->chunk_len * sizeof(unsigned int)) {
        printf("ERROR: diff2 = %u diff2_len = %u\n",
               diff2,
               diff2 / sizeof(unsigned int));
        must_exit = 1;
      }
    }
  }
  printf("--- DUMP END ---\n");
}

void test_used_mem()
{
  sv_size_t i;
  for (i = 0; i < used_slots; ++i) {
    if (slots[i].ptr) {
      if (memcmp(slots[i].ptr, slots[i].data, slots[i].size) != 0) {
        printf("FATAL: slot %u corrupted (ptr = %p)!\n", i, slots[i].ptr);
        exit(64);
      }
    }
  }
}

void check_heap_invariants()
{
  struct heap_chunk *p;
  for (p = (struct heap_chunk *)svheap; p; p = p->next) {
    if (p->data_len == 0) {
      if (p->prev && p->prev->data_len == 0) {
        printf("INVARIANT VIOLATION previous node is also empty p=%p\n", p);
        heap_dump();
        exit(16);
      }
      if (p->next && p->next->data_len == 0) {
        printf("INVARIANT VIOLATION next node is also empty p=%p\n", p);
        heap_dump();
        exit(16);
      }
    }
    if (p->next) {
      if (p->next->prev != p) {
        printf("INVARIANT VIOLATION: p->next->prev != p for %p; next = %p\n",
               p,
               p->next);
        heap_dump();
        exit(16);
      }
    }
    if (p->prev) {
      if (p->prev->next != p) {
        printf("INVARIANT VIOLATION: p->prev->next != p for %p; prev = %p\n",
               p,
               p->prev);
        heap_dump();
        exit(16);
      }
    }
  }
}

void alloc_test()
{
  static sv_size_t factor = 1, ooo = 0;
  sv_size_t size = rand() % 1024 / factor + 2;
  sv_size_t i = used_slots;
  printf("[%u] requesting memory block of size %u...\n", i, size);
  void *ptr = sv_malloc(size);
  printf("[%u] returned %p\n", i, ptr);
  if (ptr) {
    slots[i].ptr = ptr;
    slots[i].size = size;
    slots[i].data = malloc(slots[i].size);
    if (slots[i].data == NULL) {
      printf("FATAL: out of memory for verification memory!\n");
      exit(64);
    }
    memset(slots[i].data, (rand() % 255) & 0xFF, slots[i].size);
    memcpy(slots[i].ptr, slots[i].data, slots[i].size);
    printf("[%u] wrote %u bytes\n", i, slots[i].size);
    ++used_slots;
    factor = 1;
    ooo = 0;
  } else {
    printf("[%u] Out of memory!\n", i);
    factor = 100;
    ++ooo;
    if (ooo == 10)
      return;
  }
}

void free_test()
{
  int attempts = 10;
  while (attempts-- && used_slots) {
    sv_size_t i = rand() % used_slots;
    if (slots[i].ptr) {
      printf("[%u] freeing up memory...\n", i);
      sv_free(slots[i].ptr);
      slots[i].ptr = NULL;
      if (slots[i].data) {
        free(slots[i].data);
        slots[i].data = NULL;
      }
      slots[i].size = 0;
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  sv_size_t i;
  sv_size_t iter = MAX_TEST_ITER;

  if (argc == 2) {
    iter = atoi(argv[1]);
    if (iter == 0) {
      fprintf(stderr, "usage: %s <iterations>\n", *argv);
      exit(2);
    }
  }

  srand(time(NULL));

  sv_heap_init();
  sv_size_t initial_len = ((struct heap_chunk *)svheap)->chunk_len;

  heap_dump();
  used_slots = 0;
  memset(slots, 0, sizeof(slots));
  for (i = 0; i < iter; ++i) {
    if (rand() % 3) {
      alloc_test();
    } else {
      free_test();
    }
    heap_dump();
    check_heap_invariants();
    test_used_mem();
  }
  check_heap_invariants();
  test_used_mem();
  for (i = 0; i < used_slots; ++i) {
    if (slots[i].ptr) {
      sv_free(slots[i].ptr);
      free(slots[i].data);
      slots[i].ptr = slots[i].data = NULL;
    }
  }
  check_heap_invariants();
  test_used_mem();
  heap_dump();
  if (initial_len != ((struct heap_chunk *)svheap)->chunk_len) {
    printf("FAILURE: initial len = %u; final heap len = %u\n",
           initial_len,
           ((struct heap_chunk *)svheap)->chunk_len);
    exit(16);
  }
  printf("SUCCESS\n");
  printf("Total elements allocated: %u\n", used_slots);
  exit(0);
}
#endif /* _HEAP_UNIT_TEST_ */
