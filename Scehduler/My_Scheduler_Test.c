#include "My_Scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	sched My_S;
	init_sched(&My_S);

	FCFS(&My_S);
	SPN(&My_S);
	RR(&My_S);
	HRRN(&My_S);
	FeedBack(&My_S, 1);
	FeedBack(&My_S, 4);
	RM(&My_S);
	Lottery(&My_S);

	return 0;
}