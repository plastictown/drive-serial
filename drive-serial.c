
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/hdreg.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include <stdio.h>
#include <ctype.h>

#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "drive-serial.h"

int putsn(const char* sn)
{
  key_t key;
  int shmid;
  struct memory_block* mblock;
  key = ftok(SHMEM_NAME, SHMEM_KEY);
  shmid = shmget(key, sizeof(struct memory_block), 0666 | IPC_CREAT);
  mblock = (struct memory_block*) shmat(shmid, 0, 0);
  memset(mblock, 0, sizeof(struct memory_block));
  memcpy(mblock, sn, strlen(sn));
  return 0;
}

void ctrim(char** s)
{
  char* str = *s;
  if(strlen(str) < 1)
    return;
  int left = 0;
  int right = strlen(str) - 1;
  while(!isprint(str[left]) && (left < strlen(str) - 1)) ++left;
  while(!isprint(str[right]) && (right > 0)) --right;

  int len = right - left + 2;
  char* buf = (char*)calloc(len, sizeof(char));
  memcpy (buf, str + left, right - left + 1);
  free (*s);
  *s = buf;
}

void serial( char* buf)
{

  static struct hd_driveid hd;
  int fd;

  char* dev = get_root_device();
  if(dev == NULL)
  {
    printf("can't get drive s/n\n");
    return;
  }
  ctrim(&dev);


  if ((fd = open(dev, O_RDONLY | O_NONBLOCK)) < 0)
  {
    printf("ERROR opening %s\n", dev);
    perror("open failed: ");
    free(dev);
    exit(EXIT_FAILURE);
  }

  if (!ioctl(fd, HDIO_GET_IDENTITY, &hd))
  {
    sprintf(buf, "%.20s", hd.serial_no);
  }
  else if (errno == -ENOMSG)
  {
    printf("No serial number available\n");
  }
  else
  {
    perror("ERROR: HDIO_GET_IDENTITY");
    free(dev);
    exit(EXIT_FAILURE);
  }
  free(dev);
}

char* get_root_device()
{
  const size_t max_buf_sz = 256u;
  const char* cmd = "awk '$2==\"/\"{print $1}' /proc/self/mounts";
  FILE* pipe = popen(cmd, "r");
  if(NULL == pipe)
  {
    perror("can't open pipe: ");
    return NULL;
  }
  char buf[max_buf_sz];
  if( fgets(buf, sizeof buf, pipe) == NULL)
  {
    perror("can't read from pipe: ");
    pclose(pipe);
    return NULL;
  }
  pclose(pipe);
  size_t len = strlen(buf);
  char* ret_buf = (char*) calloc(len + 1u, sizeof(char));
  if(NULL == ret_buf)
  {
    perror("can't allocate memory: ");
    return NULL;
  }
  strcpy(ret_buf, buf);
  return ret_buf;
}
