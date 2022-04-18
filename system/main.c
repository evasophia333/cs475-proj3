/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks

//locks are declared and initialized here

//define the array of all right forks

//define the array of all left forks 
mutex_t allForks[N];
mutex_t rightFork;
mutex_t leftFork;
mutex_t printing = FALSE;



/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{
	uint32 right = phil_id;
    rightFork = allForks[right];			//right fork
    uint32 left = N-1;
    if(phil_id ==0){
        uint32 left = N-1;	//TODO - left fork
    }else{
        uint32 left = phil_id-1;	//TODO - left fork
    }
    leftFork = allForks[left];
	
    srand(phil_id);

	while (TRUE)
	{        
        if((rand() %10+1)>3){
            //THINK
            mutex_lock(&printing);
            kprintf("Philosopher %d thinking: zzzzzZZZz\n", phil_id);
            mutex_unlock(&printing);
            think();
        }else{
            if(rightFork==FALSE && leftFork==FALSE){
            //did you obtain both forks?? 
            //yes, then eat  for random amount of time 
            mutex_lock(&leftFork);
            mutex_lock(&rightFork);
            //also lock pringint statment
            mutex_lock(&printing);
            kprintf("Philosopher %d eating: nom nom nom\n", phil_id);
            //release forks
            mutex_unlock(&printing);

            //EAT
            eat();
            mutex_unlock(&leftFork);
            mutex_unlock(&rightFork);
            }
            //no just release any forks
        }
	}
}

int	main(uint32 argc, uint32 *argv)
{
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	return 0;
}
