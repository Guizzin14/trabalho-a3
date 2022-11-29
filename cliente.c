#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_IP "193.136.93.147"	
#define SERVERPORT "4950" // porto
#define MAXBUFLEN 100

int main(int argc, char *argv[])
{
int num =0;
int sockfd;
struct addrinfo hints, *servinfo, *p;
int rv;
int numbytes;
char mensagem[MAXBUFLEN];
char temp [33];

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_DGRAM;

if ((rv = getaddrinfo(SERVER_IP, SERVERPORT, &hints, &servinfo)) != 0) {
 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
 return 1;
}

// pesquisa os resultados e cria a socket
for(p = servinfo; p != NULL; p = p->ai_next) {
 if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
	 perror("talker: socket");
	 continue;
 }

 break;
 }

if (p == NULL) {
 fprintf(stderr, "clinete: failed to bind socket\n");
 return 2;
}

for(num=0; num<100; num++) {
temp[0]='\0';
mensagem[0]='\0';
strncpy(mensagem, "mensgem num x ", 14);
snprintf(temp, 33, "%d", num);
strncpy(mensagem+14, temp,33);
//mensagem[46]='\0';
printf("%s \n", mensagem);

if ((numbytes = sendto(sockfd, mensagem, strlen(mensagem), 0, p->ai_addr, p->ai_addrlen)) == -1) {
perror("cliente: a enviar");
exit(1);
}

//freeaddrinfo(servinfo);
}
close(sockfd);

return 0;
}
