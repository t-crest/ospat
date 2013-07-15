/*  
 * 		Copyright (c) 2007-2009 POK team
 *
 *		Redistribution and use in source and binary forms, with or without
 *		modification, are permitted provided that the following conditions
 *		are met:
 *
 *			* Redistributions of source code must retain the above copyright
 *			  notice, this list of conditions and the following disclaimer.
 *			* Redistributions in binary form must reproduce the above
 *			  copyright notice, this list of conditions and the following
 *			  disclaimer in the documentation and/or other materials
 *			  provided with the distribution.
 *			* Neither the name of the POK Team nor the names of its main
 *			  author (Julien Delange) or its contributors may be used to
 *			  endorse or promote products derived from this software
 *			  without specific prior written permission.
 *
 *		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *		AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *		LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *		FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *		COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *		INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *		BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *		CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *		LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *		ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *		POSSIBILITY OF SUCH DAMAGE.
 */


#include <types.h>
#include <errno.h>
#include <string.h>
#include <bsp.h>

#include "thread.h"

#include <arch.h>
#include <stdio.h>

#define KERNEL_STACK_SIZE           16384
#define KERNEL_SHADOW_STACK_SIZE    16384

#define CONTEXT_SIZE sizeof( context_t )

// Struct representing physical space reserved
struct pok_space
{
	uint32_t phys_base;
	uint32_t size;
};

// Physical space allocation for each partition
struct pok_space spaces[POK_CONFIG_NB_PARTITIONS];

// Extern exit method
extern void exit(int level);

extern void restore_context (void);

// Creates context's space for the specified thread,
// stack_rel is the pointer to the stack
// shadow_stack_rel is the pointer to the shadow_stack
// entry_rel is the pointer to the entry point of the thread
uint32_t pok_space_context_create (uint8_t partition_id,
									uint32_t entry_rel,	// for main thread is the address of the main routine (__pok_partition_start) that call the user main
									uint32_t stack_rel,
									uint32_t shadow_stack_rel)
{
  context_t* ctx;
  (void) partition_id;

  ctx = (context_t*) pok_bsp_mem_alloc (
    CONTEXT_SIZE );

  memset (ctx, 0, sizeof (*ctx));

  // Setting shadow stack pointer
  ctx->r29	  = (uint32_t) shadow_stack_rel; 

  // Setting stack pointer and spill pointer
  ctx->s6     = (uint32_t) stack_rel;
  ctx->s5     = (uint32_t) stack_rel;

  // Return address
  ctx->r30    = (uint32_t) restore_context;

  // Return from interrupt address (entry point of the thread)
  ctx->s9     = (uint32_t) entry_rel;

#ifdef POK_NEEDS_DEBUG
  printf ("[DEBUG]\t Creating context for partition %d, ctx: %p, entry: %x\n", 
    partition_id, ctx, entry_rel);
  printf ("[DEBUG]\t Creating context for partition %d, stack: %x, s_stack: %x\n", 
    partition_id, stack_rel, shadow_stack_rel);
#endif

  return (uint32_t)ctx;
}