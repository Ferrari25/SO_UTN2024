#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

//int main(int argc, char * argv[])
int main(void)
{
    //signal(SEÑAL,FUNCION)
    signal(SIGINT, SIG_IGN);
    while (1)
    {
        printf("aqui estoy con mi pid %d\n",getpid());
        sleep(1);
    }
    exit(0);
}