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


#if defined (POK_NEEDS_PORTS_SAMPLING) || defined (POK_NEEDS_PORTS_QUEUEING)
#include <types.h>
#include <core/debug.h>
#include <core/error.h>
#include <middleware/port.h>

extern pok_port_t pok_ports[POK_CONFIG_NB_PORTS];

void pok_port_init (void)
{
	uint8_t i;

	for (i = 0 ; i < POK_CONFIG_NB_PORTS ; i++)
	{
		pok_ports[i].size	= 0;
		pok_ports[i].off_b	= 0;
		pok_ports[i].off_e	= 0;
		pok_ports[i].empty	= TRUE;
		pok_ports[i].full	= FALSE;
		pok_ports[i].index	= 0;
		pok_ports[i].ready	= FALSE;
		pok_ports[i].kind	= POK_PORT_KIND_INVALID;
		pok_ports[i].last_receive = 0;
		pok_ports[i].must_be_flushed = FALSE;
	}
}

#endif
