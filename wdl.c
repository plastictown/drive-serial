
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "drive-serial.h"

int main(int argc, char** argv)
{
  char buf[255] = {0};
  serial(buf);
  //printf("%s\n", buf);
  putsn(buf);
  while(1)
  {
    sleep(1);
  }
  return EXIT_SUCCESS;
}
