#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv)
{
    printf("The process id of the server is: %d\n", 526);
    printf("Client ready to send signals..\n");
    printf("%s\n", argv[0]);
    kill(526, 12);
}