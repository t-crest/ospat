#include <arinc653/types.h>
#include <arinc653/time.h>
#include <arinc653/process.h>
#include <arinc653/event.h>
#include "deployment.h"

#ifdef POK_ARCH_PATMOS
	#include <stdio.h>
#endif


extern EVENT_ID_TYPE pok_arinc653_events_ids[1];

extern PROCESS_ID_TYPE arinc_threads[POK_CONFIG_NB_THREADS];


void* thr1_1_job ()
{
	RETURN_CODE_TYPE ret;
	while (1)
	{
		printf("Partition n. 1 - Thread n.1\n");

		/***************************************************************/
		/* Message processing code should be placed here               */
		/***************************************************************/

		printf("1: -- do something\n\t\t1 :: Waiting on an event\n\n");
		RESUME (arinc_threads[2], &(ret));
		PERIODIC_WAIT (&(ret));
	}
}

void* thr1_1bis_job()
{
	int flag = 0;
	RETURN_CODE_TYPE ret;
	SYSTEM_TIME_TYPE time = APERIODIC_PROCESS;
	printf("	Partition n. 1 - Thread n.2\n");
			printf ("\t2: Sporadic (wait evt)\n");
	while (1)
	{
		if (flag){
			printf ("\t2: Th self-suspending.........zzzz\n");
		} else {
			flag=1;
		}
		SUSPEND_SELF (time, &ret);
		printf ("\t2: Resume - Going to WAIT_EVENT \n");
		WAIT_EVENT (pok_arinc653_events_ids[0], 0, &(ret));
		printf ("\t2: Event %i is UP\n", (unsigned int) pok_arinc653_events_ids[0]);
	}
}

void* thr1_3_job ()
{
	RETURN_CODE_TYPE ret;
	while (1)
	{
		printf("Partition n. 1 - Thread n.3\n");

		/***************************************************************/
		/* Message processing code should be placed here               */
		/***************************************************************/

		printf(" 3: -- do something\n");
		printf(" 3: Setting an event UP\n\n");
		SET_EVENT (pok_arinc653_events_ids[0], &(ret));
		printf(" 3: Event SET -- Resume sporadic\n\n");
		RESUME (arinc_threads[4], &(ret));
		PERIODIC_WAIT (&(ret));
	}
}

void* thr1_3bis_job()
{
	int flag = 0;
	RETURN_CODE_TYPE ret;
	SYSTEM_TIME_TYPE time = APERIODIC_PROCESS;
	printf("\t4: Sporadic (after set evt)\n");
	while (1)
	{
		if (flag){
			printf("\t4: Resume - Continuation after event is set\n\n");
			RESET_EVENT (pok_arinc653_events_ids[0], &(ret));
			printf("\t4: Event %i is DOWN [%i]\n", (unsigned int) pok_arinc653_events_ids[0], ret);
			printf("\t4: Th self-suspending.........zzzz\n");
		} else {
			flag=1;
		}
		SUSPEND_SELF (time, &ret);
	}
}


