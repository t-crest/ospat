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


#include <arinc653/types.h>


/* SAMPLING PORT constant and type definitions and management services*/ 
 
#ifndef APEX_SAMPLING 
#define APEX_SAMPLING 
 
#define  MAX_NUMBER_OF_SAMPLING_PORTS	SYSTEM_LIMIT_NUMBER_OF_SAMPLING_PORTS 
 
typedef  NAME_TYPE		 SAMPLING_PORT_NAME_TYPE; 
 
typedef  APEX_INTEGER	 SAMPLING_PORT_ID_TYPE; 
 
typedef  enum { INVALID = 0, VALID = 1 } VALIDITY_TYPE; 
 
typedef struct
{ 
	SYSTEM_TIME_TYPE		REFRESH_PERIOD; 
	MESSAGE_SIZE_TYPE		MAX_MESSAGE_SIZE; 
	PORT_DIRECTION_TYPE		PORT_DIRECTION; 
	VALIDITY_TYPE			LAST_MSG_VALIDITY; 
} SAMPLING_PORT_STATUS_TYPE; 
 
extern void CREATE_SAMPLING_PORT
		(const SAMPLING_PORT_NAME_TYPE	/* in */	SAMPLING_PORT_NAME, 
		const MESSAGE_SIZE_TYPE			/* in */	MAX_MESSAGE_SIZE, 
		const PORT_DIRECTION_TYPE		/* in */	PORT_DIRECTION, 
		const SYSTEM_TIME_TYPE		 	/* in */	REFRESH_PERIOD, 
		SAMPLING_PORT_ID_TYPE * const	/* out */	SAMPLING_PORT_ID, 
		RETURN_CODE_TYPE * const  		/* out */	RETURN_CODE);
 
extern void WRITE_SAMPLING_MESSAGE
		(const SAMPLING_PORT_ID_TYPE	/* in */	SAMPLING_PORT_ID, 
		const MESSAGE_ADDR_TYPE 		/* in */	MESSAGE_ADDR, 
		const MESSAGE_SIZE_TYPE			/* in */	LENGTH, 
		RETURN_CODE_TYPE * const  		/* out */	RETURN_CODE);
 
extern void READ_SAMPLING_MESSAGE
		(const SAMPLING_PORT_ID_TYPE	/* in */	SAMPLING_PORT_ID, 
		MESSAGE_ADDR_TYPE /* Array */	/* in out */MESSAGE_ADDR, 
		MESSAGE_SIZE_TYPE * const		/* out */	LENGTH, 
		VALIDITY_TYPE * const			/* out */	VALIDITY, 
		RETURN_CODE_TYPE * const		/* out */	RETURN_CODE);

extern void GET_SAMPLING_PORT_ID
		(const SAMPLING_PORT_NAME_TYPE	/* in */	SAMPLING_PORT_NAME, 
		SAMPLING_PORT_ID_TYPE * const	/* out */	SAMPLING_PORT_ID, 
		RETURN_CODE_TYPE * const		/* out */	RETURN_CODE);

extern void GET_SAMPLING_PORT_STATUS
		(const SAMPLING_PORT_ID_TYPE	/* in */	SAMPLING_PORT_ID, 
		SAMPLING_PORT_STATUS_TYPE * const /* out */	SAMPLING_PORT_STATUS, 
		RETURN_CODE_TYPE * const  		/* out */	RETURN_CODE);

#endif
