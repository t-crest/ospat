/*  
 * Copyright (c) 2012  University of Padua, Department of Mathematics  
 *  
 *  This file is free software: you may copy, redistribute and/or modify it  
 *  under the terms of the GNU General Public License as published by the  
 *  Free Software Foundation, either version 2 of the License, or (at your  
 *  option) any later version.  
 *  
 *  This file is distributed in the hope that it will be useful, but  
 *  WITHOUT ANY WARRANTY; without even the implied warranty of  
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  
 *  General Public License for more details.  
 *  
 *  You should have received a copy of the GNU General Public License  
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  
 *  
 * This file incorporates work covered by the following copyright and  
 * permission notice:  
 *  
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

// Return from interrupt procedure, restores 
// the context. Defined in entry.S (assembly)
// No need for it in Patmos
// extern void pok_arch_rfi (void);

// Creates context's space for the specified
// thread, allocates stack space
// Is used by pok_partition_thread_create in thread.c 
// to create threads for the partition, the first time is called
// to init partition's main thread
// stack_rel is the pointer to the stack
// shadow_stack_rel is the pointer to the shadow_stack
// entry_rel is the pointer to the entry point of the thread
uint32_t pok_space_context_create (uint8_t partition_id,
									uint32_t entry_rel,	// for main thread is the address of the main routine (__pok_partition_start) that call the user main
									uint32_t stack_rel,  // init_stack_addr (points inside the partition memory)
									uint32_t shadow_stack_rel)
{
  context_t* ctx;
  (void) partition_id;

  ctx = (context_t*) pok_bsp_mem_alloc (
    CONTEXT_SIZE );


#ifdef POK_NEEDS_DEBUG
  printf ("ctx starts at: 0x%x \n", (uint32_t)ctx);
#endif

  memset (ctx, 0, sizeof (*ctx));

  // Setting shadow stack pointer
  ctx->r29	  = (uint32_t) shadow_stack_rel; 

  // Setting stack pointer and spill pointer
  ctx->s6     = (uint32_t) stack_rel;

  // Return address
  ctx->r30    = (uint32_t) restore_context;

  // Return from interrupt address (entry point of the thread)
  ctx->s9     = (uint32_t) entry_rel;

#ifdef POK_NEEDS_DEBUG
  printf ("space_context_create %d: entry=%x stack=%x shadow_stack=%x",
			 partition_id, entry_rel, stack_rel, shadow_stack_rel);
#endif

  return (uint32_t)ctx;
}