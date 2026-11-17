Name: Jajala Bhavitha
Roll Number: 2402MC07
Set Number: Set 2

Question 1: Page Protection with mprotect() and munprotect()
- Added change_prot() in vm.c (declared in defs.h) to validate page alignment, positive length, and address bounds, verify PTE_P/PTE_U flags via walkpgdir(), toggle PTE_W, and flush the TLB using lcr3(V2P(myproc()->pgdir)).
- Registered mprotect() and munprotect() system calls across syscall.h, syscall.c, sysproc.c, user.h, and usys.S, and added _prottest to Makefile.
- Created prottest.c to verify read access after mprotect(), kernel termination of a child writing to a read-only page, restored write access after munprotect(), and -1 returns on invalid arguments.

Question 2: Priority-Based CPU Scheduler
- Added an integer priority field to struct proc in proc.h and initialized it to default priority 10 inside allocproc() in proc.c.
- Implemented set_priority(int pid, int priority) in proc.c under ptable.lock to validate range 1..20, update the target process priority, and return its previous priority.
- Updated scheduler() in proc.c to select the RUNNABLE process with the numerically smallest priority (breaking ties by process table order) and added schedtest.c to verify execution order (5 -> 10 -> 15).
