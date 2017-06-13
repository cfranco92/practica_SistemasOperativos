/** NIVEL 2
 ** Proceso evaluador (evaluador): El evaluador se encarga de recibir una expresión
 ** al inicio del programa y cada vez que llega por su entrada estándar un entorno
 ** de variables, estas son ejecutadas por el y retornar su respuesta por la salida
 ** estándar. **/

 #include <iostream>
 #include <cctype>
 #include <stdio.h>
 #include <stdlib.h> 
 #include <string>

 int
 main(void) {
   char c;

  //  while ((c = std::cin.get()) != EOF) {
  //      c = ::toupper(c);
  //      std::cout << (char) c;
  //  }

    std::string s;
    while ((c = std::cin.get()) != EOF) {
      c = ::toupper(c);
      s = s + c;
      //  c = ::toupper(c);
      //std::cout << (char) c;
    }

    /*char * DIRDETRABAJO = getenv ("DIRDETRABAJO");
    char * FICHEROCFG = getenv ("FICHEROCFG");

    printf ("VALOR DE LAS ENV: %s",DIRDETRABAJO);
    printf ("VALOR DE LAS ENV: %s",FICHEROCFG);*/

    std::cout << s << std::endl;//"\n";

     return 0;
 }
