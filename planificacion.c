/*
este ejemplo muestra una pequeña planificacion de procesos
donde un proceso padre planifica la ejecucuin de sus hijos
la cantidad de hijos que se crean se ingresa desde lla linea
de comandos cuando se manda a ejecutar el ejemplo
--------------------------------------------------------
un proceso padre crea n procesos en abanico
el proceso padre cumple la funcion de ser un proceso planificador de procesos
el procesos planificador le asigna cinco segundos de ejecucion a cada proceso
hijo en el orden en el cual fueron creados
La ejecucion de los procesos hijos solo muestra por pantalla su PID
--------------------------------------------------------
se usa la funcion alarm(..)combinada con la señal SIGALRM para representar el 
el tiempo de ejecucion que el planificador le asigna a cada proceso
-----------------------------------------------------------
el padre setea la alarma para enviar la señal SIGALRM cada cinco segundos
cuando se cumple el tiempom la alarma interrumpe y el planificador detiene el
proceso hijo que esta en ejecucion y pone en ejecucuon al siguiente hijo en forma
de rueda circular
-----------------------------------------------------------
se usa señal SIGSTOP para detener la ejecucion de un proceso y la señal
SIGCONT para reanudar su ejecucion
*/

/*
para ejecutar el codigo hay que pasalar desde la linea de comando la 
cantidad de procesos hijos que se van a crearr, por ej, si se complia con
$ gcc- Wall -o plan planificacion.c
cuando se ejecuta, se escribe 
./plan 5
con la ejecucion anterior se crearan 5 procesos hijos del mismo padre osea
en abanico*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>


//FUNCIONES
void FuncionAlarma(void); //se ejecuta cuando se recibe la señal SIGALRM

//VARIABLES GLOBALES
int numproces; //cantidad de procesos hijos
pid_t vecpid[100]; //vector de pids de procesos
int ent; //indice del vector de pids de procesos

//MAIN
int main(int argc, char * argv[]) //prototipo de main, el cual recibe argumentos desde la linea de comandos
{
    pid_t pid; //variable retornada por el fork()
    int i; //variable iteracion
    
    numproces = atoi(argv[1]);//convierte en entero lo que recibio en string desde linea de comando
                             // y lo almacena en la variable

    for (i = 0; i < numproces; i++)//ciclo creado de procesos hijos en abanico
    {
        pid = fork();

        if (pid == 0) //HIJO
        {
            printf("....hijo i = %d, pid = %d, se detiene espeando planificacion",i,getpid());
            raise(SIGSTOP); //el hijo creado se envia a si mismo la señal SIGSTOP
                            //para detenerse hasta comenzar con el proceso de ejecucion circular
            break;//el hijo creado sale del ciclo
        }
        vecpid[i] = pid;
        sleep(1);
    }
    if (i == numproces) //cuando i = numproces, es el padre y ya creo todos los hijos
    {
        //codigo que ejecuta el padre
        signal(SIGALRM, (void*)FuncionAlarma); // el padre instala el nuevo handler para la señal SIGALRM con la funcion FuncionAlarma
        printf("\n.....Padre i = %d , pid = %d, Planificando\n\n",i,getpid());
        ent = 0;
        while(1)
        {
            printf("Padre reanuda al hijo %d , pid %d", ent, vecpid[ent]);
            kill(vecpid[ent],SIGCONT); // el padre le da continuacion de ejecucion al hijo vecpid[ent] enviadole la señal SIGCONT
            alarm(5); // setea la alarma para recibir la señal SIGALRM en 5 segundos
            printf("---> Padre pausado\n");
            pause(); // el padre se pausa esperando la señal SIGALARM
            ent =(ent +1) % numproces; //ent queda apuntando al proxmo proceso
        }        
    }
    else
    {
        //CODIGO QUE EJECUTA EL HIJO
        while(1)
        {
            printf(".......Hijo %d, pid %d ejecutando, valor de i =%d", i, getpid(),i);
            int i;
            for(i=0;i<6;i++){printf("%d\n",getpid());sleep(1);}
        }
    }
    exit(0);

}

void FuncionAlarma(void)
{
    printf("Padre detiene al hijo %d pid =%d\n\n",ent,vecpid[ent]);
    kill(vecpid[ent],SIGSTOP);//el padre detiene al hijo vecpid[ent]
}