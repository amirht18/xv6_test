#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  int pid, pty;

  pid = atoi(argv[1]);
  pty = atoi(argv[2]);

  if (pty < 1 || pty > 6) {
    printf(2, "Invalid priority \n" );
    exit();
  }

  setPriority(pid, pty);

  exit();
}