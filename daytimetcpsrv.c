/*********************************************************************
	Practical1
	daytimetcpsrv.c
	From Stevens' Textbook

*********************************************************************/
#include	"cc352.h"
#include <unistd.h>


int
main(int argc, char **argv)
{
	char	recvline[MAXLINE + 1];
	char			buff[MAXLINE];
	
	int			listenfd2, connfd2;
	socklen_t		len2;
	struct sockaddr_in	servaddr2, cliaddr2;

	listenfd2 = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr2, sizeof(servaddr2));
	servaddr2.sin_family      = AF_INET;
	servaddr2.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr2.sin_port        = htons(8080);

	bind(listenfd2, (SA *) &servaddr2, sizeof(servaddr2));	
	
	listen(listenfd2, LISTENQ);
		

	//server
	printf("/////////////Welcome to the Chat////////////\n");
	printf("/v1/////////////////////////////////////////\n");
	for ( ; ; ) {
	
	
	len2 = sizeof(cliaddr2);
	connfd2 = accept(listenfd2, (SA *) &cliaddr2, &len2);
	read(connfd2, recvline, MAXLINE);
	
	
	fputs(recvline, stdout);
	printf("////////////////////////////////////////////\n");
	
	memset(recvline,0,sizeof(recvline));
        close(connfd2);
	}
	
}



