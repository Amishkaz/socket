#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cc352.h"
#include <unistd.h>

pthread_mutex_t mutex;
//char number[MAXLINE]="<p style='background-color:powderblue;' >No Data</p>";
char number[MAXLINE]="G0000000000";

void *piserver(void *arg);
void *httpserver(void *arg);

int main() {
    pthread_t pithread,webthread;
    int return_value;
    char                    number[MAXLINE];

    pthread_create(&pithread, NULL, piserver, NULL);
    pthread_create(&webthread, NULL, httpserver, NULL);

    printf("Main thread waiting for the child thread to complete...\n");

    pthread_join(pithread, NULL);
    pthread_join(webthread, NULL);
   
    printf("Child thread has completed.\n");

    exit(EXIT_SUCCESS);
}
void *httpserver(void *arg){

	int			listenfd, connfd;
	socklen_t		len;
	char	recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr, cliaddr;
	char			buff[MAXLINE];
	char			htmlHeader[MAXLINE];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(8081); /* daytime server */

	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));	
	
	listen(listenfd, LISTENQ);
		
	printf("Listening on port 8081\n");

	//server
	printf("/////////////Welcome to the Chat////////////\n");
	printf("/v1/////////////////////////////////////////\n");
	for ( ; ; ) {
	
	len = sizeof(cliaddr);
	connfd = accept(listenfd, (SA *) &cliaddr, &len);
       	snprintf(htmlHeader,sizeof(htmlHeader),"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n",strlen(number));
	pthread_mutex_lock(&mutex);
	snprintf(buff,sizeof(buff)+sizeof(number),"%s%s\n",htmlHeader,number);
	//printf("%s\n",number);
	pthread_mutex_unlock(&mutex);
	write(connfd,buff,strlen(buff));
	memset(recvline,0,sizeof(recvline));
        close(connfd);
	
	}
	
	pthread_exit(NULL);
}

void *piserver(void *arg) {
   	
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
	printf("Listening on port 8080\n");		

	//server
	printf("/////////////Welcome to the Chat////////////\n");
	printf("/v1/////////////////////////////////////////\n");
	for ( ; ; ) {
	
	
	len2 = sizeof(cliaddr2);
	connfd2 = accept(listenfd2, (SA *) &cliaddr2, &len2);
	pthread_mutex_lock(&mutex);
	read(connfd2, recvline, MAXLINE);
	//snprintf(number,sizeof(number),"<p style='background-color:powderblue;' >test</p>");
	strcpy(number,recvline);
	pthread_mutex_unlock(&mutex);
	fputs(recvline, stdout);
	printf("////////////////////////////////////////////\n");
	
	memset(recvline,0,sizeof(recvline));
        close(connfd2);
	}
	
    pthread_exit(NULL);
}


