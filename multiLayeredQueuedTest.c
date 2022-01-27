#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int id[60] , run=1, ready=2, sleep=3, prio=4;
    int counter = 0;
    int turnT[60], waitT[60], cbt[60];
    int turnAve=0, waitAve=0, cbtAve=0;
    int tA[6]={0}, wA[6]={0}, cbtA[6]={0};
    int thisID = getpid();
    for (int i=0; i<60; i++) {
        if (getpid() == thisID) {
            fork();
            if (getpid() != thisID) {
                setPriority(i/10 + 1);
            }
        }
    }

    if (getpid() == thisID) {
        for (int i=0; i<60; i++) {
            id[counter] = tmeasure_wait(&run, &ready, &sleep, &prio);
            turnT[counter] = run + ready + sleep;
            waitT[counter] = ready;
            cbt[counter] = run;
            turnAve += turnT[counter];
            waitAve += waitT[counter];
            cbtAve += cbt[counter];
            tA[prio-1] += turnT[counter];
            wA[prio-1] += waitT[counter];
            cbtA[prio-1] += cbt[counter];
            counter++;
        }
    }
    else {
        for (int i=1; i<=200; i++) {
            withPriPrint(i);
            //printf(1, "/%d/ : /%d/\n", getpid(), i);
        }
        exit();
    }
    
    for (int i=0; i<60; i++) {
        printf(1, "Turnaround Time for /%d/ = %d\n",id[i],turnT[i]);
        printf(1, "Waiting Time for /%d/ = %d\n",id[i],waitT[i]);
        printf(1, "CBT Time for /%d/ = %d\n\n",id[i],cbt[i]);
    }
    waitAve /= 60;
    turnAve /= 60;
    cbtAve /= 60;
    printf(1, "Averages = %d %d %d\n\n",turnAve,waitAve,cbtAve);
    for (int i=0; i<6; i++) {
        tA[i] /= 10;
        printf(1, "turn Average for queue %d = %d\n",i+1,tA[i]);
        wA[i] /= 10;
        printf(1, "wait Average for queue %d = %d\n",i+1,wA[i]);
        cbtA[i] /= 10;
        printf(1, "cbt Average for queue %d = %d\n\n",i+1,cbtA[i]);
    }
    exit();

}

