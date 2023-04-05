#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int pid;

    pid = getpid();

    printf("The process id of the server is: %d\n", pid);
}