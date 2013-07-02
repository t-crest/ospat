#include "activity.h"
#include <arinc653/types.h>
#include <arinc653/process.h>
#include <arinc653/partition.h>
#include "deployment.h"
#include <arinc653/event.h>

#ifdef POK_ARCH_PATMOS
	#include <stdio.h>
#endif


PROCESS_ID_TYPE arinc_threads[POK_CONFIG_NB_THREADS];

extern EVENT_ID_TYPE pok_arinc653_events_ids[1];
extern char* pok_arinc653_events_names[POK_CONFIG_ARINC653_NB_EVENTS];

int main ()
{

	PROCESS_ATTRIBUTE_TYPE tattr;
	RETURN_CODE_TYPE ret;

	printf("	part1 - Main thread\n");

	CREATE_EVENT (pok_arinc653_events_names[0], &(pok_arinc653_events_ids[0]), &(ret));
	printf("	Event %s created! EVENT ID: %u, ret: %d \n", pok_arinc653_events_names[0], (unsigned int) pok_arinc653_events_ids[0], ret);

	tattr.PERIOD = 400;
	tattr.BASE_PRIORITY = 10;
	tattr.ENTRY_POINT = thr1_1_job;
	CREATE_PROCESS (&(tattr), &(arinc_threads[1]), &(ret));

	tattr.PERIOD = APERIODIC_PROCESS;
	tattr.BASE_PRIORITY = 9;
	tattr.ENTRY_POINT = thr1_1bis_job;
	CREATE_PROCESS (&(tattr), &(arinc_threads[2]), &(ret));

	tattr.PERIOD = 400;
	tattr.BASE_PRIORITY = 8;
	tattr.ENTRY_POINT = thr1_3_job;
	CREATE_PROCESS (&(tattr), &(arinc_threads[3]), &(ret));

	tattr.PERIOD = APERIODIC_PROCESS;
	tattr.BASE_PRIORITY = 7;
	tattr.ENTRY_POINT = thr1_3bis_job;
	CREATE_PROCESS (&(tattr), &(arinc_threads[4]), &(ret));


	START (arinc_threads[1],&(ret));
	START (arinc_threads[2],&(ret));
	START (arinc_threads[3],&(ret));
	START (arinc_threads[4],&(ret));

	SET_PARTITION_MODE (NORMAL, &(ret));
	return 0;
}
