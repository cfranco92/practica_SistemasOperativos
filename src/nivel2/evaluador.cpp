/** NIVEL 2
 ** Proceso evaluador (evaluador): El evaluador se encarga de recibir una expresión
 ** al inicio del programa y cada vez que llega por su entrada estándar un entorno
 ** de variables, estas son ejecutadas por el y retornar su respuesta por la salida
 ** estándar. aaa**/

/*#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
  char c;
  while((c = std::cin.get()) != EOF){
    std::cout << (char) c;
  }

  return EXIT_SUCCESS;
}*/

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> 

using namespace std;

void evaluador(int a, int b)
{
	int c = a + b;
	printf("nivel2: Evaluador -> respuesta:  %d \n", c);
	return;
}

int main()
{   
    evaluador(5, 6); //el valor que cojemos aca sera cambiado por la lectura de .cfg
    return 0;
}  