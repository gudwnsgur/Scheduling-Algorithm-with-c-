#include "My_Scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	sched My_S;
	init_sched(&My_S);

	FIFO(&My_S);
	SJF(&My_S);
	SRT(&My_S);
	RR(&My_S, 2);
	Lottery(&My_S);
	FeedBack(&My_S, 2);
	FeedBack(&My_S, 4);
	FeedBack(&My_S, 8);
	
	return 0;
}