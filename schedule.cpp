#include <stdio.h>
#include <stdlib.h>
#include "task.h"

node SearchSmallestDeadline(link taskList)
{
	link tempStart = taskList;
	node min_deadline;
	min_deadline.deadline = MAX_DEADLINE_SET;

	for (taskList;; taskList = taskList->front) {

		//找出最短deadline 並replace到min_deadline node
		if (taskList->deadline < min_deadline.deadline)
		{
			min_deadline.taskNo = taskList->taskNo;
			min_deadline.period = taskList->period;
			min_deadline.exTime = taskList->exTime;
			min_deadline.exTimeDef = taskList->exTimeDef;
			min_deadline.deadline = taskList->deadline;
			min_deadline.utilization = taskList->utilization;
		}

		if (taskList->front == tempStart)
			break;
	}

	return min_deadline;
}

// Wait Clean
void DisplayScheduleStatus(int coreID, int timeTick, node currentTask, node previousTask, node nextTask) {
	
	//if (currentTask.exTime == 0 && currentTask.taskNo != nextTask.taskNo) {
	//	printf("%d %15d \t\tTask%d<%d>    \tFinish\t\tTask%d<%d>\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline, currentTask.taskNo, currentTask.deadline);
	//	return;
	//}
		if (previousTask.taskNo != IDLE || currentTask.taskNo != IDLE) {
			printf("%d %15d \t\tTask%d<%d>    \tpreempted\tTask%d<%d>\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline, currentTask.taskNo, currentTask.deadline);
			return;
		}

		if (previousTask.taskNo == IDLE)
		{
			printf("%d %15d \t\tIdle_Task    \tpreempted\tTask%d<%d>\n", coreID, timeTick, currentTask.taskNo, currentTask.deadline);
		}
		if (currentTask.taskNo == IDLE)
		{
			printf("%d %15d \t\tTask%d<%d>    \tpreempted\tIdle_Task\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline);
		}

	
}

void EDF_SchedSimulator(link list, int coreID, int startTime, int endTime)
{

	int scheduleState = INITIAL;
	int timeTick = startTime;

	link taskReadyQueue = list;
	link taskWaittingQueue = NULL;

	node nextTask;
	node previousTask;
	node currentTask = SearchSmallestDeadline(taskReadyQueue);

	//Set Idle Task
	node idleTask;
	idleTask.taskNo = IDLE;
	idleTask.exTime = IDLE;
	idleTask.period = IDLE;
	idleTask.exTimeDef = IDLE;
	idleTask.deadline = IDLE;
	idleTask.utilization = IDLE;

	printf("%s%15s%20s%12s%20s%\n", "CPU_ID", "Time_Tick", "Previous_Task", "State", "Scheduled_Task");

	//Run Schedule
	while (timeTick < endTime)
	{
		// Ready queue null - Task execution done - Change next task
		if (taskReadyQueue == NULL)
		{
			scheduleState = IDLE;
			
			if (currentTask.exTime == 0)
				printf("%d %15d \t\tTask%d<%d>    \tFinish\t\tIdle_Task\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline);
		
			currentTask = idleTask;
			goto TimeTick;
		}

		scheduleState = INITIAL;
		nextTask = SearchSmallestDeadline(taskReadyQueue);

		// Exuction self
		if (currentTask.taskNo == nextTask.taskNo)
			currentTask.exTime--;
		
		// Preemption
		if (currentTask.exTime != 0 && currentTask.taskNo != nextTask.taskNo)
		{
			scheduleState = PREEMPTED;
			previousTask = currentTask;
			currentTask = nextTask;
			currentTask.exTime--;

			if (taskReadyQueue != NULL && currentTask.taskNo != IDLE)
			{
				taskReadyQueue = RemoveTask(currentTask, taskReadyQueue);
				taskReadyQueue = InsertTaskToList(currentTask, taskReadyQueue);
			}

			if (previousTask.taskNo != IDLE && currentTask.taskNo != IDLE) 
				printf("%d %15d \t\tTask%d<%d>    \tpreempted\tTask%d<%d>\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline, currentTask.taskNo, currentTask.deadline);
		
			if (previousTask.taskNo == IDLE)
				printf("%d %15d \t\tIdle_Task    \tpreempted\tTask%d<%d>\n", coreID, timeTick, currentTask.taskNo, currentTask.deadline);
	
			if (currentTask.taskNo == IDLE)
				printf("%d %15d \t\tTask%d<%d>    \tpreempted\tIdle_Task\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline);
	
		}
	
		// Finish
		if (currentTask.exTime == 0 && currentTask.taskNo != nextTask.taskNo)
		{
			previousTask = currentTask;
			currentTask = nextTask;
			currentTask.exTime--;
			printf("%d %15d \t\tTask%d<%d>    \tFinish\t\tTask%d<%d>\n", coreID, timeTick, previousTask.taskNo, previousTask.deadline, currentTask.taskNo, currentTask.deadline);
		
		}

		if (currentTask.exTime == 0)
		{
			scheduleState = FINISH;
			previousTask = currentTask;
			taskReadyQueue = RemoveTask(currentTask, taskReadyQueue);
			taskWaittingQueue = InsertTaskToList(currentTask, taskWaittingQueue);    
		}


	TimeTick:
		timeTick++;

		link startNode = taskWaittingQueue;
		int counter = 0;
		node temp[TASK_NUM];

		for (taskWaittingQueue;;taskWaittingQueue = taskWaittingQueue->front)
		{
			// Waitting queue is null
			if (taskWaittingQueue == NULL)
				break;

			// Deadline on time task in waitting queue -> Insert Temp, Wait insert to ready queue
			if (taskWaittingQueue->deadline == timeTick && taskWaittingQueue != NULL)
			{
				temp[counter] = GetTaskInfo(temp[counter], taskWaittingQueue);
				counter++;
			}

			// Visit end - Remove task from waitting queue and putting in ready queue
			if (taskWaittingQueue->front == startNode)
			{
				for (int i = 0; i < counter; i++) {
					taskWaittingQueue = RemoveTask(temp[i], taskWaittingQueue);

					temp[i].exTime = temp[i].exTimeDef;
					temp[i].deadline = temp[i].deadline + temp[i].period;

					taskReadyQueue = InsertTaskToList(temp[i], taskReadyQueue);
				}
				break;
			}
		}

		// Move Current Task To Tail
		if (scheduleState != FINISH && scheduleState != IDLE && scheduleState != PREEMPTED)
		{
			taskReadyQueue = RemoveTask(currentTask, taskReadyQueue);
			taskReadyQueue = InsertTaskToList(currentTask, taskReadyQueue);
		}
	}
}
