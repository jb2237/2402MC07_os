#include "types.h"
#include "user.h"

int
main(void)
{
  char *p = sbrk(4096);
  *p = 'A';

  int r1 = mprotect(p, 1);
  printf(1, "(i) mprotect(p, 1) returned %d, read value: %c\n", r1, *p);

  int pid = fork();
  if(pid == 0){
    printf(1, "(ii) Child attempting write to read-only page...\n");
    *p = 'B';
    printf(1, "(ii) ERROR: Child survived write!\n");
    exit();
  }
  wait();
  printf(1, "(ii) Parent continued after child killed, value still: %c\n", *p);

  int r2 = munprotect(p, 1);
  *p = 'C';
  printf(1, "(iii) munprotect(p, 1) returned %d, new value: %c\n", r2, *p);

  printf(1, "(iv) unaligned addr: %d\n", mprotect(p + 1, 1));
  printf(1, "(iv) len=0: %d\n", mprotect(p, 0));
  printf(1, "(iv) out of range: %d\n", mprotect(p, 100));

  exit();
}
