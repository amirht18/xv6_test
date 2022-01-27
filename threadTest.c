
#include "types.h"
#include "stat.h"
#include "user.h"

void childPrint(void* args) {
    printf(1, "hi bye : %d\n", *(int*) args);
}

int main(void) {
    int arg1 = 1;
    int arg2 = 2;
    int arg3 = 3;
    int arg4 = 4;

    int thread1_id = thread_creator(&childPrint, (void*)&arg1);
    if(thread1_id < 0) {
        printf(1, "thread_creator failed\n");
    }
    thread_wait();
    printf(1, "thread1_id is : %d\n", thread1_id);

    int thread2_id = thread_creator(&childPrint, (void*)&arg2);
    if(thread2_id < 0) {
        printf(1, "thread_creator failed\n");
    }
    thread_wait();
    printf(1, "thread2_id is : %d\n", thread2_id);

    int thread3_id = thread_creator(&childPrint, (void*)&arg3);
    if(thread3_id < 0) {
        printf(1, "thread_creator failed\n");
    }

    int thread4_id = thread_creator(&childPrint, (void*)&arg4);
    if(thread3_id < 0) {
        printf(1, "thread_creator failed\n");
    }

    thread_wait();
    thread_wait();
    printf(1, "thread3_id is : %d\n", thread3_id);
    printf(1, "thread4_id is : %d\n", thread4_id);

    exit();
}

/*
#include "types.h"
#include "stat.h"
#include "user.h"

int stack[4096] __attribute__ ((aligned (4096)));
int x = 0;

int main(int argc, char *argv[]) {
  printf(1, "Stack is at %p\n", stack);
  int tid = fork();
  //int tid = thread_create(stack);

  if (tid < 0) {
    printf(2, "error!\n");
  } else if (tid == 0) {
    // child
    for(;;) {
      x++;
      sleep(100);
    }
  } else {
    // parent
    for(;;) {
      printf(1, "x = %d\n", x);
      sleep(100);
    }
  }

  exit();
}
*/