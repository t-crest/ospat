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

#ifndef __POK_PATMOS_THREAD_H__
#define __POK_PATMOS_THREAD_H__

#include <types.h>
#ifdef POK_NEEDS_DEBUG
	#include <libc.h>
#endif 

typedef struct
{
	uint32_t r1;	/*	0	*/
	uint32_t r2;
	uint32_t r3;	/*	8	*/
	uint32_t r4;
	uint32_t r5;	/*	16	*/
	uint32_t r6;
	uint32_t r7;	/*	24	*/
	uint32_t r8;
	uint32_t r9;	/*	32	*/
	uint32_t r10;
	uint32_t r11;	/*	40	*/
	uint32_t r12;
	uint32_t r13;	/*	48	*/
	uint32_t r14;
	uint32_t r15;	/*	56	*/
	uint32_t r16;
	uint32_t r17;	/*	64	*/
	uint32_t r18;
	uint32_t r19;	/*	72	*/
	uint32_t r20;
	uint32_t r21;	/*	80	*/	
	uint32_t r22;
	uint32_t r23;	/*	88	*/	
	uint32_t r24;
	uint32_t r25;	/*	96	*/
	uint32_t r26;
	uint32_t r27;	/*	104	*/
	// Frame pointer used by compiler
	uint32_t r28;
	// Stack pointer used by compiler
	uint32_t r29;	/*	112	*/	
	uint32_t r30;
	uint32_t r31;	/*	120	*/

	// Predicate registers status
	uint32_t s0;
	uint32_t s1;	/*	128	*/
	uint32_t s2;
	uint32_t s3;	/*	136	*/
	uint32_t s4;
	uint32_t s5;	/*	144	*/
	// First frame spilled to main memory
	uint32_t s6;
	uint32_t s7;	/*	152	*/
	uint32_t s8;
	/* Program counter */
	uint32_t s9;	/*	160	*/
	uint32_t s10;
	uint32_t s11;	/*	168	*/
	uint32_t s12;
	uint32_t s13;	/*	176	*/
	uint32_t s14;
	uint32_t s15;	/*	184	*/

	uint32_t ssize; /*	188	*/
	uint32_t exc;

} context_t;

uint32_t		pok_context_create(uint32_t id,
						uint32_t stack_size,
						uint32_t shadow_stack_size,
						uint32_t entry);

void			pok_context_switch(uint32_t old_context);

#ifdef POK_NEEDS_DEBUG
void 			pok_context_print(context_t* ctx);
#endif


#endif /* __POK_PATMOS_THREAD_H__ */
