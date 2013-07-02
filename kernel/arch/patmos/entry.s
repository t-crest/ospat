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

		  .section ".start", "ax"
/* Entry point, starts the boot sequence */
base: 

		.globl 		_pok_reset
		.type 		_pok_reset,@function
		.size 		_pok_reset, .Ltmp8-_pok_reset
		.fstart		_pok_reset, .Ltmp8-_pok_reset, 4
_pok_reset:
	    li		$r1 				= pok_stack_end 
		li		$r2 				= pok_shadow_stack_end
		mov 	$r29 				= $r1
		mts 	$st  				= $r2
		mts 	$ss 				= $r2
		and 	$r0 				= $r0, 0x0

		brcf 	_pok_clear_bss
		nop
		nop	
		nop
.Ltmp8:


		.type 		_pok_clear_bss,@function
		.size 		_pok_clear_bss, .Ltmp12-_pok_clear_bss
		.fstart		_pok_clear_bss, .Ltmp12-_pok_clear_bss, 4
_pok_clear_bss:


	4:			li $r3 					= __bss_start
				li $r5 					= __bss_end
				cmplt $p1				= $r3, $r5
		(!$p1) 	br 6
	5:			swm	[$r3] 				= $r0
				add $r3 				= $r3, 4
				cmplt $p1				= $r3, $r5
		($p1)	br 5
				nop
				nop
				nop
	6:			
				li $r30					= _pok_clear_bss
				call 					pok_boot
				nop
				nop
				nop
.Ltmp12:

// Needs to be registered by the boot code
		.globl 		_interval_ISR
		.type 		_interval_ISR,@function
		.size 		_interval_ISR, .Ltmp3-_interval_ISR
		.fstart		_interval_ISR, .Ltmp3-_interval_ISR, 4
_interval_ISR:

		// Reset r0 to 0
		and 	$r0				= $r0, 0x0

		// Bootstrap context switch saving $r1 in the shadow stack
		sub		$r29			= $r29, 4
		swm		[$r29 + 0]		= $r1
		li		$r1				= pok_current_context	
		
		// Store general purpose registers
		swm  	[$r1 + 1] 		= $r2
		swm  	[$r1 + 2] 		= $r3
		swm  	[$r1 + 3] 		= $r4
		swm  	[$r1 + 4] 		= $r5
		swm  	[$r1 + 5] 		= $r6
		swm  	[$r1 + 6] 		= $r7
		swm  	[$r1 + 7] 		= $r8
		swm  	[$r1 + 8] 		= $r9
  		swm  	[$r1 + 9] 		= $r10
		swm  	[$r1 + 10] 		= $r11
		swm  	[$r1 + 11] 		= $r12
		swm  	[$r1 + 12] 		= $r13
		swm  	[$r1 + 13] 		= $r14
		swm  	[$r1 + 14] 		= $r15
		swm  	[$r1 + 15] 		= $r16
		swm  	[$r1 + 16] 		= $r17
		swm  	[$r1 + 17] 		= $r18
		swm  	[$r1 + 18] 		= $r19
		swm  	[$r1 + 19] 		= $r20
		swm  	[$r1 + 20] 		= $r21
		swm  	[$r1 + 21]		= $r22
		swm  	[$r1 + 22] 		= $r23
		swm  	[$r1 + 23] 		= $r24
		swm  	[$r1 + 24] 		= $r25
		swm  	[$r1 + 25] 		= $r26
		swm  	[$r1 + 26] 		= $r27
		swm  	[$r1 + 27] 		= $r28

		// Restore previous r29 value
		add		$r29			= $r29, 4
		swm  	[$r1 + 28] 		= $r29
		swm  	[$r1 + 29] 		= $r30
		swm  	[$r1 + 30] 		= $r31

  		sub     $r2 		    = $r5, $r6
  		sspill  $r2
  		swm     [$r1 + 48] 		= $r2
		// Spill everything from the stack cache
		//sres 	0x3FFFF /* MAX_STACK_CACHE_SIZE */
		//sfree 	0x3FFFF /* MAX_STACK_CACHE_SIZE */

		// Store special purpose registers
		mfs	 	$r2 			= $s0
		swm  	[$r1 + 31] 		= $r2
		mfs		$r2 			= $s1
		swm  	[$r1 + 32] 		= $r2
		mfs	 	$r2 			= $s2
		swm  	[$r1 + 33] 		= $r2
		mfs	 	$r2 			= $s3
		swm  	[$r1 + 34] 		= $r2
		mfs	 	$r2 			= $s4
		swm  	[$r1 + 35] 		= $r2
		mfs	 	$r2 			= $s5
		swm  	[$r1 + 36] 		= $r2
		mfs	 	$r2 			= $s6
		swm  	[$r1 + 37] 		= $r2
		mfs	 	$r2 			= $s7
		swm  	[$r1 + 38] 		= $r2
		mfs	 	$r2 			= $s8
		swm  	[$r1 + 39] 		= $r2
		mfs	 	$r2 			= $s9
		swm  	[$r1 + 40] 		= $r2
		mfs	 	$r2 			= $s10
		swm  	[$r1 + 41] 		= $r2
		mfs	 	$r2 			= $s11
		swm  	[$r1 + 42] 		= $r2
		mfs	 	$r2 			= $s12
		swm  	[$r1 + 43] 		= $r2
		mfs	 	$r2 			= $s13
		swm  	[$r1 + 44] 		= $r2
		mfs	 	$r2 			= $s14
		swm  	[$r1 + 45] 		= $r2
		mfs	 	$r2 			= $s15
		swm  	[$r1 + 46] 		= $r2

		// Restore r1
		sub		$r29			= $r29, 4
		lwc	 	$r2 			= [$r29 + 0]
		add		$r29			= $r29, 4
		swm  	[$r1 + 0] 		= $r2

		// Switch to kernel space
		li		$r29 			= pok_stack_end 
		mts 	$s6				= $r29
		li		$r29 			= pok_shadow_stack_end

		// Call interrupt routine 
		li		$r30 				= _interval_ISR
		call 	pok_arch_decr_int
		nop
		nop

		brcf 	restore_context
		nop
		nop
		nop

