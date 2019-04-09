#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<sys/time.h>

#define TIMEOUT 5

void HandlerTimeout(int sig) 
{
	time_t timer = {0};
	(void) time(&timer);
	printf("%s\n", ctime(&timer));
}

int main()
{
	struct sigaction act = {0};
	(void) sigemptyset(&act.sa_mask);
	act.sa_handler = HandlerTimeout;
	act.sa_flags = SA_RESTART;

	if(sigaction(SIGALRM, &act, 0) == -1)
	{
		perror("sigaction");
		return(1);
	}

	struct itimerval val = {0};
	val.it_interval.tv_sec = TIMEOUT;
	val.it_interval.tv_usec = 0;
	val.it_value.tv_sec = TIMEOUT;
	val.it_value.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &val, 0) == -1)
	{
		perror("setitimer");
		return (1);
	}

	else
	{
		for(;;)
		{
			(void) pause(); // Waiting for signal.
		}
	}

	return 0;
}