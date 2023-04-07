#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handle_sigusr(int sig, siginfo_t *info, void *ucontext);

int main(int argc, char **argv)
{
    int pid;
    struct sigaction	action;

    pid = getpid();

    printf("The process id of the server is: %d\n", pid);
    printf("Waiting for signals..\n");

    action.sa_sigaction = handle_sigusr;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
    while (1)
    {
        pause();
    }
    return (0);
}

void handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
    printf("Received signal %d\n", sig);
    printf("Received some signal!");
    //printf("Client pid: %d\n", info->si_pid);
}