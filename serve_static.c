#include<my_serve.h>
#define MAXBUF 8192
ssize_t rio_writen(int fd,void *usrbuf,size_t n);
void get_filetype(char *filename,char *filetype)
{
	if (strstr(filename,".html"))
		strcpy(filetype,"text/html");
	else if(strstr(filename,".gif"))
		strcpy(filetype,"image/gif");
	else if(strstr(filename,".png"))
		strcpy(filetype,"image/png");
	else if(strstr(filename,".jpg"))
		strcpy(filetype,"image/jpeg");
	else
		strcpy(filetype,"text/plain");
}

void serve_static(int fd,char *filename ,int filesize)
{
	int srcfd;
	char *srcp,filetype[MAXLINE],buf[MAXBUF];
	get_filetype(filename,filetype);
	sprintf(buf,"HTTP/1.0 200 OK\r\n");
	sprintf(buf,"%sServer:Tiny Web Server\r\n",buf);
	sprintf(buf,"%sConnection:close\r\n",buf);
	sprintf(buf,"%sContent-length:%d\r\n",buf,filesize);
	sprintf(buf,"%sContent-type:%s\r\n\r\n",buf,filetype);
	rio_writen(fd,buf,strlen(buf));
	printf("Response headers:\n");
	printf("%s",buf);
	srcfd=open(filename,O_RDONLY,0);
	srcp=mmap(0,filesize,PROT_READ,MAP_PRIVATE,srcfd,0);
	close(srcfd);
	rio_writen(fd,srcp,filesize);
	munmap(srcp,filesize);
}
