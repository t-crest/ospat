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

 		.globl 		restore_context
		.type 		restore_context,@function
		.size 		restore_context, .Ltmp3-restore_context
		.fstart		restore_context, .Ltmp3-restore_context, 4
restore_context:

		// Reset r0 to 0
		and 	$r0				= $r0, 0x0

		li		$r1				= pok_current_context	

		lwc  	$r2 			= [$r1 + 1]
		lwc  	$r3 			= [$r1 + 2]
		lwc  	$r4 			= [$r1 + 3]
		lwc  	$r5 			= [$r1 + 4]
		lwc  	$r6 			= [$r1 + 5]
		lwc  	$r7 			= [$r1 + 6]
		lwc  	$r8 			= [$r1 + 7]
		lwc  	$r9 			= [$r1 + 8]
  		lwc  	$r10 			= [$r1 + 9]
		lwc  	$r11 			= [$r1 + 10]
		lwc  	$r12			= [$r1 + 11]
		lwc  	$r13 			= [$r1 + 12]
		lwc  	$r14 			= [$r1 + 13]
		lwc  	$r15 			= [$r1 + 14]
		lwc  	$r16 			= [$r1 + 15]
		lwc  	$r17 			= [$r1 + 16]
		lwc  	$r18 			= [$r1 + 17]
		lwc  	$r19 			= [$r1 + 18]
		lwc  	$r20 			= [$r1 + 19]
		lwc  	$r21 			= [$r1 + 20]
		lwc  	$r22 			= [$r1 + 21]
		lwc  	$r23 			= [$r1 + 22]
		lwc  	$r24 			= [$r1 + 23]
		lwc  	$r25 			= [$r1 + 24]
		lwc  	$r26 			= [$r1 + 25]
		lwc  	$r27 			= [$r1 + 26]
		lwc  	$r28 			= [$r1 + 27]
		lwc  	$r29 			= [$r1 + 28]
		lwc  	$r30 			= [$r1 + 29]
		lwc  	$r31 			= [$r1 + 30]

		// Spill everything from the stack cache
		sres 	0x3FFFF /* MAX_STACK_CACHE_SIZE */
		sfree 	0x3FFFF /* MAX_STACK_CACHE_SIZE */

		lwc  	$r2 			= [$r1 + 31]
		mts  	$s0 			= $r2
		lwc  	$r2 			= [$r1 + 32]
		mts  	$s1 			= $r2
		lwc  	$r2 			= [$r1 + 33]
		mts  	$s2 			= $r2
		lwc  	$r2 			= [$r1 + 34]
		mts  	$s3 			= $r2
		lwc  	$r2 			= [$r1 + 35]
		mts  	$s4 			= $r2
		lwc  	$r2 			= [$r1 + 36]
		mts  	$s5 			= $r2
		lwc  	$r2 			= [$r1 + 37]
		mts  	$s6 			= $r2
		lwc  	$r2 			= [$r1 + 38]
		mts  	$s7 			= $r2
		lwc  	$r2 			= [$r1 + 39]
		mts  	$s8 			= $r2
		lwc  	$r2 			= [$r1 + 41]
		mts  	$s10 			= $r2
		lwc  	$r2 			= [$r1 + 42]
		mts  	$s11 			= $r2
		lwc  	$r2 			= [$r1 + 43]
		mts  	$s11 			= $r2
		lwc  	$r2 			= [$r1 + 44]
		mts  	$s12 			= $r2
		lwc  	$r2 			= [$r1 + 45]
		mts  	$s13 			= $r2
		lwc  	$r2 			= [$r1 + 46]
		mts  	$s14 			= $r2
		lwc  	$r2 			= [$r1 + 47]
		mts  	$s15 			= $r2

		// Program counter in $r2
		lwc  	$r2 			= [$r1 + 40]
		mts  	$s9 			= $r2

		// Returning from interrupt
		brcf	$r2

		// Restore r1 and r2
		lwc  	$r2 			= [$r1 + 1]
		lwc  	$r1 			= [$r1 + 0]

		

.Ltmp3: