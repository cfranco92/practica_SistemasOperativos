#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main() {

  int tuberia1[2];
  int tuberia2[2];

  pipe(tuberia1);
  pipe(tuberia2);

  // Crear primer hijo ls
  if (fork() == 0) {
    dup2(tuberia1[1],1);
    close(tuberia1[0]);
    close(tuberia2[0]);
    close(tuberia2[1]);
    execlp("ls", "ls", NULL);
  }
  else {
    // Crear el segundo hijo cat
    if (fork() == 0) {
      char * argumentos[] = { "cat", NULL };
      dup2(tuberia1[0],0);
      dup2(tuberia2[1],1);
      close(tuberia1[1]);
      close(tuberia2[0]);
      execvp("cat", argumentos);
    }
    else {
      // Crear el tercer hijo sort
      pid_t hijoSort;
      if ((hijoSort = fork()) == 0) {
	dup2(tuberia2[0],0);
	close(tuberia2[1]);
	close(tuberia1[0]);
	close(tuberia1[1]);
	execl("/usr/bin/sort", "sort", "-r", NULL);
      }
      else {
	int status;
	close(tuberia1[0]);
	close(tuberia1[1]);
	close(tuberia2[0]);
	close(tuberia2[1]);
	waitpid(hijoSort, &status, 0); 
      }
    }
  }

}
