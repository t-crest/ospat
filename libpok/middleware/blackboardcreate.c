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

#include <errno.h>
#include <types.h>
#include <libc/string.h>
#include <core/event.h>
#include <middleware/blackboard.h>

extern pok_blackboard_t	pok_blackboards[POK_CONFIG_NB_BLACKBOARDS];
extern char*			pok_blackboards_names[POK_CONFIG_NB_BLACKBOARDS];
pok_size_t				pok_blackboards_data_index = 0;
pok_bool_t				first_time = TRUE;

pok_ret_t pok_blackboard_create (char*									  name, 
								const pok_port_size_t				 msg_size, 
								pok_blackboard_id_t*				  id)
{
	pok_ret_t	ret;
	uint8_t	  n;

	if (first_time)
	{
		pok_blackboard_init();
		first_time = FALSE;
	}

	for (n=0 ; n < POK_CONFIG_NB_BLACKBOARDS ; n++)
	{
		if (streq (name, pok_blackboards_names[n]))
		{
			if (pok_blackboards[n].ready == TRUE)
			{
				return POK_ERRNO_READY;
			}

			ret = pok_event_create (&pok_blackboards[n].lock);

#ifdef POK_NEEDS_SCHED_O1_SPLIT
			pok_event_lock (pok_blackboards[n].lock);
#endif

			if (ret != POK_ERRNO_OK)
			{
				return ret;
			}

			pok_blackboards[n].ready					= TRUE;
			pok_blackboards[n].empty					= TRUE;
			pok_blackboards[n].index					= pok_blackboards_data_index;
			pok_blackboards[n].waiting_processes		= 0;
			pok_blackboards[n].size					 	= msg_size;
			*id											= n;
			pok_blackboards_data_index				 	= pok_blackboards_data_index + msg_size;
			return POK_ERRNO_OK;
		}
	}

	return POK_ERRNO_EINVAL;
}

#endif /* POK_NEEDS_BLACKBOARDS */
