#include<my_serve.h>
void *thread(void *vargp)
{
extern sbuf_t s_buf;
extern pool p;
void doit(int fd);
pthread_detach(pthread_self());
int connfd;
while(1)
{
        connfd=sbuf_remove(&s_buf);
	int i=pthread_self();
	printf("线程%d处理此连接\n",i);
        doit(connfd);
        close(connfd);
}
return NULL;
}
