#include<my_serve.h>

int open_clientfd(char *hostname,char *port)
{
	int clientfd;
	struct addrinfo hints,*listp,*p;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_NUMERICSERV;
	hints.ai_flags |=AI_ADDRCONFIG;
	getaddrinfo(hostname,port,&hints,&listp);
	for(p=listp;p;p=p->ai_next)
	{
		if(clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol)<0)
		{
			continue;
		}
		if(connect(clientfd,p->ai_addr,p->ai_addrlen)!=-1)
		{
			break;
		}
		close(clientfd);
	}
	freeaddrinfo(listp);
	if(!p)
	{
		return -1;
	}
	else
		return clientfd;
}
