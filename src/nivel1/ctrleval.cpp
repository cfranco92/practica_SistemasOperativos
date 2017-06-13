/** NIVEL 1
 ** Proceso de control de evaluaciones (ctrleval): También llamado proceso de
 ** nivel 1. Este proceso se encarga de controlar un conjunto de procesos de nivel 2
 ** (evaluador) que se encargarán de realizar las evaluaciones de cada expresión
 ** descrita por un fichero de configuración ubicado en un directorio en particular
 ** (ctrleval.cfg). El proceso de control se encarga de obtener las variables de
 ** ambiente del proceso padre de nivel 0 y pasarla a cada uno de sus procesos hijos
 ** (nivel 2) en el orden que estos están definidos en fichero de configuración. **/

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;


//------------------------------------------------------------------------------
                          // CREACION DE PROCESOS
//------------------------------------------------------------------------------
void CrearCtrlEval(int n, bool repeat)
{

    pid_t proceso;
    proceso = fork();

    if(proceso == 0)
    {
        execl("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel2/evaluador.exe", NULL);
    }

    /*padre(ctrlSis)*/
    else
    {
        if(repeat == true)
        {
            printf("nivel1: ctrlEval %d \n", getpid());
        }

        for(int j= 1; j < n; j++)
        {
            CrearCtrlEval(0, false);
        }
    }

    return;
}





int main()
{ 
    //int num_Evaluadores = atoi(argv[1]);
    string valor;
    string line;
    char* num_Evaluadores;
    int c;

//------------------------------------------------------------------------------
                          // LEER EL ARCHIVO .CFG
//------------------------------------------------------------------------------

    ifstream myfile ("C:/Users/USER/Documents/Universidad/Operativos/Practica1/src/nivel1/example.cfg");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            
        }
        myfile.close();
    }else{
        printf("No se puede abrir el archivo, default de evaluadores: 3 \n");
        line = "2";
        num_Evaluadores = new char [line.length()+1];
        strcpy (num_Evaluadores, line.c_str());
    }
    num_Evaluadores = new char [line.length()+1]; // en esta variable va la informacion del .cfg
    strcpy (num_Evaluadores, line.c_str());


    

    while ((c = cin.get()) != EOF) {
        //cout << (char) c "\n";
    }


//------------------------------------------------------------------------------
                          // MANEJO DE TUBERIAS
//------------------------------------------------------------------------------




    /*Creacion de procesos evaluadores*/
    CrearCtrlEval(atoi(num_Evaluadores), true);
    return 0;
}  