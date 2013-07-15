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

#include "core/syscall.h"

#define SYS_CALL_ADDR 	0x1C0900
#define NOT_USED(x) 	((void)(x))

uint32_t (*syscall)(void) = (uint32_t (*)(void)) SYS_CALL_ADDR;

pok_ret_t pok_syscall1  (pok_syscall_id_t syscall_id,
						uint32_t arg1)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);
	return syscall();
}
 
pok_ret_t pok_syscall2  (pok_syscall_id_t syscall_id,
						uint32_t arg1,
						uint32_t arg2)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);	
	NOT_USED(arg2);
	return syscall();
}
 
pok_ret_t pok_syscall3 (pok_syscall_id_t syscall_id,
						uint32_t arg1,
						uint32_t arg2,
						uint32_t arg3)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);	
	NOT_USED(arg2);
	NOT_USED(arg3);	
	return syscall();
}

pok_ret_t pok_syscall4 (pok_syscall_id_t syscall_id,
						uint32_t arg1,
						uint32_t arg2,
						uint32_t arg3,
						uint32_t arg4)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);	
	NOT_USED(arg2);
	NOT_USED(arg3);	
	NOT_USED(arg4);		
	return syscall();
}
 
pok_ret_t pok_syscall5 (pok_syscall_id_t syscall_id,
						uint32_t arg1,
						uint32_t arg2,
						uint32_t arg3,
						uint32_t arg4,
						uint32_t arg5)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);	
	NOT_USED(arg2);
	NOT_USED(arg3);	
	NOT_USED(arg4);	
	NOT_USED(arg5);	
	return syscall();
}

pok_ret_t pok_syscall6 (pok_syscall_id_t syscall_id,
						uint32_t arg1,
						uint32_t arg2,
						uint32_t arg3,
						uint32_t arg4,
						uint32_t arg5,
						uint32_t arg6)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);	
	NOT_USED(arg2);
	NOT_USED(arg3);	
	NOT_USED(arg4);	
	NOT_USED(arg5);		
	NOT_USED(arg6);
	return syscall();
}

pok_ret_t pok_syscall7 (pok_syscall_id_t  syscall_id,
						uint32_t arg1,
						uint32_t arg2,
						uint32_t arg3,
						uint32_t arg4,
						uint32_t arg5,
						uint32_t arg6,
						uint32_t arg7)
{
	NOT_USED(syscall_id);
	NOT_USED(arg1);	
	NOT_USED(arg2);
	NOT_USED(arg3);	
	NOT_USED(arg4);	
	NOT_USED(arg5);		
	NOT_USED(arg6);	
	NOT_USED(arg7);
	return syscall();
}