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
 
 /*
 * Context switch fucntion, r3 holds a pointer to the old context
 */
 		.globl 		pok_context_switch
		.type 		pok_context_switch,@function
		.size 		pok_context_switch, .Ltmp6-pok_context_switch
		.fstart		pok_context_switch, .Ltmp6-pok_context_switch, 4
pok_context_switch:
		// we restore r1 and r2 from 
		// the elected context
		// other state will be restored by the return 
		// from trap
		li		$r3				= pok_current_context
		nop
		lwc		$r3 			= [$r3 + 0]
		ret
		lwc  	$r1 			= [$r3 + 0]
		lwc  	$r2 			= [$r3 + 1]
		nop

.Ltmp6:

 		.globl 		restore_context
		.type 		restore_context,@function
		.size 		restore_context, .Ltmp3-restore_context
		.fstart		restore_context, .Ltmp3-restore_context, 4
restore_context:

		// Restore previous context
		// we leave untouched r1 and r2 that
		// hold return value of the system call
		and 	$r0				= $r0, 0x0

		li		$r3				= pok_current_context
		nop
		lwc		$r3 			= [$r3 + 0]
		nop

		// General purpose registers
		lwc  	$r5 			= [$r3 + 4]
		lwc  	$r6 			= [$r3 + 5]
		lwc  	$r7 			= [$r3 + 6]
		lwc  	$r8 			= [$r3 + 7]
		lwc  	$r9 			= [$r3 + 8]
  		lwc  	$r10 			= [$r3 + 9]
		lwc  	$r11 			= [$r3 + 10]
		lwc  	$r12			= [$r3 + 11]
		lwc  	$r13 			= [$r3 + 12]
		lwc  	$r14 			= [$r3 + 13]
		lwc  	$r15 			= [$r3 + 14]
		lwc  	$r16 			= [$r3 + 15]
		lwc  	$r17 			= [$r3 + 16]
		lwc  	$r18 			= [$r3 + 17]
		lwc  	$r19 			= [$r3 + 18]
		lwc  	$r20 			= [$r3 + 19]
		lwc  	$r21 			= [$r3 + 20]
		lwc  	$r22 			= [$r3 + 21]
		lwc  	$r23 			= [$r3 + 22]
		lwc  	$r24 			= [$r3 + 23]
		lwc  	$r25 			= [$r3 + 24]
		lwc  	$r26 			= [$r3 + 25]
		lwc  	$r27 			= [$r3 + 26]
		lwc  	$r28 			= [$r3 + 27]
		lwc  	$r29 			= [$r3 + 28]
		lwc  	$r30 			= [$r3 + 29]
		lwc  	$r31 			= [$r3 + 30]

		// Special purpose registers
		lwc  	$r4 			= [$r3 + 31]
		nop
		mts  	$s0 			= $r4
		lwc  	$r4 			= [$r3 + 32]
		nop
		mts  	$s1 			= $r4
		lwc  	$r4 			= [$r3 + 33]
		nop
		mts  	$s2 			= $r4
		lwc  	$r4 			= [$r3 + 34]
		nop
		mts  	$s3 			= $r4
		lwc  	$r4 			= [$r3 + 35]
		nop
		mts  	$s4 			= $r4
		lwc  	$r4 			= [$r3 + 36]
		nop
		mts  	$s5 			= $r4
		lwc  	$r4 			= [$r3 + 37]
		nop
		mts  	$s6 			= $r4
		lwc  	$r4 			= [$r3 + 38]
		nop
		mts  	$s7 			= $r4
		lwc  	$r4 			= [$r3 + 39]
		nop
		mts  	$s8 			= $r4
		lwc  	$r4 			= [$r3 + 40]
		nop
		mts  	$s9 			= $r4
		lwc  	$r4 			= [$r3 + 41]
		nop
		mts  	$s10 			= $r4
		lwc  	$r4 			= [$r3 + 42]
		nop
		mts  	$s11 			= $r4
		lwc  	$r4 			= [$r3 + 43]
		nop
		mts  	$s12 			= $r4
		lwc  	$r4 			= [$r3 + 44]
		nop
		mts  	$s13 			= $r4
		lwc  	$r4 			= [$r3 + 45]
		nop
		mts  	$s14 			= $r4
		lwc  	$r4 			= [$r3 + 46]
		nop
		mts  	$s15 			= $r4

		// Stack cache state
		lwm     $r4           	= [$r3 + 47]
		nop
  		sens    $r4
		// Spill everything from the stack cache
		//sres 	0x3FFFF /* MAX_STACK_CACHE_SIZE */
		//sfree 	0x3FFFF /* MAX_STACK_CACHE_SIZE */

		// Restore r1 and r2
		lwc  	$r4 			= [$r3 + 3]
		lwc  	$r3 			= [$r3 + 2]		

	    xret
	    nop
	    nop
	    nop	

.Ltmp3: