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

#include <bsp.h>
#include <stdio.h>
#include <string.h>
#include <core/thread.h>

#include "thread.h"

#ifdef POK_NEEDS_THREADS

extern void pok_arch_thread_start(void);

// Used to create special threads context (idle and kernel threads)
uint32_t		pok_context_create (uint32_t id,
									uint32_t stack_size,
									uint32_t shadow_stack_size,
									uint32_t entry)
{
	context_t*	ctx;
	char*		stack_addr;

	// Allocate stack space
	stack_addr = pok_bsp_mem_alloc (
		sizeof (context_t) 	+ 
		stack_size 			+
		shadow_stack_size);

	// find space for the threads context
	ctx = (context_t *) (stack_addr + stack_size + shadow_stack_size);

	// Set context to 0
	memset (ctx, 0, sizeof (context_t));

	// Setting temporary entry point and identifier of the
	// thread, used only before starting it (then can be modified)
	ctx->r18	= entry;
	ctx->r19	= id;

	// Setting base function address to return to
	ctx->r30	= (uint32_t) pok_arch_thread_start;
	ctx->s9		= (uint32_t) pok_arch_thread_start;

	// Setting stack pointer and spill pointer
	ctx->s5			= (uint32_t) (ctx - 4);
	ctx->s6			= (uint32_t) (ctx - 4);

	ctx->r29		= (uint32_t) (ctx - stack_size - 4);

	#ifdef POK_NEEDS_DEBUG
	printf ("[DEBUG]\t Creating system context %d, ctx: %p, sp: %x\n", id, ctx, ctx->s5);
	#endif
	return (uint32_t)ctx;
}

#ifdef POK_NEEDS_DEBUG
/* Prints the context */
void pok_context_print(context_t* ctx) {
	printf(		"r1\t=%d\n"
				"r2\t=%d\n"
				"r3\t=%d\n"
				"r4\t=%d\n"
				"r5\t=%d\n"
				"r6\t=%d\n"
				"r7\t=%d\n"
				"r8\t=%d\n"
				"r9\t=%d\n"
				"r10\t=%d\n"
				"r11\t=%d\n"
				"r12\t=%d\n"
				"r13\t=%d\n"
				"r14\t=%d\n"
				"r15\t=%d\n"
				"r16\t=%d\n"
				"r17\t=%d\n"
				"r18\t=%d\n"
				"r19\t=%d\n", 
				ctx->r1,
				ctx->r2,
				ctx->r3,
				ctx->r4,
				ctx->r5,
				ctx->r6,
				ctx->r7,
				ctx->r8,
				ctx->r9,
				ctx->r10,
				ctx->r11,
				ctx->r12,
				ctx->r13,
				ctx->r14,
				ctx->r15,
				ctx->r16,
				ctx->r17,
				ctx->r18,
				ctx->r19);
}
#endif
#endif