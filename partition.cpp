#include <stdio.h>
#include <stdlib.h>
#include "task.h"

int FindLargestUtiliztionCoreID(node Core[], double taskUtilization) {

	double cmpUtilization = 0.0;
	int  coreID = 0;

	for (int coreCnt = CORE_NUM - 1; coreCnt >= 0; coreCnt--)
	{
		if (Core[coreCnt].utilization - taskUtilization > 0.0 && cmpUtilization <= Core[coreCnt].utilization)
		{
			cmpUtilization = Core[coreCnt].utilization;
			coreID = coreCnt;
		}
	}
	return coreID;
}

int FindSmallestUtiliztionCoreID(node Core[], double taskUtilization) {

	double cmpUtilization = 1.0;
	int  coreID = 0;

	for (int coreCnt = CORE_NUM - 1; coreCnt >= 0; coreCnt--)
	{
		if (Core[coreCnt].utilization - taskUtilization > 0.0 && cmpUtilization >= Core[coreCnt].utilization)
		{
			cmpUtilization = Core[coreCnt].utilization;
			coreID = coreCnt;
		}
	}
	return coreID;
}


//FirstFit Algorithm
void FirstFit(node Task[], node Core[], link Clist[])
{
	printf("First Fit\n\n");
	
	for (int taskCnt = 0; taskCnt < TASK_NUM; taskCnt++) {
		for (int coreCnt = 0; coreCnt < CORE_NUM; coreCnt++) {
			if (Core[coreCnt].utilization - Task[taskCnt].utilization > 0.0) {
				Clist[coreCnt] = InsertTaskToList(Task[taskCnt], Clist[coreCnt]);
				Core[coreCnt].utilization = Core[coreCnt].utilization - Task[taskCnt].utilization;
				break;
			}
		}
	}
}

//BestFit Algorithm
void BestFit(node Task[], node Core[], link Clist[])
{
	printf("Best Fit\n\n");

	int  findCoreID = 0;

	//Insert first task on first core
	Clist[0] = InsertTaskToList(Task[0], Clist[0]);
	Core[0].utilization = Core[0].utilization - Task[0].utilization;

	for (int taskCnt = 1; taskCnt < TASK_NUM; taskCnt++) {

		findCoreID = FindSmallestUtiliztionCoreID(Core, Task[taskCnt].utilization);

		if (Core[findCoreID].utilization - Task[taskCnt].utilization > 0.0)
		{
			Clist[findCoreID] = InsertTaskToList(Task[taskCnt], Clist[findCoreID]);
			Core[findCoreID].utilization = Core[findCoreID].utilization - Task[taskCnt].utilization;
			continue;
		}
	}
}

//WorstFit Algorithm
void WorstFit(node Task[], node Core[], link Clist[])
{
	printf("Worst Fit\n\n");

	int  findCoreID = 0;

	//Insert first task on first core
	Clist[0] = InsertTaskToList(Task[0], Clist[0]);
	Core[0].utilization = Core[0].utilization - Task[0].utilization;

	for (int taskCnt = 1; taskCnt < TASK_NUM; taskCnt++) {

		findCoreID = FindLargestUtiliztionCoreID(Core, Task[taskCnt].utilization);

		if (Core[findCoreID].utilization - Task[taskCnt].utilization > 0.0)
		{
			Clist[findCoreID] = InsertTaskToList(Task[taskCnt], Clist[findCoreID]);
			Core[findCoreID].utilization = Core[findCoreID].utilization - Task[taskCnt].utilization;
			continue;
		}
	}
}

