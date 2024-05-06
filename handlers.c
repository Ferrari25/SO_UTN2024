#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

//FUNCIONES
void new_handler(int);
void new_handler_sig_alarm(int);


//int main(int argc, char * argv[])
int main(void)
{
    signal(SIGINT, (void *) new_handler);
    signal(SIGALRM, (void *)new_handler_sig_alarm);
    alarm(10);
    while(1)
    {
        printf("aqui estoy mi pid %d \n",getpid());
        sleep(1);

    }
    exit(0);
}


void new_handler(int s)
{
    printf("--recibi la señal --> %d ---\n",s);
}

/**
 * funcion que luego de ejecutar la alarm, pondra en default a la
 * alarma sigint
*/
void new_handler_sig_alarm(int s)
{
    printf(" **** recibi la señal --> %d\n",s);
    signal(SIGINT,SIG_DFL);
    signal(SIGALRM,SIG_DFL);
    alarm(5);
}

