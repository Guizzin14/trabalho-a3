
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

#define MYPORT "4950" // porto para os sensores se conectarem
#define MYPORT1 "4951"
#define MYPORT2 "4952"
#define MAX_EST 10
#define MAXBUFLEN 100
// obter o endereço do socket, ipv4 ou v6
void *get_in_addr(struct sockaddr *sa)
{
if (sa->sa_family == AF_INET) {
 return &(((struct sockaddr_in*)sa)->sin_addr);
}

return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
int sockfd;
int sockfd1, sockfd2; //a
struct addrinfo hints, *servinfo, *p;
struct addrinfo hints1, *servinfo1, *p1; //a
struct addrinfo hints2, *servinfo2, *p2; //a

int rv;
int rv1, rv2; //a
int numbytes;
int numbytes1, numbytes2; //a
struct sockaddr_storage their_addr;
struct sockaddr_storage their_addr1; //a
struct sockaddr_storage their_addr2; //a
char buf[MAXBUFLEN];
char buf1[MAXBUFLEN]; //a
char buf2[MAXBUFLEN]; //a
socklen_t addr_len;
socklen_t addr_len1; //a
socklen_t addr_len2; //a

//char s[iNET6_ADDRSTRLEN];

FILE *fich;

char sopo1[12]="socket 1: ";
char sopo2[12]="socket 2: ";
char sopo3[12]="socket 3: ";
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_DGRAM;
hints.ai_flags = AI_PASSIVE;
memset(&hints1, 0, sizeof hints1);
hints1.ai_family = AF_UNSPEC;
hints1.ai_socktype = SOCK_DGRAM;
hints1.ai_flags = AI_PASSIVE;

memset(&hints2, 0, sizeof hints2);
hints2.ai_family = AF_UNSPEC;
hints2.ai_socktype = SOCK_DGRAM;
hints2.ai_flags = AI_PASSIVE;

if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
 return 1;
}
if ((rv1 = getaddrinfo(NULL, MYPORT1, &hints1, &servinfo1)) != 0) {
 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv1));
 return 1;
}

if ((rv2 = getaddrinfo(NULL, MYPORT2, &hints2, &servinfo2)) != 0) {
 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv2));
 return 1;
}

// bind no primeiro resultado que encontrar
for(p = servinfo; p != NULL; p = p->ai_next) {
 if ((sockfd = socket(p->ai_family, p->ai_socktype,
		 p->ai_protocol)) == -1) {
	 perror("listener: socket");
	 continue;
 }

 if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
	 close(sockfd);
	 perror("listener: bind");
	 continue;
 }

 break;
}


 // bind no primeiro resultado que encontrar
for(p1 = servinfo1; p1 != NULL; p1 = p1->ai_next) {
 if ((sockfd1 = socket(p1->ai_family, p1->ai_socktype,
		 p1->ai_protocol)) == -1) {
	 perror("listener: socket");
	 continue;
 }

 if (bind(sockfd1, p1->ai_addr, p1->ai_addrlen) == -1) {
	 close(sockfd1);
	 perror("listener: bind");
	 continue;
 }

 break;
}

 // bind no primeiro resultado que encontrar
for(p2 = servinfo2; p2 != NULL; p2 = p2->ai_next) {
 if ((sockfd2 = socket(p2->ai_family, p2->ai_socktype,
		 p2->ai_protocol)) == -1) {
	 perror("listener: socket");
	 continue;
 }

 if (bind(sockfd2, p2->ai_addr, p2->ai_addrlen) == -1) {
	 close(sockfd2);
	 perror("listener: bind");
	 continue;
 }

 break;
}


if (p == NULL) {
 fprintf(stderr, "listener: failed to bind socket\n");
 return 2;
}


if (p1 == NULL) {
 fprintf(stderr, "listener: failed to bind socket\n");
 return 2;
}


if (p2 == NULL) {
 fprintf(stderr, "listener: failed to bind socket\n");
 return 2;
}

freeaddrinfo(servinfo);

freeaddrinfo(servinfo1);
freeaddrinfo(servinfo2);

printf("listener: waiting to recvfrom...\n");


while(1) {
fich = fopen("test0", "a");

addr_len = sizeof their_addr;
if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
perror("recvfrom");
exit(1);
}
buf[numbytes] = '\0';
fprintf(fich, "%s %s\n",sopo1, buf);
printf("%s %s\n",sopo1, buf);



addr_len1 = sizeof their_addr1;
if ((numbytes1 = recvfrom(sockfd1, buf1, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr1, &addr_len1)) == -1) {
perror("recvfrom");
exit(1);
}
buf1[numbytes1] = '\0';
fprintf(fich, "%s %s\n", sopo2, buf1);

addr_len2 = sizeof their_addr2;
if ((numbytes2 = recvfrom(sockfd2, buf2, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr2, &addr_len2)) == -1) {
perror("recvfrom");
exit(1);
}
buf2[numbytes2] = '\0';
fprintf(fich, "%s %s\n",sopo3, buf2);

fclose(fich);
}


close(sockfd);
return 0;
}
