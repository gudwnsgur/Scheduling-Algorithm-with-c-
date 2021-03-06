// Scheduler Algorithm Simulator
#include "My_Scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

	S->use_t = (int*)malloc(sizeof(int*)*S->n);
	S->Q = (int*)malloc(sizeof(int*)*S->n + 1);
	for (i = 0; i < S->n; i++) {
		S->use_t[i] = S->Task_time[i][1];			// use_t : task run time
		S->Q[i] = 0;		// check what process is in Q 
	} S->Q[S->n] = 0;	/* Q[i] == 0 : process i is not entered yet
					   Q[i] == 1 : process i is in Q
					   Q[i] == -1 : process i is end
					   Q[n] : count process in Q
					*/
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

void Clean_frame(sched *S)	// clean frame, use_t, Q for each Scheduler
{
	int i, j;
	for (i = 0; i < S->n; i++)
		for (j = 0; j < S->total_time; j++)
			S->Sched_frame[i][j] = 0;	// initialize scheduler frame

	for (i = 0; i < S->n; i++) {
		S->use_t[i] = S->Task_time[i][1];			// use_t : task run time
		S->Q[i] = 0;		// check what process is in Q 
	} S->Q[S->n] = 0;	/*	  Q[i] == 0 : process i is not in Q
							  Q[i] == 1 : process i is in Q
							  Q[n] : count process in Q			*/
}

