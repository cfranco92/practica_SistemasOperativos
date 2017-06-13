/** NIVEL 0
 ** Proceso control del sistema (ctrlsis): También llamado proceso de NIVEL 0.
 ** Se encarga ejecutar una serie de procesos definidos por el fichero de descripción
 ** (ctrsis.cfg). Este es responsable de pasar los mensajes de contexto entre los
 ** procesos de nivel 1 (ctreval), este mensaje es pasado en el orden que aparecen
 ** en el fichero de descripción (ctrsis.cfg). **/

 #include <iostream>
 #include <unistd.h>
 #include <pthread.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <stdlib.h>
 #include <fstream>
 #include <sstream>
 #include <stdio.h>
 #include <string>

 using namespace std;

 struct WriteIn {
   int in;
   int out;
 };

 void* readWriteThread(void *);

 int
 main(void) {
   int n = 0;
  //  string entrada;
   //
  //  cin >> entrada;
  char c;
  std::string entrada;
  while ((c = std::cin.get()) != '}') {
    entrada = entrada + c;
   //  c = ::toupper(c);
   //  std::cout << (char) c;
  }
   ofstream ficheroSalida;
   ficheroSalida.open ("proceso.txt");
   ficheroSalida << entrada;
   ficheroSalida.close();

   ofstream ficheroSalida2;
   ficheroSalida.open ("procso.txt");
   ficheroSalida << entrada;
   ficheroSalida.close();

   //cout << "Escriba el nombre del archivo a leer: " << endl;
	string filename = "ctrlsis.cfg";
	//cin >> filename;
	ifstream file(filename.c_str());
	if(!file)
	{
		cout << "Error no se puede abrir el archivo: " << filename << endl;
                return 1;
	}
	string linea, archivo;
	while(getline(file, linea)){
    archivo += linea + "\n";
	  //cout << archivo;
  }


  //OBTENEMOS EL NÚMERO DE PROCESOS DE QUE SE VA A CREAR
   for(int j = 0; j < archivo.length(); j++)
    {
      if(archivo.at(j) == '}')
        {
          n++;
          // letra = argumento.substr(0,j);
          // j++;
          // int numero = atoi(argumento.substr(j).c_str());
          // calc->storeVar(letra,numero);
        }
    }


    //INICIO DE VARIABLES DE ENTORNO

    char * DIRDETRABAJO = "LALALA";
    char * FICHEROCFG = "LALA";


    char *argv[] = { "./ctrleval", "ctrleval", 0 };

    char *envp[] =
    {
        "DIRDETRABAJO",
        "FICHEROCFG",   
        "NULL"
    };

    




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

    char * DIRDETRABAJO = "DIRDETRABAJO=./nivel1/hijo1";
    char * FICHEROCFG = "FICHEROCFG=hijo1.cfg";

    for(int i = 0; i <= 2; i++){
      if(i == 0){
        envp[i] = DIRDETRABAJO;
      }else if( i == 1){
        envp[i] = FICHEROCFG;
      }else{
        envp[i] = 0;
      }
    }

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
     execve(argv[0], &argv[0], envp);
     //execl("./ctrleval", "ctrleval", NULL);
     return 1;
   }

   if(n >= 2){
     if ((evaluador2Child = fork()) == 0) {

      char * DIRDETRABAJO = "DIRDETRABAJO=./nivel1/hijo2";
      char * FICHEROCFG = "FICHEROCFG=hijo2.cfg";

      for(int i = 0; i <= 2; i++){
        if(i == 0){
          envp[i] = DIRDETRABAJO;
        }else if( i == 1){
          envp[i] = FICHEROCFG;
        }else{
          envp[i] = 0;
        }
      }

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
       execve(argv[0], &argv[0], envp);
       //execl("./ctrleval", "ctrleval", NULL);
       return 1;
     }
   }

   if(n >= 3){
     if ((evaluador3Child = fork()) == 0) {

      char * DIRDETRABAJO = "DIRDETRABAJO=./nivel1/hijo3";
      char * FICHEROCFG = "FICHEROCFG=hijo3.cfg";


      for(int i = 0; i <= 2; i++){
        if(i == 0){
          envp[i] = DIRDETRABAJO;
        }else if( i == 1){
          envp[i] = FICHEROCFG;
        }else{
          envp[i] = 0;
        }
      }

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
       execve(argv[0], &argv[0], envp);
       //execl("./ctrleval", "ctrleval", NULL);
       return 1;
     }
   }
   if(n >= 4){
     if ((evaluador4Child = fork()) == 0) {

      char * DIRDETRABAJO = "DIRDETRABAJO=./nivel1/hijo4";
      char * FICHEROCFG = "FICHEROCFG=hijo4.cfg";


      for(int i = 0; i <= 2; i++){
        if(i == 0){
          envp[i] = DIRDETRABAJO;
        }else if( i == 1){
          envp[i] = FICHEROCFG;
        }else{
          envp[i] = 0;
        }
      }


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
       execve(argv[0], &argv[0], envp);
       //execl("./ctrleval", "ctrleval", NULL);
       return 1;
     }
   }
   if(n >= 5){
     if ((evaluador5Child = fork()) == 0) {

      char * DIRDETRABAJO = "DIRDETRABAJO=./nivel1/hijo5";
      char * FICHEROCFG = "FICHEROCFG=hijo5.cfg";


      for(int i = 0; i <= 2; i++){
        if(i == 0){
          envp[i] = DIRDETRABAJO;
        }else if( i == 1){
          envp[i] = FICHEROCFG;
        }else{
          envp[i] = 0;
        }
      }


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
       execve(argv[0], &argv[0], envp);
       //execl("./ctrleval", "ctrleval", NULL);
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

   if ((wiFil.in = open("ctrlsis.cfg", O_RDONLY)) == -1) {
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
