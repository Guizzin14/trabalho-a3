 /*
2.                       CLIENTE
3.                   */
4.                    
5.                   #include <stdio.h>
6.                   #include <stdlib.h>
7.                   #include <string.h>
8.                   #include <winsock.h>
9.                    
10.               #define BUFFER_SIZE 128
11.               #define EXIT_CALL_STRING "#quit"
12.                
13.               int remote_socket = 0;
14.               int message_length = 0;
15.                
16.               unsigned short remote_port = 0;
17.                
18.               char remote_ip[32];
19.               char message[BUFFER_SIZE];
20.                
21.               struct sockaddr_in remote_address;
22.                
23.               WSADATA wsa_data;
24.                
25.               /* Exibe uma mensagem de erro e termina o programa */
26.               void msg_err_exit(char *msg)
27.               {
28.                   fprintf(stderr, msg);
29.                   system("PAUSE");
30.                   exit(EXIT_FAILURE);
31.               }
32.                
33.               int main(int argc, char **argv)
34.               {
35.                   if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0)
36.                       msg_err_exit("WSAStartup() failed\n");
37.                
38.                   printf("IP do servidor: ");
39.                   scanf("%s", remote_ip);
40.                   fflush(stdin);
41.                
42.                   printf("Porta do servidor: ");
43.                   scanf("%d", &remote_port);
44.                   fflush(stdin);
45.                
46.                   remote_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
47.                   if (remote_socket == INVALID_SOCKET)
48.                   {
49.                       WSACleanup();
50.                       msg_err_exit("socket() failed\n");
51.                   }
52.                
53.                   // preenchendo o remote_address (servidor)
54.                   memset(&remote_address, 0, sizeof(remote_address));
55.                   remote_address.sin_family = AF_INET;
56.                   remote_address.sin_addr.s_addr = inet_addr(remote_ip);
57.                   remote_address.sin_port = htons(remote_port);
58.                
59.                   printf("conectando ao servidor %s...\n", remote_ip);
60.                   if (connect(remote_socket, (struct sockaddr *) &remote_address, sizeof(remote_address)) == SOCKET_ERROR)
61.                   {
62.                       WSACleanup();
63.                       msg_err_exit("connect() failed\n");
64.                   }
65.                
66.                   printf("digite as mensagens\n");
67.                   do
68.                   {
69.                       // limpa o buffer
70.                       memset(&message, 0, BUFFER_SIZE);
71.                
72.                       printf("msg: ");
73.                       gets(message);
74.                       fflush(stdin);
75.                
76.                       message_length = strlen(message);
77.                
78.                       // envia a mensagem para o servidor
79.                       if (send(remote_socket, message, message_length, 0) == SOCKET_ERROR)
80.                       {
81.                           WSACleanup();
82.                           closesocket(remote_socket);
83.                           msg_err_exit("send() failed\n");
84.                       }
85.                   }
86.                   while(strcmp(message, EXIT_CALL_STRING)); // sai quando enviar um "#quit" para o servidor
87.                
88.                   printf("encerrando\n");
89.                   WSACleanup();
90.                   closesocket(remote_socket);
91.                
92.                   system("PAUSE");
93.                   return 0;
94.               }
