#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

extern int readCount;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getProcCount(void)
{
  return getProcCount();
}

int
sys_getReadCount(void)
{
  return readCount;
}


int
sys_thread_create(void)
{
  int stack;
  if (argint(0, &stack) < 0) return -1;
  return thread_create((void*)stack);
}

int
sys_thread_wait(void)
{
  return thread_wait();
}

int
sys_tmeasure_wait(void)
{
  int *runningT;
  int *readyT;
  int *sleepingT;
  int *pri;

  if (argptr(0, (char**)&readyT, sizeof(int)) < 0)
    return -1;
  if (argptr(1, (char**)&runningT, sizeof(int)) < 0)
    return -1;
  if (argptr(2, (char**)&sleepingT, sizeof(int)) < 0)
    return -1;
  if (argptr(3, (char**)&pri, sizeof(int)) < 0)
    return -1;
  return tmeasure_wait(runningT, readyT, sleepingT, pri);
}

int
sys_patternPrint(void)
{
  int number;
  if (argint(0, &number) < 0) return -1;
  patternPrint(number);
  return 0;
}

int
sys_changePolicy(void)
{
  int pol;
  if (argint(0, &pol) < 0) return -1;
  changePolicy(pol);
  return 0;
}

int
sys_changeTimes(void)
{
  changeTimes();
  return 0;
}

int
sys_setPriority(void)
{
  int prio;
  if (argint(0, &prio) < 0) return -1;

  setPriority(prio);
  return 0;
}

int
sys_withPriPrint(void)
{
  int prio;
  if (argint(0, &prio) < 0) return -1;
  return withPriPrint(prio);
}

int
sys_isHigherQueueAvailable(void)
{
  int available;
  if (argint(0, &available) < 0) return -1;
  return isHigherQueueAvailable();
}
