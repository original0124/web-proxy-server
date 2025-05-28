#include<my_serve.h>

ssize_t rio_readlineb(rio_t *rp,void *usrbuf,size_t maxlen);
void read_requesthdrs(rio_t *rp)
{
	char buf[MAXLINE];
	rio_readlineb(rp,buf,MAXLINE);
/*	while(strcmp(buf,"\r\n"))
	{
		rio_readlineb(rp,buf,MAXLINE);
		printf("%s",buf);
	}
	return;
*/
	 while (1) {
        if (rio_readlineb(rp, buf, MAXLINE) <= 0)
            break;
        if (!strcmp(buf, "\r\n") || !strcmp(buf, "\n") || buf[0] == '\0')
            break;
        printf("%s", buf);
    }
}

