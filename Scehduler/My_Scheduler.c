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

	S->Task_name = (char*)malloc(sizeof(char*)*S->n);	// allocation Task_name 
	for (i = 0; i < S->n; i++) S->Task_name[i] = (char)(i + 65);
	// initialize Task_name

	S->Task_time = (int**)malloc(sizeof(int*)*S->n);
	for (i = 0; i < S->n; i++)
		S->Task_time[i] = (int*)malloc(sizeof(int) * 2);	// allocation Task_time
	for (i = 0; i < S->n; i++) {
		printf("enter-time and run-time of process %c : ", S->Task_name[i]);
		scanf_s("%d %d", &S->Task_time[i][0], &S->Task_time[i][1]);
		S->total_time += S->Task_time[i][1];	// calculate total_time
	}	// initialize Task_time

	S->Sched_frame = (char**)malloc(sizeof(char*)*S->n);
	for (i = 0; i < S->n; i++)
		S->Sched_frame[i] = (char*)malloc(sizeof(char)*S->total_time);	// allocation Sched_frame

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

void push(Queue *q, char data)	{ // put data in queue
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

char pop(Queue *q)	{ // delete last node in queue
	if (!IsEmpty(q)) return NULL;
	ChainNode* DelNode = q->front;	// DelNode will be deleted
	char Del_data = q->front->data;	// Del_data is data of DelNode
	q->front = q->front->link;	// second node will be front node
	free(DelNode);		
	q->count--;
	return &Del_data;	// return deleted process name 
}
void Clean_frame(sched *S) {
	for (int i = 0; i < S->n; i++)
		for (int j = 0; j < S->total_time; j++)
			S->Sched_frame[i][j] = 'x';	// initialize scheduler frame
}

void FCFS(sched *s) {	
	Clean_frame(s);		// clean my frame for FCFS
	printf("\t\t FCFS \n\n");
	char c;
	Queue q;
	InitQueue(&q);		
	int i, j;

	int* use_t = (int*)malloc(sizeof(int*)*s->n);
	for (i = 0; i < s->n; i++) use_t[i] = s->Task_time[i][1];
	// use_t for task run time

	for (i = 0; i < s->total_time; i++)
	{
		for (j = 0; j < s->n; j++)	{
			if (s->Task_time[j][0] == i) {
				push(&q, s->Task_name[j]);
			}
		}
		s->Sched_frame[(int)(q.front->data - 65)][i] = 'o';
		use_t[(int)(q.front->data - 65)]--;
		if (use_t[(int)(q.front->data - 65)] == 0) pop(&q);
	}
	
	for (i = 0; i < s->n; i++) {
		printf("%c : ", s->Task_name[i]);
		for (j = 0; j < s->total_time; j++) {
			if(s->Sched_frame[i][j] == 'o') printf(" ■ ");
			else printf(" □ ");
		}
		printf("\n");
	}		// print process scheduled by FCFS
}
void RR(sched *s) {
	printf("\t\t RR \n\n");
}
void SPN(sched *s) {
	printf("\t\t SPN \n\n");
}
void HRRN(sched *s) {
	printf("\t\t HRRN \n\n");
}
void FeedBack(sched *s,int t) {
	printf("\t\t FeedBack of time %d \n\n",t);
}
void RM(sched *s) {
	printf("\t\t RM \n\n");
}
void Lottery(sched *s) {
	printf("\t\t Lottery \n\n");
	
	printf("end\n");
}

/*
   Queue queue;

	InitQueue(&queue);//큐 초기화
	for (i = 1; i <= 5; i++)//1~5까지 큐에 보관
	{
		Enqueue(&queue, i);
	}
	while (!IsEmpty(&queue))//큐가 비어있지 않다면 반복
	{
		printf("%d ", Dequeue(&queue));//큐에서 꺼내온 값 출력
	}
*/