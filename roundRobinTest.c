#include "types.h"
#include "stat.h"
#include "user.h"

#include "param.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int main(int argc, char *argv[]) {
    int id[10] , run=1, ready=2, sleep=3, prio=4;
    int counter = 0;
    int turnT[10], waitT[10], cbt[10];
    int turnAve=0, waitAve=0, cbtAve=0;
    int thisID = getpid();
    for (int i=0; i<10; i++) {
        if (getpid() == thisID) fork();
    }

    if (getpid() == thisID) {
        for (int i=0; i<10; i++) {
            id[counter] = tmeasure_wait(&run, &ready, &sleep, &prio);
            turnT[counter] = run + ready + sleep;
            waitT[counter] = ready;
            cbt[counter] = run;
            turnAve += turnT[counter];
            waitAve += waitT[counter];
            cbtAve += cbt[counter];
            counter++;
        }
    }
    else {
        for (int i=1; i<=1000; i++) {
            patternPrint(i);
            //printf(1, "/%d/ : /%d/\n", getpid(), i);
        }
        exit();
    }
    
    for (int i=0; i<10; i++) {
        printf(1, "Turnaround Time for /%d/ = %d\n",id[i],turnT[i]);
        printf(1, "Waiting Time for /%d/ = %d\n",id[i],waitT[i]);
        printf(1, "CBT Time for /%d/ = %d\n\n",id[i],cbt[i]);
    }
    waitAve /= 10;
    turnAve /= 10;
    cbtAve /= 10;
    printf(1, "Averages = %d %d %d\n\n",turnAve,waitAve,cbtAve);
    exit();

}
