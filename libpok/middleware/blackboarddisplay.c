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

#include <core/dependencies.h>

#ifdef POK_NEEDS_BLACKBOARDS

#include <types.h>
#include <errno.h>
#include <core/event.h>
#include <libc/string.h>
#include <middleware/blackboard.h>

extern pok_blackboard_t		pok_blackboards[POK_CONFIG_NB_BLACKBOARDS];
extern char					pok_blackboards_data[MAX_BLACKBOARDS_DATA_SIZE];


pok_ret_t pok_blackboard_display (const pok_blackboard_id_t	id, 
									const void*				message, 
									const pok_port_size_t	len)
{

	if (id > POK_CONFIG_NB_BLACKBOARDS)
	{
		return POK_ERRNO_EINVAL;
	}

	if (message == POK_NULL)
	{
		return POK_ERRNO_EINVAL;
	}

	if (len > pok_blackboards[id].size)
	{
		return POK_ERRNO_SIZE;
	}

	if (pok_blackboards[id].ready != TRUE)
	{
		return POK_ERRNO_EINVAL;
	}

	//pok_event_lock (pok_blackboards[id].lock);

	memcpy (&pok_blackboards_data[pok_blackboards[id].index], message, len);

	pok_blackboards[id].msgsize = len;
	
	pok_blackboards[id].empty = FALSE;

	//pok_event_unlock (pok_blackboards[id].lock);

	pok_event_broadcast (pok_blackboards[id].lock);

	return POK_ERRNO_OK;
}

#endif
