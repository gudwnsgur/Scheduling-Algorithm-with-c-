#pragma once
typedef struct sched {
	int n;				// number of process
	int total_time;		// total time of tasks
	char* Task_name;	// name of process
	int** Task_time;	// enter-time and run-time of process
	char** Sched_frame;	// frame of scheduler
}sched;		// include my variables for scheduling

typedef struct ChainNode {
	char data;
	struct ChainNode* link;
}ChainNode;

typedef struct Queue {
	ChainNode* front;
	ChainNode* rear;
	int count;
}Queue;			// struct for using queue

void init_sched(sched *S);	// initialize sched

void InitQueue(Queue *q);	// initialize Queue
int IsEmpty(Queue *q); // check Queue is empty
void push(Queue *q, char data); // put data in queue
char pop(Queue *q); // delete last node in queue

void FCFS(sched *S);
void RR(sched *S);
void SPN(sched *S);
void HRRN(sched *S);
void FeedBack(sched *S, int t);
void RM(sched *S);
void Lottery(sched *S);

void Clean_frame(sched *S);