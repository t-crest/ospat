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


#ifndef __POK_TYPES_H__
#define __POK_TYPES_H__

#ifdef POK_ARCH_PPC
#include <arch/ppc/types.h>
#endif

#ifdef POK_ARCH_PATMOS
#include <arch/patmos/types.h>
#endif

#define POK_NULL	0
#define FALSE	0
#define TRUE	1
#define bool_t 	int
#define pok_bool_t int


typedef uint32_t	pok_port_size_t;
typedef uint8_t		pok_port_direction_t;
typedef uint8_t		pok_queueing_discipline_t;
typedef uint8_t		pok_port_id_t;
typedef uint32_t	pok_size_t;
typedef uint8_t		pok_range_t;
typedef long		pok_buffer_id_t;
typedef long		pok_blackboard_id_t;
typedef uint8_t		pok_mutex_id_t;
typedef uint8_t  	pok_event_id_t;	// must be of the same type of pok_lockobj_id_t (see kernel/include/types.h)  
typedef uint8_t		pok_sem_id_t;
typedef uint8_t		pok_partition_id_t;
typedef uint8_t		pok_sem_status_t;
typedef uint16_t	pok_sem_value_t;

typedef uint64_t	pok_time_t;

#endif
