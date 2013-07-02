/*
 *  Copyright (c) 2012  University of Padua, Department of Mathematics
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
 *  This file incorporates work covered by the following copyright and
 *  permission notice:
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

#include "rtc.h"

/** Patches for arch.c
 *  [1] pok_arch_init modified to enable FP bit in MSR
 *  [2] pok_arch_idle modified to enable interrupts for the IDLE thread
 *  [3] pok_arch_cache_freeze/unfreeze procedures
 */

extern unsigned long long time_new;

extern void _interval_ISR(void);

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
	// Register _interval_ISR function as interrupt service routine
	// for timer interrupt
	__PATMOS_RTC_WR_ISR((unsigned int)_interval_ISR)

	return POK_ERRNO_OK;
}

// TODO: Disable preemption, maybe allow this in PATMOS
// for the moment it is not possible
pok_ret_t pok_arch_preempt_disable()
{
	return (POK_ERRNO_OK);
}

// TODO: Enable preemption, see method above
pok_ret_t pok_arch_preempt_enable()
{
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
	
#ifdef POK_SKIP_IDLE
		if (POK_CURRENT_PARTITION.head_asynch_queue == POK_NULL)
		{
			set_patmos_tb(time_new);
		}
#endif
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
