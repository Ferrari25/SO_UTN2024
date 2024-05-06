#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc , char * argv[]) {
    pid_t pid;
    int n = atoi(argv[1]);
    int i; 

    for (i =0;i < n; i++)
    {
        pid = fork();
        if (pid > 0)break;
    }

    printf("padre %d saliendo -- creo hijo %d\n", getpid() , pid);
    exit(0);
    

    return 0;
}