.Ltmp3:

/* System call function */
/* In Patmos this is not called by an interrupt */
/* caused by SC instruction (such as in powerpc) */
/* but is explicitly called upon an API system call */
		.globl		system_call
		.type 		system_call,@function
		.size 		system_call, .Ltmp2-system_call
		.org		0x900 - 4
		.fstart		system_call, .Ltmp2-system_call, 4
system_call:
		// Reset r0 to 0
		and 	$r0				= $r0, 0x0

		// Bootstrap context switch saving $r1 in the shadow stack
		sub		$r29			= $r29, 4
		swm		[$r29 + 0]		= $r1
		li		$r1				= pok_current_context	
		
		// Store general purpose registers
		swm  	[$r1 + 1] 		= $r2
		swm  	[$r1 + 2] 		= $r3
		swm  	[$r1 + 3] 		= $r4
		swm  	[$r1 + 4] 		= $r5
		swm  	[$r1 + 5] 		= $r6
		swm  	[$r1 + 6] 		= $r7
		swm  	[$r1 + 7] 		= $r8
		swm  	[$r1 + 8] 		= $r9
  		swm  	[$r1 + 9] 		= $r10
		swm  	[$r1 + 10] 		= $r11
		swm  	[$r1 + 11] 		= $r12
		swm  	[$r1 + 12] 		= $r13
		swm  	[$r1 + 13] 		= $r14
		swm  	[$r1 + 14] 		= $r15
		swm  	[$r1 + 15] 		= $r16
		swm  	[$r1 + 16] 		= $r17
		swm  	[$r1 + 17] 		= $r18
		swm  	[$r1 + 18] 		= $r19
		swm  	[$r1 + 19] 		= $r20
		swm  	[$r1 + 20] 		= $r21
		swm  	[$r1 + 21]		= $r22
		swm  	[$r1 + 22] 		= $r23
		swm  	[$r1 + 23] 		= $r24
		swm  	[$r1 + 24] 		= $r25
		swm  	[$r1 + 25] 		= $r26
		swm  	[$r1 + 26] 		= $r27
		swm  	[$r1 + 27] 		= $r28

		// Restore previous r29 value
		add		$r29			= $r29, 4
		swm  	[$r1 + 28] 		= $r29
		swm  	[$r1 + 29] 		= $r30
		swm  	[$r1 + 30] 		= $r31

  		sub     $r2 		    = $r5, $r6
  		sspill  $r2
  		swm     [$r1 + 48] 		= $r2
		// Spill everything from the stack cache
		//sres 	0x3FFFF /* MAX_STACK_CACHE_SIZE */
		//sfree 	0x3FFFF /* MAX_STACK_CACHE_SIZE */

		// Store special purpose registers
		mfs	 	$r2 			= $s0
		swm  	[$r1 + 31] 		= $r2
		mfs		$r2 			= $s1
		swm  	[$r1 + 32] 		= $r2
		mfs	 	$r2 			= $s2
		swm  	[$r1 + 33] 		= $r2
		mfs	 	$r2 			= $s3
		swm  	[$r1 + 34] 		= $r2
		mfs	 	$r2 			= $s4
		swm  	[$r1 + 35] 		= $r2
		mfs	 	$r2 			= $s5
		swm  	[$r1 + 36] 		= $r2
		mfs	 	$r2 			= $s6
		swm  	[$r1 + 37] 		= $r2
		mfs	 	$r2 			= $s7
		swm  	[$r1 + 38] 		= $r2
		mfs	 	$r2 			= $s8
		swm  	[$r1 + 39] 		= $r2
		mfs	 	$r2 			= $s9
		swm  	[$r1 + 40] 		= $r2
		mfs	 	$r2 			= $s10
		swm  	[$r1 + 41] 		= $r2
		mfs	 	$r2 			= $s11
		swm  	[$r1 + 42] 		= $r2
		mfs	 	$r2 			= $s12
		swm  	[$r1 + 43] 		= $r2
		mfs	 	$r2 			= $s13
		swm  	[$r1 + 44] 		= $r2
		mfs	 	$r2 			= $s14
		swm  	[$r1 + 45] 		= $r2
		mfs	 	$r2 			= $s15
		swm  	[$r1 + 46] 		= $r2

		// Restore r1
		sub		$r29			= $r29, 4
		lwc	 	$r2 			= [$r29 + 0]
		add		$r29			= $r29, 4
		swm  	[$r1 + 0] 		= $r2

		// Switch to kernel space
		li		$r29 			= pok_stack_end 
		mts 	$s6				= $r29
		li		$r29 			= pok_shadow_stack_end

		/* Function call */
		li		$r30 				= system_call
		call 	pok_arch_sc_int
		nop
		nop
		nop

		brcf 	restore_context /* pok_arch_rfi */
		nop
		nop
		nop
.Ltmp2:

	.section ".bss", "aw"
pok_stack:
		.space 8 * 1024
		.globl pok_stack_end
pok_stack_end:

pok_cache_stack:
		.space 8 * 1024
		.globl pok_shadow_stack_end
pok_shadow_stack_end:

pok_save_area:
		.space 4 * 8
		.section ".reset", "ax"

