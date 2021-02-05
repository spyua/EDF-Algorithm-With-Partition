#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "task.h"
#include "partition.h"
#include "schedule.h"

node _taskSet[TASK_NUM];
node _coreSet[CORE_NUM];
link _coreList[CORE_NUM];
link _readyQueue;

//設置Task參數
void InitialTask(Task item[])
{
	item[0].taskNo = 1;
	item[0].period = 5;
	item[0].exTimeDef = 1;
	item[0].exTime = item[0].exTimeDef;
	item[0].deadline = item[0].period;
	item[0].utilization = (double)item[0].exTime / item[0].period;


	item[1].taskNo = 2;
	item[1].period = 50;
	item[1].exTimeDef = 20;
	item[1].exTime = item[1].exTimeDef;
	item[1].deadline = item[1].period;
	item[1].utilization = (double)item[1].exTime / item[1].period;


	item[2].taskNo = 3;
	item[2].period = 125;
	item[2].exTimeDef = 40;
	item[2].exTime = item[2].exTimeDef;
	item[2].deadline = item[2].period;
	item[2].utilization = (double)item[2].exTime / item[2].period;


	item[3].taskNo = 4;
	item[3].period = 70;
	item[3].exTimeDef = 25;
	item[3].exTime = item[3].exTimeDef;
	item[3].deadline = item[3].period;
	item[3].utilization = (double)item[3].exTime / item[3].period;


	item[4].taskNo = 5;
	item[4].period = 20;
	item[4].exTimeDef = 4;
	item[4].exTime = item[4].exTimeDef;
	item[4].deadline = item[4].period;
	item[4].utilization = (double)item[4].exTime / item[4].period;


	item[5].taskNo = 6;
	item[5].period = 24;
	item[5].exTimeDef = 8;
	item[5].exTime = item[5].exTimeDef;
	item[5].deadline = item[5].period;
	item[5].utilization = (double)item[5].exTime / item[5].period;


	item[6].taskNo = 7;
	item[6].period = 20;
	item[6].exTimeDef = 3;
	item[6].exTime = item[6].exTimeDef;
	item[6].deadline = item[6].period;
	item[6].utilization = (double)item[6].exTime / item[6].period;


	item[7].taskNo = 8;
	item[7].period = 120;
	item[7].exTimeDef = 40;
	item[7].exTime = item[7].exTimeDef;
	item[7].deadline = item[7].period;
	item[7].utilization = (double)item[7].exTime / item[7].period;


	item[8].taskNo = 9;
	item[8].period = 15;
	item[8].exTimeDef = 2;
	item[8].exTime = item[8].exTimeDef;
	item[8].deadline = item[8].period;
	item[8].utilization = (double)item[8].exTimeDef / item[8].period;

}


int main(int argc, char* argv[])
{

	InitialTaskInfo(_taskSet);
	InitialTask(_taskSet);
	InitialCoreInfo(_coreSet);

	printf("Task Set\n");
	printf("--------------------------------------------------------------------------------\n");
	for (int taskCnt = 0; taskCnt < TASK_NUM; taskCnt++)
		_readyQueue = InsertTaskToList(_taskSet[taskCnt], _readyQueue);

	DisplayTaskList(_readyQueue);

	//BestFit(TaskSet, CoreSet, CoreList);
	FirstFit(_taskSet, _coreSet, _coreList);
	//WorstFit(TaskSet, CoreSet, CoreList);

	for (int coreCnt = 0; coreCnt < CORE_NUM; coreCnt++) {

		int coreIDDisplay = coreCnt + 1;

		if (_coreList[coreCnt] == NULL)
			break;
		printf("Core%d\t U=%f\n", coreIDDisplay, 1.0 - _coreSet[0].utilization);
		DisplayTaskList(_coreList[coreCnt]);
		EDF_SchedSimulator(_coreList[coreCnt], coreIDDisplay, 0, 100);
	}


	return 0;
}

