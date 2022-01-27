#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int pol = atoi(argv[1]);
    changePolicy(pol);
    printf(1, "The Scheduling Policy changed to %d\n", pol);
    exit();
}