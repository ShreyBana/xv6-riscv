#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("%l\n", freepm());
  return 0;
}
