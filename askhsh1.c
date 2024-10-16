#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>

int sem_id;

void display(const char *message) {
    struct sembuf sem_op;

    sem_op.sem_num = 0;
    sem_op.sem_op = -1; 
    sem_op.sem_flg = 0;

    if (semop(sem_id, &sem_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    printf("%s", message);
    fflush(stdout);

    sem_op.sem_op = 1; 
    if (semop(sem_id, &sem_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    
    if ((sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    
    if (semctl(sem_id, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    pid_t pid;

    pid = fork();

    if (pid > 0) {
        display("Good morning ");
        display("a nice day\n\n");

        
        if (semctl(sem_id, 0, IPC_RMID) == -1) {
            perror("semctl");
            exit(EXIT_FAILURE);
        }

        wait(NULL);
    } else if (pid == 0) {
        display("sir\n");
        display("I wish you, ");
    } else {
        printf("Fork error.\n");
    }

    exit(0);
}


