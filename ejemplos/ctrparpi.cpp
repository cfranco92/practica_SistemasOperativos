#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct WriteIn {
  int in;
  int out;
};

void* readWriteThread(void *);

int
main(void) {
  int pipeInSort[2];
  int pipeOutSort[2];

  int pipeInMay[2];
  int pipeOutMay[2];

  pipe(pipeInSort);
  pipe(pipeOutSort);
  pipe(pipeInMay);
  pipe(pipeOutMay);

  pid_t sortChild;
  pid_t mayChild;

  if ((sortChild = fork()) == 0) {
    // Sort
    close(pipeInMay[0]);
    close(pipeInMay[1]);
    close(pipeOutMay[0]);
    close(pipeOutMay[1]);
    close(pipeOutSort[1]);
    close(pipeInSort[0]);
    dup2(pipeOutSort[0], 0);
    dup2(pipeInSort[1], 1);
    close(pipeOutSort[0]);
    close(pipeInSort[1]);
    execl("/usr/bin/sort", "sort", NULL);
    return 1;
  }

  if ((mayChild = fork()) == 0) {
    // mayusculas
    close(pipeInSort[0]);
    close(pipeInSort[1]);
    close(pipeOutSort[0]);
    close(pipeOutSort[1]);
    close(pipeInMay[0]);
    close(pipeOutMay[1]);
    dup2(pipeOutMay[0], 0);
    dup2(pipeInMay[1], 1);
    close(pipeOutMay[0]);
    close(pipeInMay[1]);
    execl("./mayusculas", "mayusculas", NULL);
    return 1;
  }

  close(pipeOutSort[0]);
  close(pipeInSort[1]);
  close(pipeOutMay[0]);
  close(pipeInMay[1]);

  WriteIn wiFil, wiSort, wiMay;

  if ((wiFil.in = open("ctrparpi.cpp", O_RDONLY)) == -1) {
    std::cerr << "Error open file" << std::endl;
    return 1;
  }

  wiFil.out = pipeOutSort[1];
  wiSort.in = pipeInSort[0];
  wiSort.out = pipeOutMay[1];
  wiMay.in = pipeInMay[0];
  wiMay.out = 1;

  pthread_t threadFile, threadSort, threadMay;

  pthread_create(&threadFile, NULL, readWriteThread, &wiFil);
  pthread_create(&threadSort, NULL, readWriteThread, &wiSort);
  pthread_create(&threadMay,  NULL, readWriteThread, &wiMay);

  void *ret;

  pthread_join(threadFile, &ret);
  pthread_join(threadSort, &ret);
  pthread_join(threadMay, &ret);

  // close(pipeOutSort[1]);
  // close(pipeInSort[0]);
  // close(pipeOutMay[1]);
  // close(pipeInMay[0]);
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
