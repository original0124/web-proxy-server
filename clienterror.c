#include<my_serve.h>

ssize_t rio_writen(int fd,void *usrbuf,size_t n);
#define MAXBUF 8192

void clienterror(int fd,char *cause,char *errnum,char *shortmsg,char *longmsg)
{
	char buf[MAXLINE],body[MAXBUF];
	sprintf(body,"<html><title>Tiny Error</title>");
	sprintf(body,"%s<body bgcolor=""ffffff"">\r\n",body);
	sprintf(body,"%s%s:%s\r\n",body,errnum,shortmsg);
	sprintf(body,"%s<p>%s:%s\r\n",body,longmsg,cause);
	sprintf(body,"%s<hr><em>the web server</em>\r\n",body);

	sprintf(buf,"HTTP/1.0 %s %s\r\n",errnum,shortmsg);
	rio_writen(fd,buf,strlen(buf));
	sprintf(buf,"Content-type:text/html\r\n");
	rio_writen(fd,buf,strlen(buf));
	sprintf(buf,"Content-length:%d\r\n\r\n",(int)strlen(body));
	rio_writen(fd,buf,strlen(buf));
	rio_writen(fd,body,strlen(body));
}