void FIFO(sched *s)	{
	Clean_frame(s);		// clean my frame, use_t, Q for FIFO(First In First Out)
	printf("\n\t\t FIFO \n\n");
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

void SJF(sched *s)
{	
	Clean_frame(s);		// clean my frame, use_t, Q for SJF (Shortest Job First)
	printf("\n\t\t SJF \n\n");
	int i, j;
	int cur_task;	// task that have to run now

	for (i = 0; i < s->total_time; i++)	{
		for (j = 0; j < s->n; j++) {
			if (s->Task_time[j][0] == i) {
				s->Q[j]++; s->Q[s->n]++;
				if (s->Q[s->n] == 1) cur_task = s->Task_name[j];
			}	// if process entered, push process X in Q[X]
		}
		s->Sched_frame[cur_task][i] = 1;	// run
		s->use_t[cur_task]--;

		if (s->use_t[cur_task] == 0) {		// if current task is end
			s->Q[cur_task]--;	s->Q[s->n]--;	// delete this task at Q
			if (s->Q[s->n] == 0) break;
			int tmp = 9999;
			for (j = 0; j < s->n; j++) {
				if (s->Q[j] == 1 && tmp > s->use_t[j]) {
					tmp = s->use_t[j];	 cur_task = j;
				}
			}	// find next task to run
		}
	}
	Print(s);
}

void SRT(sched *s) {
	Clean_frame(s);		// clean my frame, use_t, Q for SRT(Shortest Remaining-Time Next)
	printf("\n\t\t SRT \n\n");
	int i, j, cur_task;

	for (i = 0; i < s->total_time; i++)
	{
		for (j = 0; j < s->n; j++) {
			if (s->Task_time[j][0] == i) {	// if process j is entered
				s->Q[j]++; s->Q[s->n]++;	// check Q[j] 
				if (s->Q[s->n] == 1) cur_task = j;	// only one process is in Q
				else {							// if process in Q are more than two
					int min = 9999;			
					for (int k = (s->n) - 1; k >= 0; k--) {		
						if (s->Q[k] == 1 && min >= s->use_t[k]) {
							min = s->use_t[k];
							cur_task = k;		// shortest run-time of process will be cur_task 
		}	}	}	}	}

		s->Sched_frame[cur_task][i] = 1;	// run
		s->use_t[cur_task]--;

		if (s->use_t[cur_task] == 0) {		// if current task is end
			s->Q[cur_task]--;	s->Q[s->n]--;	// delete this task at Q
			if (s->Q[s->n] == 0) break;
			int tmp = 9999;
			for (j = 0; j < s->n; j++) {
				if (s->Q[j] == 1 && tmp > s->use_t[j]) {
					tmp = s->use_t[j];	 cur_task = j;
				}
			}	// find next task to run
		}
	}
	Print(s);
}

void RR(sched *s, int t)
{	
	Clean_frame(s);		// clean my frame for RR (Round-robin)
	printf("\n\t\t RR (Time Quantum : %d) \n\n", t);
	Queue ready_q, exc_q;
	InitQueue(&ready_q);
	InitQueue(&exc_q);
	int i, j;
	int* use_Q = (int*)malloc(sizeof(int*)*s->n);
	for (i = 0; i < s->n; i++) use_Q[i] = t;	// initialize use_Q 

	for (i = 0; i < s->total_time; i++)
	{
		for (j = 0; j < s->n; j++)
			if (s->Task_time[j][0] == i)
				push(&exc_q, s->Task_name[j]);	// if process in entered, push in exc_q

		if (ready_q.count == 1) 
			push(&exc_q, pop(&ready_q));	// if waiting process is exist, push in exc_q 
		
		s->Sched_frame[exc_q.front->data][i] = 1;	// run
		s->use_t[exc_q.front->data]--;
		use_Q[exc_q.front->data]--;

		if (s->use_t[exc_q.front->data] == 0) pop(&exc_q);	// if process is end, pop this process
		else {
			if (use_Q[exc_q.front->data] == 0) {	// if time quantum is end
				push(&ready_q, pop(&exc_q));		// pop this process and push to ready_q
				use_Q[ready_q.front->data] = t;		// reallocate time quantum
			}
		}
	}
	Print(s);
}


void Lottery(sched *s) {
	Clean_frame(s);		// clean ym frame, use_t, Q for Lottery
	printf("\n\t\t Lottery \n\n");
	int i, j, k, cur_task;
	srand(time(NULL));		// random number for each time

	int* ran_arr = (int*)malloc(sizeof(int)*s->total_time);	
	printf("     ");
	for (i = 0; i < s->total_time; i++) {
		ran_arr[i] = rand() % 100;	// initialize random array to 0~99
		printf("%d  ",ran_arr[i] );
	}
	printf("\n");
	double* Ticket = (double*)malloc(sizeof(double)*s->n);
	for (k = 0; k < s->n; k++)	Ticket[k] = 0;		// Ticket[] for allocate ticket

	for (i = 0; i < s->total_time; i++)	{
		double total_T=0;		// total current run-time for Ticketing
		for (j = 0; j < s->n; j++) {
			if (s->Task_time[j][0] == i) {	// if process j is entered
				s->Q[j]++; s->Q[s->n]++;
				for (k = 0; k < s->n; k++)	Ticket[k] = 0;

				for (k = 0; k < s->n; k++) 
					total_T += (double)( s->use_t[k] * s->Q[k] );	
					// total_T is total run-time of current process
				
				double x = 0;
				for (k = 0; k < s->n; k++) {
					if(s->Q[k] != 0 ){
						Ticket[k] =  x + (double)( (s->use_t[k] * s->Q[k] * 100) / total_T );
						x = Ticket[k];		// Ticketing accumulatively
					}
				}
			}
		}
		for (j = 0; j < s->n; j++) {
			if (ran_arr[i] < Ticket[j] || Ticket[j] == 100) {
				cur_task = j;
				break;
			}		// choose task which want to run now
		}
		s->Sched_frame[cur_task][i] = 1;	// run
		s->use_t[cur_task]--;

		if (s->use_t[cur_task] == 0) {		//
			s->Q[cur_task]--;	s->Q[s->n]--;	// delete this task at Q
			if (s->Q[s->n] == 0) break;
		
			total_T = 0;
			for (k = 0; k < s->n; k++)	Ticket[k] = 0;
			for (k = 0; k < s->n; k++)
				total_T += (double)(s->use_t[k] * s->Q[k]);

			int x = 0;
			for (k = 0; k < s->n; k++) {
				if (s->Q[k] != 0) {
					Ticket[k] = x + (double)((s->use_t[k] * s->Q[k] * 100) / total_T);
					x += Ticket[k];
				}
			}
		}	// if current task is end, Reticketing to choose next task without current task

	}
	Print(s);
}

void FeedBack(sched *s, int q) {
	Clean_frame(s);		// clean frame for MLFQ (Multi-Level Feedback Queue)
	printf("\n\t\t FeedBack of time %d (q1 : 1, q2 : %d, q3 : %d) \n\n",q, q/2 , q);
	Queue My_q[3];
	int x[2] = { -1,0 };	// x[0] = waiting process , x[1] = priority of this process
	InitQueue(&My_q[0]);	InitQueue(&My_q[1]); InitQueue(&My_q[2]);
	int i, j;

	int* use_Q = (int*)malloc(sizeof(int*)*s->n);
	for (i = 0; i < s->n; i++) use_Q[i] = q/2;		

	for (i = 0; i < s->total_time; i++)
	{
		for (j = 0; j < s->n; j++)
			if (s->Task_time[j][0] == i) { push(&My_q[0], j); }	// if process j is entered

		if (x[0] != -1)	push(&My_q[x[1]], x[0]);	// waiting process is exist

		if (My_q[0].count != 0) {	// if priority 1 queue have process
			s->Sched_frame[My_q[0].front->data][i] = 1;	// run
			s->use_t[My_q[0].front->data]--;

			if (s->use_t[My_q[0].front->data] == 0) { x[0] = -1;  pop(&My_q[0]); }
			else 	x[0] = pop(&My_q[0]);	// check process is end

			if (My_q[0].count == 0 && My_q[1].count == 0 && My_q[2].count == 0)	x[1] = 0;
			else x[1] = 1;		// check process is exist in all queue
		}
		else if (My_q[1].count != 0) {	// if priority 2 queue have process
			s->Sched_frame[My_q[1].front->data][i] = 1;	// run
			s->use_t[My_q[1].front->data]--;
			use_Q[My_q[1].front->data]--;

			if (s->use_t[My_q[1].front->data] == 0) { x[0] = -1;  pop(&My_q[1]); }	// if current task is end
			else {	// if crrent task is not end
				if (use_Q[My_q[1].front->data] == 0) {	// current task already use q/2 in My_q[1] 
					x[0] = pop(&My_q[1]);
					x[1] = 2;
					use_Q[x[0]] = q;
				}
				else x[0] = -1;	// current task has not use q/2 yet
			}

		}
		else if (My_q[2].count != 0) {	// if priority 2 queue have process
			s->Sched_frame[My_q[2].front->data][i] = 1;	// run
			s->use_t[My_q[2].front->data]--;
			use_Q[My_q[2].front->data]--;

			if (s->use_t[My_q[2].front->data] == 0) { x[0] = -1;  pop(&My_q[2]); }	// if current task is end
			else {
				if (use_Q[My_q[2].front->data] == 0) 	// current task already use q in My_q[2] 
					push(&My_q[2], pop(&My_q[2]));
			}
		}

	}
	Print(s);
}

void Print(sched *s) {
	int i, j;
	for (i = 0; i < s->n; i++) {
		printf("%c : ", (char)(s->Task_name[i]+65));
		for (j = 0; j < s->total_time; j++) {
			if (s->Sched_frame[i][j] == 1) printf(" �� ");
			else printf(" �� ");
		}
		printf("\n");
	}		// print Scheduled process
}