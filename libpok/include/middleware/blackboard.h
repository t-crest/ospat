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



#ifndef  __POK_USER_BLACKBOARD_H__
#define __POK_USER_BLACKBOARD_H__

#ifdef POK_NEEDS_BLACKBOARDS

#include <types.h>
#include <errno.h>

#ifndef POK_CONFIG_MAX_BLACKBOARDS_MESSAGE_SIZE
#define POK_CONFIG_MAX_BLACKBOARDS_MESSAGE_SIZE 256
#endif

#define MAX_BLACKBOARDS_DATA_SIZE	POK_CONFIG_MAX_BLACKBOARDS_MESSAGE_SIZE*POK_CONFIG_NB_BLACKBOARDS

typedef struct
{
	pok_size_t	size;
	pok_size_t	msgsize;
	pok_bool_t	empty;
	pok_range_t	waiting_processes;
	pok_size_t	index;
	pok_bool_t	ready;
	pok_event_id_t	lock;
}pok_blackboard_t;

typedef struct
{
	pok_port_size_t	msg_size;
	pok_bool_t		empty;
	pok_range_t		waiting_processes;
}pok_blackboard_status_t;


pok_ret_t pok_blackboard_create (char*					name,
								const pok_size_t		msg_size,
								pok_blackboard_id_t*	id);

pok_ret_t pok_blackboard_read (const pok_blackboard_id_t	id,
								const uint64_t				timeout,
								void*						data,
								pok_port_size_t*			len);

pok_ret_t pok_blackboard_display (const pok_blackboard_id_t	id,
								const void*					message,
								const pok_port_size_t		len);

pok_ret_t pok_blackboard_clear (const pok_blackboard_id_t	id);

pok_ret_t pok_blackboard_id	  (char*						name,
								pok_blackboard_id_t*		id);

pok_ret_t pok_blackboard_status (const pok_blackboard_id_t	id,
								pok_blackboard_status_t*	status);
#endif
#endif

