/***********************************************************************
	Practical1
	daytimetcpcli.c
	from Stevens's Textbook

************************************************************************/
#include	"cc352.h"
#include 	"string.h"
#include <unistd.h>

int
main(int argc, char **argv)
{	
	char name[10];	
	
	int i=0;
	int	sockfd, n;
	char	buff[MAXLINE];
	char	recvline[MAXLINE + 1];
	char 	msg[MAXLINE]="";
	struct sockaddr_in	servaddr;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(8080);	
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	

	while(1){
	
		sockfd = socket(AF_INET, SOCK_STREAM, 0);	
		printf("Type :");
		fgets(msg,MAXLINE,stdin);
		msg[strcspn(msg,"\n")]=0;
		if(strlen(msg)!=0){
			if((strcmp(msg,"exit"))==0){
				
				close(sockfd);
				exit(0);	
			}
	
			//scanf("%s",msg);
			connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	
			snprintf(buff, MAXLINE, "%s",msg);
			write(sockfd, buff, MAXLINE);
			//printf("you types %s",buff);
			
	
		}
		else{
			printf("Type something\n");
		}
	}
	
}



