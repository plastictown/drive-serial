
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 #include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>


#include "drive-serial.h"

enum apptype{CLIENT, SERVER, UNKNOWN};

int main(int argc, char** argv)
{
    int type = UNKNOWN;
    if(argc >= 2){
        if(strcmp("-c", argv[1]) == 0)
            type = CLIENT;
        else if(strcmp("-s", argv[1]) == 0)
            type = SERVER;
    }
    if(type == UNKNOWN)
    {
        printf("usage: %s <flag>\n where flag is: -c or -s\n", argv[0]);
        return EXIT_FAILURE;
    }
if(type == SERVER)
{
  char buf[255] = {0};
  serial(buf);
  printf("%s\n", buf);
  putsn(buf);
  while(1){
      sleep(1);
  }
}
else if(type == CLIENT)
{
    key_t key = ftok(SHMEM_NAME, SHMEM_KEY);
    int shmid = shmget(key, sizeof(struct memory_block), 0666);
    if(shmid == -1){
        perror("can't open shmem: ");
        return EXIT_FAILURE;
    }
    struct memory_block* blk = (struct memory_block*)shmat(shmid,0,0);
    if(blk != NULL){
        printf("s/n from shmem: %s\n", blk->string);
    }
}
  return EXIT_SUCCESS;
}
