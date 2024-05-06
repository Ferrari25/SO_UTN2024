#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


int main(int argc, char * argv[])
{

    int res; 
    kill(atoi(argv[1]), SIGINT);
    if (errno = ESRCH)
        printf("proceso receptor señal no exite\n");
    exit(0);
}