#include<my_serve.h>
#define SBUFSIZE 1024
int open_listenfd(char *port);
void *thread(void *vargp);
sbuf_t s_buf;
pool p;
void handler(int sig)
{
        while(waitpid(-1,NULL,WNOHANG)>0)
        {
		;
        }
}

int main(int argc,char **argv)
{
	int listenfd,connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;	
	if(argc!=3)
	{
		fprintf(stderr,"usage:%s<port><nthreads>\n",argv[0]);
		exit(1);
	}
	signal(SIGCHLD,handler);
	sem_init(&p.mutex,0,1);
	int thread_num=atoi(argv[2]);
	pthread_t *tid;
	tid=calloc(thread_num,sizeof(pthread_t));
	s_bufinit(&s_buf,SBUFSIZE);
	listenfd=open_listenfd(argv[1]);
	FD_ZERO(&(p.read_set));
	FD_SET(listenfd,&(p.read_set));
	p.nready=-1;
	p.maxfd=listenfd;
	int i;
        for(i=0;i<thread_num;i++)
        {
                pthread_create(tid+i,NULL,thread,NULL);
        }
	while(1)
	{
		p.ready_set=p.read_set;
		p.nready=select(p.maxfd+1,&p.ready_set,NULL,NULL,NULL);
		if(p.nready<0)
		{
			if(errno==EINTR)
			{
				continue;
			}
			perror("select error\n");
			exit(1);
		}
		if(FD_ISSET(listenfd,&p.ready_set))
		{
			clientlen=sizeof(struct sockaddr_storage);
			connfd=accept(listenfd,(SA *)&clientaddr,&clientlen);
			if (connfd < 0) {
                                         perror("accept 失败\n");
                                         continue;
                                         }
			if(connfd>p.maxfd)
			{
				p.maxfd=connfd;
			}
			sem_wait(&p.mutex);
			FD_SET(connfd,&p.read_set);
			sem_post(&p.mutex);
			p.nready--;
		}
		for(i=0;p.nready>0;i++)
		{
			if(FD_ISSET(i,&p.ready_set)&&i!=listenfd)
			{
				sbuf_insert(&s_buf,i);
				p.nready--;
				FD_CLR(i,&p.read_set);
			}
		}		
	}
}
