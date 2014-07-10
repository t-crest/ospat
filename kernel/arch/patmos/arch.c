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

/**
 * \file	 arch/patmos/arch.c
 * \brief	Provide generic architecture access for Patmos architecture
 */

#include <bsp.h>
#include <types.h>
#include <errno.h>
#include <core/partition.h>
#include <core/time.h>
#include <core/thread.h>

 #ifdef POK_NEEDS_DEBUG
	#include <stdio.h>
 #endif

#include <machine/exceptions.h>
#include "rtc.h"

/** Patches for arch.c
 *  [1] pok_arch_init modified to enable FP bit in MSR
 *  [2] pok_arch_idle modified to enable interrupts for the IDLE thread
 *  [3] pok_arch_cache_freeze/unfreeze procedures
 */

unsigned* _loader_baseaddr;
/// _loader_off - the offset of the loading function (one per core)
unsigned* _loader_off;

extern unsigned long long time_new;

extern void _interval_ISR(void);

extern void _system_call_ISR(void);

extern void pok_clear_bss(void) __attribute__((used));

// Function used to start a system thread such as the idle thread
// thread's id and entry point are supposed to be in r18 and r19
// (see arch/thread.c)
void pok_arch_thread_start() {

	uint32_t entry;
	uint32_t id;

	asm (
		"mov %0 = $r18\n\t"
		"mov %1 = $r19\n\t"
		: "=r"(entry), "=r"(id));

	pok_thread_start_execution((void (*)())entry, id);
}

// Inits the architecture, no need to do anything in PATMOS
pok_ret_t pok_arch_init ()
{
	// Register _system_call_ISR function as interrupt service routine
	// for system call
	exc_register(3, _system_call_ISR);
	// Register _interval_ISR function as interrupt service routine
	// for timer interrupt
	exc_register(16, _interval_ISR);
	exc_register(17, _interval_ISR);

	return POK_ERRNO_OK;
}

// TODO: Disable preemption, maybe allow this in PATMOS
// for the moment it is not possible
pok_ret_t pok_arch_preempt_disable()
{
	return (POK_ERRNO_OK);
}

pok_ret_t pok_arch_preempt_enable() __attribute__((used));
// TODO: Enable preemption, see method above
pok_ret_t pok_arch_preempt_enable()
{
	// clear pending flags
	intr_clear_all_pending();
	// unmask interrupts
	intr_unmask_all();
	// enable interrupts
	intr_enable();
	
	return (POK_ERRNO_OK);
}

// Set the processor to idle
pok_ret_t pok_arch_idle()
{
	while (1)
	{
#ifdef POK_NEEDS_SCHED_O1
		// macro for pok_udpate_tick if schedO1
		// is enabled or for pok_tick_counter
		// both of timer.c
		uint64_t now = POK_GETTICK();

		if (POK_CURRENT_PARTITION.head_asynch_queue != POK_NULL && POK_CURRENT_PARTITION.head_asynch_queue->timestamp <= now)
		{
			pok_sched_end_period();
		}
#endif
	}
	return (POK_ERRNO_OK);	
}

// Computes the stack address of a given thread in a given 
// partition
uint32_t	 pok_thread_stack_addr	(const uint8_t	partition_id, const uint32_t	local_thread_id)
{
	return 	pok_partitions[partition_id].size - 
			(local_thread_id * (POK_USER_STACK_SIZE + POK_USER_SHADOW_STACK_SIZE));
}


// Computes the shadow stack address of a given thread in a given 
// partition
uint32_t	 pok_thread_shadow_stack_addr	(const uint8_t	partition_id, const uint32_t	local_thread_id)
{
	return 	pok_partitions[partition_id].size - 
			(local_thread_id * (POK_USER_STACK_SIZE + POK_USER_SHADOW_STACK_SIZE))
			- POK_USER_STACK_SIZE;
}
