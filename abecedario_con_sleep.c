/**
 * un proceso hace un fork, tiene un hijo
 * el padre y el hijo van a escribir en un archivo en el fileSystem
 * que cooperen para escribir el abecedario de manera intercalado cada uno
 * y las letras que escribe el padre que sean en minus y las del hijo en mayus
*/

/**
 * otro programa similar al anterior pero que,
 * primero se escrban las minusculas del padre y luego las mayusculas del hijos a..B..
*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>



int main(void) {
    pid_t pid, hijoter;
    int fd = open("abc", O_CREAT | O_WRONLY | O_TRUNC,0600);
    char letra = 'a';
    int i;
    
    for( i = 0; i < 3; i++)
    {
        pid = fork();
        if (pid > 0) //PADRE
        {   

            printf("padre comienza a escribir \n");
            letra='a';
            while (letra <= 'z')
            {
                write(fd,&letra,1);
                letra +=2;
                sleep(1);
            }
            //espera la terminacion del hijo
            hijoter = wait(0);

            //escribe en el archivo, termino mi hijo y el pid las n veces
            char pid[7];
            memset(pid,'\0',7);
            sprintf(pid, "%d", hijoter);
            pid[5] = '\n';
            write(fd,"\nTermino mi hijo ",17); // 17 ya que (\nTermino mi hijo) son 17 bytes, 1 por cada char 
            write(fd,pid,strlen(pid));
        }
        else
        {
            if (pid == 0) //HIJO
            {
                usleep(500000);
                letra = 'B';
                printf("hijo comienza a escribir \n");
                while (letra <= 'Z')
                {
                    write(fd,&letra,1);
                    letra+=2;
                    sleep(1);
                }  
                exit(0);
            }

            else//ERROR 
            perror("el fork fallo \n");
        }
    }
    close(fd);

    return 0;
}



