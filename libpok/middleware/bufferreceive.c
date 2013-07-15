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

#ifdef POK_NEEDS_BUFFERS

#include <errno.h>
#include <types.h>
#include <core/time.h>
#include <core/event.h>
#include <libc/string.h>
#include <middleware/buffer.h>

extern pok_buffer_t	pok_buffers[POK_CONFIG_NB_BUFFERS];
extern char			pok_buffers_data[MAX_BUFFERS_DATA_SIZE];

pok_ret_t pok_buffer_receive (const pok_buffer_id_t		id, 
								const uint64_t			timeout, 
								void*					data, 
								pok_port_size_t*		len)
{

	pok_ret_t ret;

	if (id > POK_CONFIG_NB_BUFFERS)
	{
#ifdef DEBUG_BF
			printf("	too many buffers\n");			
#endif
			return POK_ERRNO_EINVAL;
	}

	if (pok_buffers[id].ready == FALSE)
	{
#ifdef DEBUG_BF
			printf("	not ready\n");			
#endif
		return POK_ERRNO_EINVAL;
	}

	if (data == POK_NULL)
	{
#ifdef DEBUG_BF
			printf("	data null\n");			
#endif
		return POK_ERRNO_EINVAL;
	}

#ifndef POK_NEEDS_SCHED_O1_SPLIT

	//pok_event_lock (pok_buffers[id].lock);

#ifdef DEBUG_BF
		printf("	buffer empty %d?\n",pok_buffers[id].empty);			
#endif
	while (pok_buffers[id].empty == TRUE)
	{
//		pok_event_lock (pok_buffers[id].lock);

#ifdef DEBUG_BF
	printf("	Buffer empty\n");		
#endif
		if (timeout == 0)
		{
//		pok_event_unlock (pok_buffers[id].lock);
		return POK_ERRNO_EMPTY;
		}
		else
		{
			// set the event message-in-the-buffer DOWN and waits for it
			pok_event_lock (pok_buffers[id].lock);
			ret = pok_event_wait (pok_buffers[id].lock, timeout);
			if (ret != POK_ERRNO_OK)
			{
				pok_event_unlock (pok_buffers[id].lock);
				return ret;
			}
		}
	}

#else /* POK_NEEDS_SCHED_O1_SPLIT is defined */
	/* wait for data (and for predecessor if the calling thread is a successor) */
	ret = pok_event_wait (pok_buffers[id].not_empty, timeout);
	if (ret != POK_ERRNO_OK)
	{
		//pok_event_unlock (pok_buffers[id].lock);
		return ret;
	}
#endif

	int16_t first = pok_buffers[id].first_size;
	*len = pok_buffers[id].msg_sizes[first];
#ifdef DEBUG_BF
	printf("	first message to read %d\n",first);		
	printf("	size of firt message %d\n",*len);
#endif		
	// % operation should be necessary only in case the flushall procedure at the end of the partition is never executed. 
	pok_buffers[id].first_size++;
	pok_buffers[id].status.nb_messages--;


	pok_port_size_t tmp_size;
	pok_port_size_t tmp_size2;

	if ((pok_buffers[id].off_b + *len) > pok_buffers[id].size)
	{
		tmp_size = pok_buffers[id].size - pok_buffers[id].off_b;
		memcpy (data, &pok_buffers_data[pok_buffers[id].index + pok_buffers[id].off_b], tmp_size);
		tmp_size2 = *len - tmp_size;
		memcpy (data + tmp_size, &pok_buffers_data[pok_buffers[id].index], tmp_size2);
	}
	else
	{
		memcpy (data, &pok_buffers_data[pok_buffers[id].index + pok_buffers[id].off_b], *len);
	}
#ifdef DEBUG_BF
	printf("	message to read  %c\n",pok_buffers_data[pok_buffers[id].index + pok_buffers[id].off_b]);	
	printf("	message read %c\n",((unsigned char *)data)[0]);
#endif
	pok_buffers[id].off_b = (pok_buffers[id].off_b + *len) % pok_buffers[id].size;

	if (pok_buffers[id].off_b == pok_buffers[id].off_e)
	{
#ifdef POK_NEEDS_SCHED_O1_SPLIT
		/* buffer is now empty, lock the not-empty lock object */
		pok_event_lock(pok_buffers[id].not_empty);
#endif
		pok_buffers[id].empty = TRUE;
		pok_buffers[id].full  = FALSE;
		pok_buffers[id].first_size=-1;
	}

	//pok_event_unlock (pok_buffers[id].lock);
#ifndef POK_NEEDS_SCHED_O1_SPLIT
	pok_event_broadcast (pok_buffers[id].lock);
#else /* POK_NEEDS_SCHED_O1_SPLIT is defined */
	pok_event_signal (pok_buffers[id].not_full);
#endif
	return POK_ERRNO_OK;
}

#endif /* POK_NEEDS_BUFFERS */
