#ifndef _PARTITION_H_

#define _PARTITION_H_

void FirstFit(node Task[], node Core[], link Clist[]);
void BestFit(node Task[], node Core[], link Clist[]);
void WorstFit(node Task[], node Core[], link Clist[]);

#endif