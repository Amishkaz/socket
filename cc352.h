#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#define	MAXLINE	40960
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001  // replace this with your assigned port number
#define	SA	struct sockaddr
