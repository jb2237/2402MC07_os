#include "types.h"
#include "user.h"

void
spin(void)
{
  volatile int i, j;
  for(i = 0; i < 3000; i++){
    for(j = 0; j < 20000; j++){
      asm volatile("nop");
    }
  }
}

int
main(void)
{
  int prios[3] = {15, 5, 10};
  set_priority(getpid(), 1);

  for(int k = 0; k < 3; k++){
    int p = prios[k];
    int pid = fork();
    if(pid == 0){
      spin();
      printf(1, "Child (pid=%d) with priority %d finished\n", getpid(), p);
      exit();
    } else {
      set_priority(pid, p);
    }
  }

  for(int k = 0; k < 3; k++)
    wait();

  printf(1, "Done\n");
  exit();
}
