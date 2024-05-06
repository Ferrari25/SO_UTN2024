#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) {
    pid_t pid , hijoter;
    int status;

    pid = fork();

    if (pid == 0) //HIJO
    {
        printf("soy el hijo %d, mi padre es %d \n",getpid(), getppid());
        printf("me convierto en otra cosa\n");
        //execl("./prueba1","./prueba1",0); ==> le paso el ejecutable al execl 
        execl(argv[1],argv[1],0); //==> cambio la cabecera para pasarle por linea de comando, el ejecutable a utiliza
        
        exit(7);
    }
    else
    {
        if (pid > 0) //PADRE
        {
            printf("soy el padre %d y mi hijo tiene pid = %d y mi padre %d \n",getpid(), pid, getppid());
            printf("estoy esperando la terminacion del hijo\n");
            hijoter = wait(&status);
            printf("termino mi hijo %d \n",hijoter);

            printf("mi hijo termino y me envio un %d\n",WEXITSTATUS(status));
            //printf("mi hijo termino y me envio un %d\n",status/256);
            }

        else//ERROR 
        printf("el fork fallo \n");
    }

    return 0;
}

