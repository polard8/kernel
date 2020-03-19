/*
 *  ZeX/OS
 *  Copyright (C) 2007  Tomas 'ZeXx86' Jedrzejek (zexx86@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <x86.h>
#include <string.h>

#define	_32BIT	1

/* use small (32K) heap for 16-bit compilers,
large (500K) heap for 32-bit compilers */
#if defined(_32BIT)
#define	HEAP_SIZE	16384u //500000uL
#else
#define	HEAP_SIZE	32768u
#endif

#define	MALLOC_MAGIC	0x6D92	/* must be < 0x8000 */

typedef struct _malloc		/* Turbo C	DJGPP */
{
	size_t size;		/* 2 bytes	 4 bytes */
	struct _malloc *next;	/* 2 bytes	 4 bytes */
	unsigned magic : 15;	/* 2 bytes total 4 bytes total */
	unsigned used : 1;
} malloc_t;		/* total   6 bytes	12 bytes */

static char *g_heap_bot, *g_kbrk, *g_heap_top;
/*****************************************************************************
*****************************************************************************/
static void dump_heap (void)
{
	unsigned blks_used = 0, blks_free = 0;
	size_t bytes_used = 0, bytes_free = 0;
	malloc_t *m;
	int total;

	for (m = (malloc_t *)g_heap_bot; m != NULL; m = m->next)
	{
		//DPRINT ("blk %5p: %6u bytes %s\n", m,
		//	m->size, m->used ? "used" : "free");

		if (m->used)
		{
			blks_used++;
			bytes_used += m->size;
		}
		else
		{
			blks_free++;
			bytes_free += m->size;
		}
	}

	/*DPRINT ("blks:  %6u used, %6u free, %6u total\n", blks_used,
		blks_free, blks_used + blks_free);
	DPRINT ("bytes: %6u used, %6u free, %6u total\n", bytes_used,
		bytes_free, bytes_used + bytes_free);
	DPRINT ("g_heap_bot=0x%p, g_kbrk=0x%p, g_heap_top=0x%p\n",
		g_heap_bot, g_kbrk, g_heap_top);*/

	total = (bytes_used + bytes_free) +
			(blks_used + blks_free) * sizeof(malloc_t);

	//if(total != g_kbrk - g_heap_bot)
		//DPRINT ("*** some heap memory is not accounted for\n");
}
/*****************************************************************************
POSIX sbrk() looks like this
	void *sbrk(int incr);
Mine is a bit different so I can signal the calling function
if more memory than desired was allocated (e.g. in a system with paging)
If your kbrk()/sbrk() always allocates the amount of memory you ask for,
this code can be easily changed.

			int brk(	void *sbrk(		void *kbrk(
function		 void *adr);	 int delta);		 int *delta);
----------------------	------------	------------		-------------
POSIX?			yes		yes			NO
return value if error	-1		-1			NULL
get break value		.		sbrk(0)			int x=0; kbrk(&x);
set break value to X	brk(X)		sbrk(X - sbrk(0))	int x=X, y=0; kbrk(&x) - kbrk(&y);
enlarge heap by N bytes	.		sbrk(+N)		int x=N; kbrk(&x);
shrink heap by N bytes	.		sbrk(-N)		int x=-N; kbrk(&x);
can you tell if you're
  given more memory
  than you wanted?	no		no			yes
*****************************************************************************/
static void *kbrk (int *delta)
{
	static char heap[HEAP_SIZE];
/**/
	char *new_brk, *old_brk;

/* heap doesn't exist yet */
	if(g_heap_bot == NULL)
	{
		g_heap_bot = g_kbrk = heap;
		g_heap_top = g_heap_bot + HEAP_SIZE;
	}
	new_brk = g_kbrk + (*delta);
/* too low: return NULL */
	if(new_brk < g_heap_bot)
		return NULL;
/* too high: return NULL */
	if(new_brk >= g_heap_top)
		return NULL;
/* success: adjust brk value... */
	old_brk = g_kbrk;
	g_kbrk = new_brk;
/* ...return actual delta... (for this sbrk(), they are the same)
	(*delta) = (*delta); */
/* ...return old brk value */
	return old_brk;
}

/*****************************************************************************
malloc() and free() use g_heap_bot, but not g_kbrk nor g_heap_top
*****************************************************************************/
void *malloc (size_t size)
{
	asm volatile (
		"movl $14, %%eax;"
	     	"movl %0, %%ebx;"
	     	"int $0x80;" :: "g" ((unsigned) size) : "%eax", "%ebx");

	unsigned long *memptr = (unsigned long *) 0x9000;
	unsigned long *p = memptr;

	return (void *) *p;
}
/*****************************************************************************
*****************************************************************************/
void free (void *blk)
{
	malloc_t *m, *n;

/* get address of header */
	m = (malloc_t *)((char *)blk - sizeof(malloc_t));
	if(m->magic != MALLOC_MAGIC)
//		panic("attempt to free() block at 0x%p "
//			"with bad magic value", blk);
	{
		//printf ("*** attempt to free() block at 0x%p "
		//	"with bad magic value\n", blk);
		return;
	}
/* find this block in the heap */
	n = (malloc_t *)g_heap_bot;
	if(n->magic != MALLOC_MAGIC)
//		panic("kernel heap is corrupt in free()");
	{
		//printf ("*** kernel heap is corrupt in free()\n");
		return;
	}
	for(; n != NULL; n = n->next)
	{
		if(n == m)
			break;
	}
/* not found? bad pointer or no heap or something else? */
	if(n == NULL)
//		panic("attempt to free() block at 0x%p "
//			"that is not in the heap", blk);
	{
		//printf ("*** attempt to free() block at 0x%p "
		//	"that is not in the heap\n", blk);
		return;
	}
/* free the block */
	m->used = 0;
/* coalesce adjacent free blocks
Hard to spell, hard to do */
	for(m = (malloc_t *)g_heap_bot; m != NULL; m = m->next)
	{
		while(!m->used && m->next != NULL && !m->next->used)
		{
/* resize this block */
			m->size += sizeof(malloc_t) + m->next->size;
/* merge with next block */
			m->next = m->next->next;
		}
	}
}
/*****************************************************************************
*****************************************************************************/
void *realloc (void *blk, size_t size)
{
	void *new_blk;
	malloc_t *m;

/* size == 0: free block */
	if (size == 0)
	{
		if (blk != NULL)
			free (blk);
		new_blk = NULL;
	}
	else
	{
/* allocate new block */
		new_blk = malloc (size);
/* if allocation OK, and if old block exists, copy old block to new */
		if (new_blk != NULL && blk != NULL)
		{
			m = (malloc_t *)((char *)blk - sizeof(malloc_t));
			if (m->magic != MALLOC_MAGIC)
//				panic("attempt to krealloc() block at "
//					"0x%p with bad magic value", blk);
			{
				//printf ("*** attempt to krealloc() block at "
				//	"0x%p with bad magic value\n", blk);
				return NULL;
			}
/* copy minimum of old and new block sizes */
			if(size > m->size)
				size = m->size;
			memcpy (new_blk, blk, size);
/* free the old block */
			free (blk);
		}
	}
	return new_blk;
}
/*****************************************************************************
*****************************************************************************/
