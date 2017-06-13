#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>


using namespace std;





struct WriteIn {
        int in;
        int out;
};

void* readWriteThread(void *);







//------------------------------------------------------------------------------
                          // FUNCION DE CREAR PROCESOS
//------------------------------------------------------------------------------
void CrearCtrlEval(int n, bool repeat, char* ProcesosEval)
{
    pid_t proceso;

    int fd_in[2];
    int fd_out[2];
    pipe(fd_in);
    pipe(fd_out);

    WriteIn WReval, WRfile;

//------------------------------------------------------------------------------
                          // CREAR PROCESOS
//------------------------------------------------------------------------------
    proceso = fork();
    if(proceso == 0)
    {
        close(fd_out[1]);
        close(fd_in[0]);
        dup2(fd_in[1],1);
        dup2(fd_out[0],0);
        close(fd_out[0]);
        close(fd_in[1]);
        printf("Creando Proceso \n");
        execl("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel1/ctrleval.exe", "ctrleval.exe", NULL);
    }

    else
    {

        if (repeat == true)
        {
            printf("nivel0: ctrlSis \n", getpid());
            repeat = false;
        }

        for(int j= 1; j < n; j++)
        {  
            //printf("Creando Proceso parte 2 \n");
            CrearCtrlEval(0, false, ProcesosEval);
        }
//------------------------------------------------------------------------------
                          // MANEJO DE TUBERIAS
//------------------------------------------------------------------------------
        close(fd_in[1]);
        close(fd_out[0]);

        if ((WRfile.in = open("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel0/fileIn.txt", O_RDONLY)) == -1) {
            cerr << "Error open file" << endl;
            return;
        }

        WRfile.out = fd_out[1];
        WReval.out = 1;
        WReval.in = fd_in[0];

        pthread_t threadCtrlEval, threadFile;
        pthread_create(&threadFile, NULL, readWriteThread, &WRfile);
        pthread_create(&threadCtrlEval, NULL, readWriteThread, &WReval);


        void *ret;
        pthread_join(threadFile, &ret);
        pthread_join(threadCtrlEval, &ret);
    }

    return;
}











//------------------------------------------------------------------------------
                          // MAIN
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{ 


//------------------------------------------------------------------------------
                          // INICIO DE VARIABLES
//------------------------------------------------------------------------------
    bool repeat = true;
    char * ArregloTuberias;
    /*pid_t proceso;

    int fd_in[2];
    int fd_out[2];
    pipe(fd_in);
    pipe(fd_out);

    WriteIn WReval, WRfile;*/

//------------------------------------------------------------------------------
                          // LEER EL ARCHIVO .CFG
//------------------------------------------------------------------------------
    string line;
    ifstream myfile ("example.cfg");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            
        }
        myfile.close();
    }
    char* num_controladores = new char [line.length()+1]; // en esta variable va la informacion del .cfg
    strcpy (num_controladores, line.c_str());

    CrearCtrlEval(atoi(num_controladores), true, ArregloTuberias);



//------------------------------------------------------------------------------
                          // CREAR PROCESOS
//------------------------------------------------------------------------------
    /*proceso = fork();
    if(proceso == 0)
    {
        close(fd_out[1]);
        close(fd_in[0]);
        dup2(fd_in[1],1);
        dup2(fd_out[0],0);
        close(fd_out[0]);
        close(fd_in[1]);
        execl("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel1/ctrleval.exe", "ctrleval.exe", num_controladores, NULL);
    }

    else
    {

        if (repeat == true)
        {
            printf("nivel0: ctrlSis \n", getpid());
            repeat = false;
        }

        for(int j= 1; j < atoi(num_controladores); j++)
        {
            if(fork() == 0)
            {
                execl("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel1/ctrleval.exe", "ctrleval.exe", num_controladores, NULL);
            }
        }



//------------------------------------------------------------------------------
                          // MANEJO DE TUBERIAS
//------------------------------------------------------------------------------
        

        close(fd_in[1]);
        close(fd_out[0]);

        if ((WRfile.in = open("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel0/fileIn.txt", O_RDONLY)) == -1) {
            cerr << "Error open file" << endl;
            return 1;
        }

        WRfile.out = fd_out[1];
        WReval.out = 1;
        WReval.in = fd_in[0];

        pthread_t threadCtrlEval, threadFile;
        pthread_create(&threadFile, NULL, readWriteThread, &WRfile);
        pthread_create(&threadCtrlEval, NULL, readWriteThread, &WReval);


        void *ret;
        pthread_join(threadFile, &ret);
        pthread_join(threadCtrlEval, &ret);
    }*/

    return 0;
}





//------------------------------------------------------------------------------
                          // FUNCION PRINCIPAL DE LAS TUBERIAS
//------------------------------------------------------------------------------


void* readWriteThread(void *arg) {
  WriteIn *dataInOut = (struct WriteIn *) arg;

  char c;
  while (read(dataInOut->in, &c, 1) > 0) {
    // std::cout << "In: " << c << std::endl;
    write(dataInOut->out, &c, 1);
  }
  close(dataInOut->in);
  close(dataInOut->out);
  return NULL;
}








