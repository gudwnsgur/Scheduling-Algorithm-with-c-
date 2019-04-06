#pragma once
typedef struct sched {
	int n;				// number of process
	int total_time;		// total time of tasks
	int* Task_name;	// name of process
	int** Task_time;	// enter-time and run-time of process
	int** Sched_frame;	// frame of scheduler
	int* use_t; // each process's run-time for using
	int* Q;		
} sched;		// include my variables for scheduling

typedef struct ChainNode {
	int data;
	struct ChainNode* link;
}ChainNode;

typedef struct Queue {
	ChainNode* front;
	ChainNode* rear;
	int count;	
} Queue;			// struct for using queue

void init_sched(sched *S);	// initialize sched

void InitQueue(Queue *q);	// initialize Queue
int IsEmpty(Queue *q); // check Queue is empty
void push(Queue *q, int data); // put data in queue
int pop(Queue *q); // delete last node in queue

void FIFO(sched *S);
void SJF(sched *S);
void SRT(sched *S);
void RR(sched *S);
void FeedBack(sched *S, int q);
void Lottery(sched *S);

void Clean_frame(sched *S);
void Print(sched *S);