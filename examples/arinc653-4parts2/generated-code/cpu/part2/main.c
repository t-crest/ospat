#include "activity.h"
#include <arinc653/types.h>
#include <arinc653/process.h>
#include <arinc653/partition.h>
#include "deployment.h"
#ifdef POK_ARCH_PATMOS
  #include <stdio.h>
#endif

PROCESS_ID_TYPE arinc_threads[POK_CONFIG_NB_THREADS];


int main ()
{

	PROCESS_ATTRIBUTE_TYPE tattr;
	RETURN_CODE_TYPE ret;

	printf("	part2 - Main thread\n");
	tattr.PERIOD = 400;
	tattr.BASE_PRIORITY = 8;
	tattr.ENTRY_POINT = thr2_1_job;
	CREATE_PROCESS (&(tattr), &(arinc_threads[1]), &(ret));

	tattr.PERIOD = 400;
	tattr.BASE_PRIORITY = 9;
	tattr.ENTRY_POINT = thr2_2_job;
	CREATE_PROCESS (&(tattr), &(arinc_threads[2]), &(ret));


	START (arinc_threads[1],&(ret));
  START (arinc_threads[2],&(ret));

	SET_PARTITION_MODE (NORMAL, &(ret));
	return 0;
}
