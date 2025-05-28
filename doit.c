#include<my_serve.h>

void clienterror(int fd,char *cause,char *errnum,char *shortmsg,char *longmsg);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri,char *filename,char *cgiargs);
void serve_static(int fd,char *filename,int filesize);
void serve_dynamic(int fd,char *filename,char *cgiargs);


void doit(int fd)
{
	int is_static;
	struct stat sbuf;
	char buf[MAXLINE],method[MAXLINE],uri[MAXLINE],version[MAXLINE];
	char filename[MAXLINE],cgiargs[MAXLINE];
	rio_t rio;
	rio_readinitb(&rio,fd);
	printf("准备读取请求头...\n");
	rio_readlineb(&rio,buf,MAXLINE);
	printf("%s",buf);
	sscanf(buf,"%s %s %s",method,uri,version);
	if(strcasecmp(method,"GET"))
	{
		clienterror(fd,method,"501","not implemented","tiny does not implement this method");
		return;
	}
	read_requesthdrs(&rio);
	is_static=parse_uri(uri,filename,cgiargs);
	if(stat(filename,&sbuf)<0)
	{
		clienterror(fd,filename,"404","not found","tiny couldn't find this file");
		return;
	}
	if(is_static)
	{
		if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR&sbuf.st_mode))
				{
					clienterror(fd,filename,"403","forbidde","tiny couldn't read the file");
					return;

				}
		serve_static(fd,filename,sbuf.st_size);
	}
	else
	{
		if(!(S_ISREG(sbuf.st_mode))||!(S_IXUSR&sbuf.st_mode))
		{
			clienterror(fd,filename,"403","forbidden","tiny coundn't run the CGI program");
			return;
		}
		serve_dynamic(fd,filename,cgiargs);
	}
}
