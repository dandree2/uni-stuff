#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

#define BUF_SIZE 50

void *consumer(void *params);
void *producer(void *params);

char  buffer[BUF_SIZE];
char  full_flag = 0;
char  thr_exit  = 0;
sem_t sem;

int main()
{
    pthread_t tid_prod;
    pthread_t tid_cons;

    if (sem_init(&sem, 0, 1))
    {
        perror("sem_init_failed!");
    }
    else
    {
        pthread_create(&tid_prod, NULL, producer, NULL);
        pthread_create(&tid_cons, NULL, consumer, NULL);

        pthread_join(tid_prod, NULL);
        pthread_join(tid_cons, NULL);

        sem_destroy(&sem);
        pthread_exit(NULL);
    }

    return 0;
}

void *consumer(void *params)
{
    while (!thr_exit)
    {
        sem_wait(&sem); // P(S)

        if (1 == full_flag)
        {
            // Print to the terminal (1 is the FS of the output to terminal).
            (void) write(1, buffer, sizeof(buffer));
            full_flag = 0;
        }

        sem_post(&sem); // V(S)
        sched_yield(); // usleep(10)
    }

    sem_post(&sem);
    pthread_exit(0);
}

void *producer(void *params)
{
    while (1)
    {
        sem_wait(&sem); // P(S)

        if (0 == full_flag)
        {
            // Receive from the terminal (0 is the FS of the input from terminal).
            (void) read(0, buffer, sizeof(buffer) > 0);

            if(feof(stdin))
            {
                thr_exit = 1;
                sem_post(&sem); // V(S)

                pthread_exit(0);
            }

            full_flag = 1;
        }

        sem_post(&sem); // V(S)
        sched_yield(); // usleep(10)
    }
}