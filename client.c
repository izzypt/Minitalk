#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int ft_atoi(char *str)
{
    int i;
    int sign;
    int result;

    sign = 1;
    i = 0;
    result = 0;

    if (str[i] == '-')
    {
        sign = sign * (-1);
        str++;
    }

    while (*str)
    {
        result = result * 10 + *str - '0';
        str++;
    }
    return result * sign;
}

int main(int argc, char **argv)
{
    printf("The process id of the server is: %d\n", ft_atoi(argv[1]));
    printf("Client ready to send signals..\nClient pid: %d", getpid());
    //printf("%s\n", argv[0]);
    //printf("%s\n", argv[1]);
    //printf("%s\n", argv[2]);
    kill(ft_atoi(argv[1]), 12);
}