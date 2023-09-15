#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cc352.h"
#include <unistd.h>

int main(){
  int                     listenfd, connfd;
  socklen_t               len;
  char    recvline[MAXLINE + 1];
  struct sockaddr_in      servaddr, cliaddr;
  char                    buff[MAXLINE];
  char                    htmlHeader[MAXLINE];
  char number[MAXLINE]="G1011010110";
  
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
  	snprintf(buff,sizeof(buff)+sizeof(number),"%s%s\n",htmlHeader,number);
  	//printf("%s\n",number);
  	write(connfd,buff,strlen(buff));
  	memset(recvline,0,sizeof(recvline));
  	close(connfd);
  
  }

}
