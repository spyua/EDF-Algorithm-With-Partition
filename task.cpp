#include <stdio.h>
#include <stdlib.h>
#include "task.h"

link RemoveHeadTask(link taskList)
{
    link tempList;
    tempList = taskList;

    if (taskList == NULL) {
        printf("[ERROR] RemoveHeadTask Fail - Node is Null\n ");
        return NULL;
    }  
    if (taskList->front == taskList)
    {
        // Only One Node - Remove Self
        free(taskList);
        taskList = NULL;
        return taskList;
    }
    // Release Head Node
    tempList->back->front = tempList->front;
    tempList->front->back = tempList->back;
    if (tempList == taskList)
    {
        taskList = taskList->front;
    }
    free(tempList);
    return taskList;
}

link RemoveTask(node deleteTask, link taskList)
{
    if (taskList == NULL) {
        printf("[ERROR] RemoveTask - Node is Null\n ");
        return NULL;
    }

    link tempList = taskList;
    bool findTask = false;

    // Get Node
    for (tempList ;;tempList = tempList->front)
        if (tempList->taskNo == deleteTask.taskNo)
        {
            findTask = true;
            break;
        }

    if (!findTask) {
        printf("[ERROR] RemoveTask Fail - Node is not found\n ");
        return NULL;
    }

    if (taskList->front != taskList)
    {
        tempList->back->front = tempList->front;
        tempList->front->back = tempList->back;
        if (tempList == taskList)
        {
            taskList = taskList->front;
        }
        free(tempList);
        return taskList;
    }

    free(taskList);
    taskList = NULL;
    return taskList;
     
}

link InsertTaskToList(node newNode, link taskList)
{

    // Null List - Point Self
    if (taskList == NULL)
    {
        taskList = (Task*)malloc(sizeof(Task));
        LoadTaskInfo(taskList, newNode);
        taskList->back = taskList;
        taskList->front = taskList;
        return taskList;
    }
    
    link tempNode;
    tempNode = (Task*)malloc(sizeof(Task));
    LoadTaskInfo(tempNode, newNode);
    
    tempNode->front = taskList;
    tempNode->back = taskList->back;
    taskList->back->front = tempNode;
    
    taskList->back = tempNode;
    return taskList;
}

node GetTaskInfo(node taskInfo, link taskList)
{
    taskInfo.taskNo = taskList->taskNo;
    taskInfo.period = taskList->period;
    taskInfo.exTime = taskList->exTime;
    taskInfo.exTimeDef = taskList->exTimeDef;
    taskInfo.deadline = taskList->deadline;
    taskInfo.utilization = taskList->utilization;
    return taskInfo;
}

void DisplayTaskList(link list)
{
    if (list == NULL) {
        printf("[INFO] DisplayList - Node is Null\n ");
        return;
    }
        
    link originalList = list;

    printf("%10s%15s%15s%15s  %15s\n", "", "Exec-time", "Period", "Deadline", "Utilization");
    for (list;; list = list->front)
    {
        printf("%-10d%15d%15d%15d  %15lf\n", 
            list->taskNo,
            list->exTime,
            list->period,
            list->deadline,
            list->utilization);
        // Visit Done
        if (list->front == originalList)
            break;
    }
    printf("===============================================================================\n");
}

void LoadTaskInfo(link list, node item)
{
    list->period = item.period;           //priod
    list->exTime = item.exTime;     //execution time
    list->taskNo = item.taskNo;           //task number
    list->utilization = item.utilization; //itiltization
    list->exTimeDef = item.exTimeDef;
    list->deadline = item.deadline;
}

void InitialCoreInfo(node Core[])
{
    for (int i = 0; i < CORE_NUM; i++)
    {
        Core[i].utilization = 1.0;
        Core[i].back = NULL;
        Core[i].front = NULL;
    }
}

void InitialTaskInfo(node node[])
{
    for (int i = 0; i < TASK_NUM; i++)
    {
        node[i].taskNo = 0;
        node[i].period = 0;
        node[i].exTime = 0;
        node[i].exTimeDef = 0;
        node[i].deadline = 0;
        node[i].utilization = 0;
        node[i].back = NULL;
        node[i].front = NULL;
    }
}