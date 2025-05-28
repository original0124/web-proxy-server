#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <pthread.h>
#include <semaphore.h>
#define MAXLINE 8192
#define RIO_BUFSIZE 8192

typedef struct
{
	int *buf;
	int n;
	int front;
	int rear;
	sem_t mutex;
	sem_t slots;
	sem_t items;
}sbuf_t;

typedef struct
{
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[RIO_BUFSIZE];
}rio_t;

typedef struct
{
	int maxfd;
	sem_t mutex;
	int nready;
	fd_set read_set;
	fd_set ready_set;
}pool;

typedef struct sockaddr SA;

void rio_readinitb(rio_t *rp,int fd);
ssize_t rio_readlineb(rio_t *rp ,void *usrbuf,size_t maxlen);
void s_bufinit(sbuf_t *sp,int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp,int item);
int sbuf_remove(sbuf_t *sp);

extern sbuf_t s_buf;
extern pool p;
