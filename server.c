#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void    handle_sigusr(int sig)
{
    printf("Received signal %d\n", sig);

    printf("Received some signal!");
}

int main(int argc, char **argv)
{
    int pid;

    pid = getpid();

    printf("The process id of the server is: %d\n", pid);
    printf("Waiting for signals..\n");

    signal(SIGUSR1, handle_sigusr);
    
    while (1)
    {
        
    }
}