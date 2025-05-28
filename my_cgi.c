#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE 8192
#include<my_serve.h>

int main(int argc,char **argv)
{
	struct addrinfo *p,*listp,hints;
	char buf[MAXLINE]="",content[MAXLINE],tmpbuf[MAXLINE];
	int rc,flags;
	argv[1]=getenv("QUERY_STRING");
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;
	if((rc=getaddrinfo(argv[1],NULL,&hints,&listp))!=0)
	{
	fprintf(stderr,"getaddrinfo error:%s\n",gai_strerror(rc));
	exit(0);
	}	
	flags=NI_NUMERICHOST;
	sprintf(content,"<html><title>欢迎使用DNS解析服务</title>");
        sprintf(content,"%s该域名对应的IP地址是:\r\n<body>",content);
	for(p=listp;p;p=p->ai_next)
	{
		getnameinfo(p->ai_addr,p->ai_addrlen,tmpbuf,MAXLINE,NULL,0,flags);
		sprintf(buf,"%s\r\n%s\r\n",buf,tmpbuf);
	}
	sprintf(buf,"%s\r\n</body>",buf);
	printf("Connection:close\r\n");
        printf("Content-length:%d\r\n",(int)strlen(content)+(int)strlen(buf));
        printf("Content-type:text/html\r\n\r\n");
	printf("%s",content);
	printf("%s",buf);
	fflush(stdout);
	freeaddrinfo(listp);
	exit(0);
}
