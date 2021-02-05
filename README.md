# Simple EDF Schedule Algorithm Simulator
Earliest Deadline First Scheduling algorithm simulation on multi core environment.

## Partition Method
 - First Fit Allocation : This method keeps the list of tasks organized by core location,low-ordered to high-ordered core id. 
 - Best Fit Allcation : This method keeps the task list in order by core utilition – smallest to largest.
 - Worst Fit Allocation :　This method keeps the task list in order by core utilition –  largest　to smallest.
 
## Earliest deadline first scheduling
 An optimal dynamic priority scheduling algorithm used in real-time systems. It can be used for both static and dynamic real-time scheduling.Whenever a scheduling event occurs (task finishes, new task released, etc.) the queue will be searched for the process closest to its deadline. This process is the next to be scheduled for execution.
 
## Usage

 - Set TaskSet Data
```
void InitialTask(Task item[])
```

 - Set Max Core Num on task.h
```
#define CORE_NUM 3
```

 - Set Max Task Num on task.h
 
```
#define TASK_NUM 9    
```
 - Select Partition Method (
You can only choose one at a time)
 
 ```
	//BestFit(TaskSet, CoreSet, CoreList);
	FirstFit(_taskSet, _coreSet, _coreList);
	//WorstFit(TaskSet, CoreSet, CoreList); 
```
 - GCC Compiler
 ```
g++ main.cpp task.cpp schedule.cpp partition.cpp -o Execution
```

- Execution

 ```
 ./Execution
```

## Console Result

![image](https://user-images.githubusercontent.com/20264622/107001541-c61d6c00-67c4-11eb-85f6-4ac83a5530da.png)

![image](https://user-images.githubusercontent.com/20264622/107001512-b7cf5000-67c4-11eb-9983-0a34bcac93f6.png)

![image](https://user-images.githubusercontent.com/20264622/107001591-d897a580-67c4-11eb-9377-2016d073d254.png)

![image](https://user-images.githubusercontent.com/20264622/107001617-e6e5c180-67c4-11eb-98e5-21d334762e2c.png)
 




