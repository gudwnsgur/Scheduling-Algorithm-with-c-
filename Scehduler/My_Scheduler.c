// Scheduler Algorithm Simulator
#include "My_Scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_sched(sched *S) {	// initialize Process for scheduling
	int i;
	S->total_time = 0;

	printf("Number of Process : ");
	scanf_s("%d", &S->n);			// initialize number of process

	S->Task_name = (int*)malloc(sizeof(int*)*S->n);	// allocation Task_name 
	for (i = 0; i < S->n; i++) S->Task_name[i] = i;
	// initialize Task_name

	S->Task_time = (int**)malloc(sizeof(int*)*S->n);
	for (i = 0; i < S->n; i++)
		S->Task_time[i] = (int*)malloc(sizeof(int) * 2);	// allocation Task_time
	for (i = 0; i < S->n; i++) {
		printf("enter-time and run-time of process %c : ", (char)(S->Task_name[i]+65));
		scanf_s("%d %d", &S->Task_time[i][0], &S->Task_time[i][1]);
		S->total_time += S->Task_time[i][1];	// calculate total_time
	}	// initialize Task_time

	S->Sched_frame = (int**)malloc(sizeof(int*)*S->n);
	for (i = 0; i < S->n; i++)
		S->Sched_frame[i] = (int*)malloc(sizeof(int)*S->total_time);	// allocation Sched_frame

	printf("\n");
}

void InitQueue(Queue *q) {	// initialize Queue
	q->front = q->rear = NULL;
	q->count = 0;
}

int IsEmpty(Queue *q) { // check Queue is empty
	if (q->count != 0) return 1;
	else return 0;	// if queue is empty, isEmpty() will return 0
}

void push(Queue *q, int data) { // put data in queue
	ChainNode* node = (ChainNode*)malloc(sizeof(ChainNode));
	node->data = data;	node->link = NULL;

	if (!q->front)	// if queue is empty
		q->front = q->rear = node;	// node will be front and rear
	else {			// if queue is not empty
		q->rear->link = node;	// connect rear and node
		q->rear = node;			// now node will be rear
	}
	q->count++;
}

int pop(Queue *q) { // delete last node in queue
	if (!IsEmpty(q)) return 0;
	ChainNode* DelNode = q->front;	// DelNode will be deleted
	int Del_data = q->front->data;	// Del_data is data of DelNode
	q->front = q->front->link;	// second node will be front node
	free(DelNode);
	q->count--;
	return Del_data;	// return deleted process name 
}

void Clean_frame(sched *S) {
	for (int i = 0; i < S->n; i++)
		for (int j = 0; j < S->total_time; j++)
			S->Sched_frame[i][j] = 0;	// initialize scheduler frame
}

void FCFS(sched *s) {
	Clean_frame(s);		// clean my frame for FCFS
	printf("\n\t\t FCFS \n\n");
	int x;
	Queue q;
	InitQueue(&q);
	int i, j;

	int* use_t = (int*)malloc(sizeof(int*)*s->n);
	for (i = 0; i < s->n; i++) use_t[i] = s->Task_time[i][1];
	// use_t for task run time

	for (i = 0; i < s->total_time; i++)
	{
		for (j = 0; j < s->n; j++) {
			if (s->Task_time[j][0] == i)	// if process entered
				push(&q, s->Task_name[j]);	// push this process
		}
		s->Sched_frame[q.front->data][i] = 1;	// run
		use_t[q.front->data]--;		
		if (use_t[q.front->data] == 0) pop(&q);	// if process is end, pop this process
	}
	Print(s);
}

void SPN(sched *s) {
	
	Clean_frame(s);		// clean my frame for SPN
	printf("\n\t\t SPN \n\n");
	int i, j;
	int cur_task;	// task that have to run now
	int* use_t = (int*)malloc(sizeof(int*)*s->n);
	int* Q = (int*)malloc(sizeof(int*)*s->n + 1);
	for (i = 0; i < s->n; i++) {
		use_t[i] = s->Task_time[i][1];			// use_t : task run time
		Q[i] = 0;		// check what process is in Q 
	} Q[s->n] = 0;	/* Q[i] == 0 : process i is not entered yet 
					   Q[i] == 1 : process i is in Q 					
					   Q[i] == -1 : process i is end 
					   Q[n] : count process in Q
					*/
	for (i = 0; i < s->total_time; i++)	{
		for (j = 0; j < s->n; j++) {
			if (s->Task_time[j][0] == i) {
				Q[j]++; Q[s->n]++;
				if (Q[s->n] == 1) cur_task = s->Task_name[j];
			}	// if process entered, push process X in Q[X]
		}
		s->Sched_frame[cur_task][i] = 1;	// run
		use_t[cur_task]--;

		if (use_t[cur_task] == 0) {		// if current task is end
			Q[cur_task] = -1;	Q[s->n]--;	// delete this task at Q
			if (Q[s->n] == 0) break;
			int tmp = 9999;
			for (j = 0; j < s->n; j++) {
				if (Q[j] == 1 && tmp > use_t[j]) {
					tmp = use_t[j];	 cur_task = j;
				}
			}	// find next task to run
		}
	}
	Print(s);
}

void RR(sched *s) {
	printf("\t\t RR \n\n");
}
void HRRN(sched *s) {

	printf("\t\t HRRN \n\n");
}
void FeedBack(sched *s, int t) {
	printf("\t\t FeedBack of time %d \n\n", t);
}
void RM(sched *s) {
	printf("\t\t RM \n\n");
}
void Lottery(sched *s) {
	printf("\t\t Lottery \n\n");

	printf("end\n");
}

void Print(sched *s) {
	int i, j;
	for (i = 0; i < s->n; i++) {
		printf("%c : ", (char)(s->Task_name[i]+65));
		for (j = 0; j < s->total_time; j++) {
			if (s->Sched_frame[i][j] == 1) printf(" бс ");
			else printf(" бр ");
		}
		printf("\n");
	}		// print Scheduled process
}