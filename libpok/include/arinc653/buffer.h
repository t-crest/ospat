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


#ifdef POK_NEEDS_ARINC653_BUFFER

/* BUFFER constant and type definitions and management services	*/ 
 
#ifndef APEX_BUFFER 
#define APEX_BUFFER 

#ifndef POK_NEEDS_ARINC653_PROCESS
#define POK_NEEDS_ARINC653_PROCESS
#endif

#include <arinc653/types.h>
#include <arinc653/process.h>
 
#define  MAX_NUMBER_OF_BUFFERS	 SYSTEM_LIMIT_NUMBER_OF_BUFFERS 
 
typedef  NAME_TYPE		 BUFFER_NAME_TYPE; 
 
typedef  APEX_INTEGER	 BUFFER_ID_TYPE; 
 
typedef struct { 
	MESSAGE_RANGE_TYPE  NB_MESSAGE; 
	MESSAGE_RANGE_TYPE  MAX_NB_MESSAGE; 
	MESSAGE_SIZE_TYPE	MAX_MESSAGE_SIZE;
	WAITING_RANGE_TYPE  WAITING_PROCESSES;
} BUFFER_STATUS_TYPE; 

 
extern void CREATE_BUFFER ( 
		/*in */ BUFFER_NAME_TYPE		BUFFER_NAME, 
		/*in */ MESSAGE_SIZE_TYPE		MAX_MESSAGE_SIZE, 
		/*in */ MESSAGE_RANGE_TYPE		MAX_NB_MESSAGE, 
		/*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE, 
		/*out*/ BUFFER_ID_TYPE			*BUFFER_ID, 
		/*out*/ RETURN_CODE_TYPE		*RETURN_CODE ); 
 
extern void SEND_BUFFER ( 
		 /*in */ BUFFER_ID_TYPE			BUFFER_ID, 
		 /*in */ MESSAGE_ADDR_TYPE		MESSAGE_ADDR,		 /* by reference */ 
		 /*in */ MESSAGE_SIZE_TYPE		LENGTH, 
		 /*in */ SYSTEM_TIME_TYPE		TIME_OUT, 
		 /*out*/ RETURN_CODE_TYPE		*RETURN_CODE ); 
 
extern void RECEIVE_BUFFER ( 
		 /*in */ BUFFER_ID_TYPE			BUFFER_ID, 
		 /*in */ SYSTEM_TIME_TYPE		TIME_OUT, 
		 /*out*/ MESSAGE_ADDR_TYPE		MESSAGE_ADDR, 
		 /*out*/ MESSAGE_SIZE_TYPE		*LENGTH, 
		 /*out*/ RETURN_CODE_TYPE		*RETURN_CODE ); 
 
extern void GET_BUFFER_ID ( 
		 /*in */ BUFFER_NAME_TYPE		BUFFER_NAME, 
		 /*out*/ BUFFER_ID_TYPE			*BUFFER_ID, 
		 /*out*/ RETURN_CODE_TYPE		*RETURN_CODE ); 
 
extern void GET_BUFFER_STATUS ( 
		 /*in */ BUFFER_ID_TYPE			BUFFER_ID, 
		 /*out*/ BUFFER_STATUS_TYPE		*BUFFER_STATUS, 
		 /*out*/ RETURN_CODE_TYPE		*RETURN_CODE ); 
 
#endif 
#endif
