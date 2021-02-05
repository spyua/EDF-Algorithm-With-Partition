#ifndef _TASK_H_

#define _TASK_H_

#define MAX_DEADLINE_SET 9999

//Task Set    
#define TASK_NUM 9    
#define CORE_NUM 3

//Task State
#define INITIAL 1000    
#define FINISH 20
#define PREEMPTED 30
#define IDLE 40

struct Task {
    struct Task* back;
    struct Task* front;

    int taskNo;         //ID
    int period;         //Period
    int exTime;   //Remaining Execution Time
    int exTimeDef;      //Execution Time Definition
    int deadline;       //Deadline 
    double utilization;
};
typedef struct Task node;
typedef node* link;

extern link RemoveHeadTask(link firstnode);
extern link RemoveTask(node temp, link list);
extern link InsertTaskToList(node item, link firstnode);
extern node GetTaskInfo(node get, link list);

extern void ClearCoreInfo(node Core[]);
extern void ClearTaskInfo(node node[]);
extern void DisplayTaskList(link node);
extern void LoadTaskInfo(link list, node item);

#endif