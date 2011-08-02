/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*	Joseph Randell L. Benavidez                                                 *
*	chai356@yahoo.com                                                           *
*	CMSC 125 UV-2L                                                              *
*	February 21, 2004                                                           *
*                                                                             *
*	This program simulates Shortest Job First scheduling algorithm.             *
*                                                                             *
*	The program is divided into four major parts: input processing, queuing,    *
*	dispatching and simulating the CPU.                                         *
*                                                                             *
*	First, inputs must be saved in a linked list, which includes the time       *
*	representation for each process, the number of which is also specified      *
*	by user input.  Each process is sorted in increasing order everytime it     *
*	is given a value.  After all the processes are given their corresponding    *
*	value,  all of them are dispatched one by one consuming the time equal to   *
*	their value.                                                                *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int flag = 0;

typedef struct node {
	int process_time;
	int waiting_time;
	int process_id;
	struct node *next;
	struct node *last;
} nodetype;

typedef struct node *LIST;
typedef struct node *position;

void makeNull(LIST *L) {
	*L = (nodetype *)malloc(sizeof(nodetype));
	(*L)->next = NULL;
	(*L)->last = *L;
}

position insPos(int p_time, LIST L) {
	position p;
	p = L;
	while (p->next != NULL) {
		if (p_time < p->next->process_time)
			return(p);
		else
			p = p->next;
	}
	return(p);
}

void insert(int p_time, int w_time, int p_id, position p) {
	position temp;

	temp = p->next;
	p->next = (nodetype *)malloc(sizeof(nodetype));
	p->next->process_time = p_time;
	p->next->waiting_time = w_time;
	p->next->process_id = p_id + 1;
	p->next->next = temp;
	if (temp == NULL) {
		p->last = p->next->next;
	}
}

void dispatch(position p) {
	position temp, temp2;
	int i=0;

	printf("\nDispatching processes. Please wait.\n\n");
	while (p->next != NULL) {
		while (p->next->process_time > 0) {
			if (i == p->next->next->waiting_time) {
				temp = p->next;
				p->next = p->next->next;
				i=0;
			}
			else if (i != p->next->next->waiting_time) {
				sleep(1);
				printf("Dispatching %i\n", p->next->process_id);
				(p->next->process_time)--;
			}
			i++;
		}
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
}

main () {
	LIST L, p;
	int num_process,
			process_time,
			waiting_time,
			i;
	char ans;

	makeNull(&L);


	do {
		clrscr();

		printf("\n+----------- MENU -----------+\n");
		printf("| [1] Try the SJF algorithm |\n");
		printf("| [2] Quit                   |\n");
		printf("+----------------------------+\n");
		printf("Enter chosen number: ");
		ans = toupper(getche());


		switch (ans) {
			case '1':
								clrscr();
								printf("\nEnter number of process to be created: ");
								scanf("%i", &num_process);
								printf("\n");

								printf("Enter process time and waiting time for each process\n\n");
								for (i = 0; i < num_process; i++) {
									printf("Process Time %i: ", i+1);
									scanf("%i", &process_time);
									printf("Waiting Time %i: ", i+1);
									scanf("%i", &waiting_time);
									p = insPos(process_time, L);
									insert(process_time, waiting_time, i, p);
								}

								dispatch(L);

								printf("\nPress any key to continue...");
								getch();
								break;
			case '2':	break;
		}
	} while (ans != '2');
}