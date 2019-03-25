#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_SIZE    1024
#define QUEUE_NAME  "/test_queue"

#define READER      0
#define WRITER      1

#define NUM_THREADS 2

void *readQueue(void *args)
{
    (void) printf("Thread READER starting...\n");

    mqd_t          mq               = {0};
    struct mq_attr attr             = {0};
    char           buffer[MAX_SIZE] = {0};
    ssize_t        bytes_read       = 0;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_EXCL, 0700, &attr); // Be careful with the flags - mq_open could fail, because of the creation!

    /* check if the queue open is succesful */
    if (mq > -1)
    {
         /* receive the message */
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        
        if (bytes_read >= 0)
        {
            buffer[bytes_read] = '\0';
            (void) printf("Received: %s\n", buffer);
        }
    }
    else
    {
        (void) printf("Failed to load queue!");
    }

    pthread_exit(NULL);
}

void *writeToQueue(void *args)
{
    (void) printf("Thread WRITER starting...\n");

    mqd_t mq               = {0};
    char  buffer[MAX_SIZE] = "Testing queue"; // This could be taken from stdin

    /* open the queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY | O_EXCL, 0700, NULL);

    /* check if the queue open is succesful */
    if (mq > -1)
    {
        /* presume, that the send is successful */
        (void) mq_send(mq, buffer, MAX_SIZE, 0);
    }
    else
    {
        (void) printf("Failed to load queue!");
    }

    pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
    pthread_t      thread[NUM_THREADS] = {0};
    pthread_attr_t attr                = {0};
    int            result              = 0;
    int            thr_count           = 0;
    void           *status             = NULL;

    /* initialize attributes */
    (void) pthread_attr_init(&attr);

    result = pthread_create(&thread[READER], &attr, readQueue, NULL);
    if (0 != result)
    {
        (void) printf("ERROR; return code from pthread_create() is %d\n", result);
    }

    result = pthread_create(&thread[WRITER], &attr, writeToQueue, NULL);
    if (0 != result)
    {
        (void) printf("ERROR; return code from pthread_create() is %d\n", result);
    }

    /* free attribute and wait for the other threads */
    (void) pthread_attr_destroy(&attr);

    result = pthread_join(thread[READER], &status);
    if (0!= result) 
    {
        (void) printf("ERROR; return code from pthread_join() is %d\n", result);
    }

    result = pthread_join(thread[WRITER], &status);
    if (0!= result) 
    {
        (void) printf("ERROR; return code from pthread_join() is %d\n", result);
    }

    (void) printf("Main: program completed. Exiting.\n");

    pthread_exit(NULL);

    return 0;
}