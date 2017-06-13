/** NIVEL 1
 ** Proceso de control de evaluaciones (ctrleval): También llamado proceso de
 ** nivel 1. Este proceso se encarga de controlar un conjunto de procesos de nivel 2
 ** (evaluador) que se encargarán de realizar las evaluaciones de cada expresión
 ** descrita por un fichero de configuración ubicado en un directorio en particular
 ** (ctrleval.cfg). El proceso de control se encarga de obtener las variables de
 ** ambiente del proceso padre de nivel 0 y pasarla a cada uno de sus procesos hijos
 ** (nivel 2) en el orden que estos están definidos en fichero de configuración. **/


 #include <iostream>
 #include <unistd.h>
 #include <pthread.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <stdio.h>
 #include <sstream>
 #include <stdlib.h> 
 #include <string>

 struct WriteIn {
   int in;
   int out;
 };

 void* readWriteThread(void *);

 int
 main(void) {
   int n = 0;
   char c;
   std::string s;
   while ((c = std::cin.get()) != EOF) {
     s = s + c;
    //  c = ::toupper(c);
    //  std::cout << (char) c;
   }

   for(int j = 0; j < s.length(); j++)
    {
      if(s.at(j) == '}')
        {
          n++;
          // letra = argumento.substr(0,j);
          // j++;
          // int numero = atoi(argumento.substr(j).c_str());
          // calc->storeVar(letra,numero);
        }
    }
   std::cout << s << std::endl;



  //LEER INFORMACION DE LAS VARIABLES DE ENTORNO




  /*char *argv[] = {"./evaluador", "evaluador", 0};

  char *envp[] =
  {
      "aaa",
      "bbb",           //ESTO DEBE SER DINAMICO
      0
  };*/
  
  //char * DIRDETRABAJO;
  //char * FICHEROCFG;

  char * DIRDETRABAJO = getenv ("DIRDETRABAJO");
  char * FICHEROCFG = getenv ("FICHEROCFG");

   int pipeInEvaluador[2];
   int pipeOutEvaluador[2];
   int pipeInEvaluador2[2];
   int pipeOutEvaluador2[2];
   int pipeInEvaluador3[2];
   int pipeOutEvaluador3[2];
   int pipeInEvaluador4[2];
   int pipeOutEvaluador4[2];
   int pipeInEvaluador5[2];
   int pipeOutEvaluador5[2];

   if(n >= 1){
     pipe(pipeInEvaluador);
     pipe(pipeOutEvaluador);
   }

   if(n >= 2){
     pipe(pipeInEvaluador2);
     pipe(pipeOutEvaluador2);
   }

   if(n >= 3){
     pipe(pipeInEvaluador3);
     pipe(pipeOutEvaluador3);
   }

   if(n >= 4){
     pipe(pipeInEvaluador4);
     pipe(pipeOutEvaluador4);
   }

   if(n == 5){
     pipe(pipeInEvaluador5);
     pipe(pipeOutEvaluador5);
   }

   pid_t evaluadorChild;
   pid_t evaluador2Child;
   pid_t evaluador3Child;
   pid_t evaluador4Child;
   pid_t evaluador5Child;

   if ((evaluadorChild = fork()) == 0) {

    /*char * DIRDETRABAJO = getenv ("DIRDETRABAJO");
    char * FICHEROCFG = getenv ("FICHEROCFG");
  
    for(int i = 0; i <= 2; i++){
        if(i == 0){
          envp[i] = DIRDETRABAJO;
        }else if( i == 1){
          envp[i] = FICHEROCFG;
        }else{
          envp[i] = 0;
        }
    }*/


     // Sort
     close(pipeInEvaluador2[0]);
     close(pipeInEvaluador2[1]);
     close(pipeOutEvaluador2[0]);
     close(pipeOutEvaluador2[1]);
     close(pipeOutEvaluador[1]);
     close(pipeInEvaluador[0]);
     dup2(pipeOutEvaluador[0], 0);
     dup2(pipeInEvaluador[1], 1);
     close(pipeOutEvaluador[0]);
     close(pipeInEvaluador[1]);
     //execve(argv[0], &argv[0], envp);
     execl("./evaluador", "evaluador", NULL);
     return 1;
   }

   if(n >= 2){
     if ((evaluador2Child = fork()) == 0) {
       // mayusculas
       close(pipeInEvaluador[0]);
       close(pipeInEvaluador[1]);
       close(pipeOutEvaluador[0]);
       close(pipeOutEvaluador[1]);
       close(pipeInEvaluador2[0]);
       close(pipeOutEvaluador2[1]);
       dup2(pipeOutEvaluador2[0], 0);
       dup2(pipeInEvaluador2[1], 1);
       close(pipeOutEvaluador2[0]);
       close(pipeInEvaluador2[1]);
       execl("./evaluador", "evaluador", NULL);
       return 1;
     }
   }

   if(n >= 3){
     if ((evaluador3Child = fork()) == 0) {
       // mayusculas
       close(pipeInEvaluador[0]);
       close(pipeInEvaluador[1]);
       close(pipeOutEvaluador[0]);
       close(pipeOutEvaluador[1]);
       close(pipeInEvaluador2[0]);
       close(pipeInEvaluador2[1]);
       close(pipeOutEvaluador2[0]);
       close(pipeOutEvaluador2[1]);
       close(pipeInEvaluador3[0]);
       close(pipeOutEvaluador3[1]);
       dup2(pipeOutEvaluador3[0], 0);
       dup2(pipeInEvaluador3[1], 1);
       close(pipeOutEvaluador3[0]);
       close(pipeInEvaluador3[1]);
       execl("./evaluador", "evaluador", NULL);
       return 1;
     }
   }
   if(n >= 4){
     if ((evaluador4Child = fork()) == 0) {
       // mayusculas
       close(pipeInEvaluador[0]);
       close(pipeInEvaluador[1]);
       close(pipeOutEvaluador[0]);
       close(pipeOutEvaluador[1]);
       close(pipeInEvaluador2[0]);
       close(pipeInEvaluador2[1]);
       close(pipeOutEvaluador2[0]);
       close(pipeOutEvaluador2[1]);
       close(pipeInEvaluador3[0]);
       close(pipeInEvaluador3[1]);
       close(pipeOutEvaluador3[0]);
       close(pipeOutEvaluador3[1]);
       close(pipeInEvaluador4[0]);
       close(pipeOutEvaluador4[1]);
       dup2(pipeOutEvaluador4[0], 0);
       dup2(pipeInEvaluador4[1], 1);
       close(pipeOutEvaluador4[0]);
       close(pipeInEvaluador4[1]);
       execl("./evaluador", "evaluador", NULL);
       return 1;
     }
   }
   if(n >= 5){
     if ((evaluador5Child = fork()) == 0) {
       // mayusculas
       close(pipeInEvaluador[0]);
       close(pipeInEvaluador[1]);
       close(pipeOutEvaluador[0]);
       close(pipeOutEvaluador[1]);
       close(pipeInEvaluador2[0]);
       close(pipeInEvaluador2[1]);
       close(pipeOutEvaluador2[0]);
       close(pipeOutEvaluador2[1]);
       close(pipeInEvaluador3[0]);
       close(pipeInEvaluador3[1]);
       close(pipeOutEvaluador3[0]);
       close(pipeOutEvaluador3[1]);
       close(pipeInEvaluador4[0]);
       close(pipeInEvaluador4[1]);
       close(pipeOutEvaluador4[0]);
       close(pipeOutEvaluador4[1]);
       close(pipeInEvaluador5[0]);
       close(pipeOutEvaluador5[1]);
       dup2(pipeOutEvaluador5[0], 0);
       dup2(pipeInEvaluador5[1], 1);
       close(pipeOutEvaluador5[0]);
       close(pipeInEvaluador5[1]);
       execl("./evaluador", "evaluador", NULL);
       return 1;
     }
   }

   close(pipeOutEvaluador[0]);
   close(pipeInEvaluador[1]);
   if (n >= 2){
     close(pipeOutEvaluador2[0]);
     close(pipeInEvaluador2[1]);
   }
   if (n >= 3){
     close(pipeOutEvaluador3[0]);
     close(pipeInEvaluador3[1]);
   }
   if (n >= 4){
     close(pipeOutEvaluador4[0]);
     close(pipeInEvaluador4[1]);
   }
   if (n >= 5){
     close(pipeOutEvaluador5[0]);
     close(pipeInEvaluador5[1]);
   }

   WriteIn wiFil, wiEval, wiEval2, wiEval3, wiEval4, wiEval5;

   if ((wiFil.in = open("proceso.txt", O_RDONLY)) == -1) {
     std::cerr << "Error open file" << std::endl;
     return 1;
   }


   wiFil.out = pipeOutEvaluador[1];
   wiEval.in = pipeInEvaluador[0];
   wiEval.out = 1;
   if(n >= 2){
     wiEval.out = pipeOutEvaluador2[1];
     wiEval2.in = pipeInEvaluador2[0];
     wiEval2.out = 1;
   }
   if(n >= 3){
     wiEval2.out = pipeOutEvaluador3[1];
     wiEval3.in = pipeInEvaluador3[0];
     wiEval3.out = 1;
   }
   if(n >= 4){
     wiEval3.out = pipeOutEvaluador4[1];
     wiEval4.in = pipeInEvaluador4[0];
     wiEval4.out = 1;
   }
   if(n >= 5){
     wiEval4.out = pipeOutEvaluador5[1];
     wiEval5.in = pipeInEvaluador5[0];
     wiEval5.out = 1;
   }


   pthread_t threadFile, threadEval, threadEval2, threadEval3, threadEval4, threadEval5;

   pthread_create(&threadFile, NULL, readWriteThread, &wiFil);
   pthread_create(&threadEval, NULL, readWriteThread, &wiEval);
   if(n >= 2){pthread_create(&threadEval2,  NULL, readWriteThread, &wiEval2);}
   if(n >= 3){pthread_create(&threadEval3,  NULL, readWriteThread, &wiEval3);}
   if(n >= 4){pthread_create(&threadEval4,  NULL, readWriteThread, &wiEval4);}
   if(n >= 5){pthread_create(&threadEval5,  NULL, readWriteThread, &wiEval5);}

   void *ret;

   pthread_join(threadFile, &ret);
   pthread_join(threadEval, &ret);
   if(n >= 2){pthread_join(threadEval2, &ret);}
   if(n >= 3){pthread_join(threadEval3, &ret);}
   if(n >= 4){pthread_join(threadEval4, &ret);}
   if(n >= 5){pthread_join(threadEval5, &ret);}

   // close(pipeOutEvaluador[1]);
   // close(pipeInEvaluador[0]);
   // close(pipeOutEvaluador2[1]);
   // close(pipeInEvaluador2[0]);
   // close(wiFil.in);

   return 0;
 }

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
