#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>


//set up POSIX semaphore
sem_t sem;



int main (int argc, char **argv)
{
    int sem_init(&sem, 0, 1);
    int sem_wait(&sem);
    int sem_post(&sem);
    pid_t pid;
    /* fork child processes */
    pid = fork ();
    if (pid > 0)
    {
        display ("Good morning ");
        sem_wait(&sem);
        display ("a nice day\n\n");
        
    }
    else if (pid == 0)
    {
        display ("sir\n");
        sem_post(&sem);
        display ("I wish you, ");
    }
    else /* fork failed */
    {
        printf ("Fork error.\n");
    }
    exit (0);
}