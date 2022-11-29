  /*
2.                       SERVIDOR
3.                   */
4.                    
5.                   #include <stdio.h>
6.                   #include <stdlib.h>
7.                   #include <string.h>
8.                   #include <winsock.h>
9.                    
10.               #define BACKLOG_MAX 5
11.               #define BUFFER_SIZE 128
12.               #define EXIT_CALL_STRING "#quit"
13.                
14.               int local_socket = 0;
15.               int remote_socket = 0;
16.                
17.               int remote_length = 0;
18.               int message_length = 0;
19.                
20.               unsigned short local_port = 0;
21.               unsigned short remote_port = 0;
22.                
23.               char message[BUFFER_SIZE];
24.                
25.               struct sockaddr_in local_address;
26.               struct sockaddr_in remote_address;
27.                
28.               WSADATA wsa_data;
29.                
30.               /* Exibe uma mensagem de erro e termina o programa */
31.               void msg_err_exit(char *msg)
32.               {
33.                   fprintf(stderr, msg);
34.                   system("PAUSE");
35.                   exit(EXIT_FAILURE);
36.               }
37.                
38.               int main(int argc, char **argv)
39.               {
40.                   // inicia o Winsock 2.0 (DLL), Only for Windows
41.                   if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0)
42.                       msg_err_exit("WSAStartup() failed\n");
43.                
44.                   // criando o socket local para o servidor
45.                   local_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
46.                   if (local_socket == INVALID_SOCKET)
47.                   {
48.                       WSACleanup();
49.                       msg_err_exit("socket() failed\n");
50.                   }
51.                
52.                   printf("Porta local: ");
53.                   scanf("%d", &local_port);
54.                   fflush(stdin);
55.                
56.                   // zera a estrutura local_address
57.                   memset(&local_address, 0, sizeof(local_address));
58.                
59.                   // internet address family
60.                   local_address.sin_family = AF_INET;
61.                
62.                   // porta local
63.                   local_address.sin_port = htons(local_port);
64.                
65.                   // endereco
66.                   local_address.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr("127.0.0.1")
67.                
68.                   // interligando o socket com o endereço (local)
69.                   if (bind(local_socket, (struct sockaddr *) &local_address, sizeof(local_address)) == SOCKET_ERROR)
70.                   {
71.                       WSACleanup();
72.                       closesocket(local_socket);
73.                       msg_err_exit("bind() failed\n");
74.                   }
75.                
76.                   // coloca o socket para escutar as conexoes
77.                   if (listen(local_socket, BACKLOG_MAX) == SOCKET_ERROR)
78.                   {
79.                       WSACleanup();
80.                       closesocket(local_socket);
81.                       msg_err_exit("listen() failed\n");
82.                   }
83.                
84.                   remote_length = sizeof(remote_address);
85.                
86.                   printf("aguardando alguma conexao...\n");
87.                   remote_socket = accept(local_socket, (struct sockaddr *) &remote_address, &remote_length);
88.                   if(remote_socket == INVALID_SOCKET)
89.                   {
90.                       WSACleanup();
91.                       closesocket(local_socket);
92.                       msg_err_exit("accept() failed\n");
93.                   }
94.                
95.                   printf("conexao estabelecida com %s\n", inet_ntoa(remote_address.sin_addr));
96.                   printf("aguardando mensagens...\n");
97.                   do
98.                   {
99.                       // limpa o buffer
100.                   memset(&message, 0, BUFFER_SIZE);
101.            
102.                   // recebe a mensagem do cliente
103.                   message_length = recv(remote_socket, message, BUFFER_SIZE, 0);
104.                   if(message_length == SOCKET_ERROR)
105.                       msg_err_exit("recv() failed\n");
106.            
107.                   // exibe a mensagem na tela
108.                   printf("%s: %s\n", inet_ntoa(remote_address.sin_addr), message);
109.               }
110.               while(strcmp(message, EXIT_CALL_STRING)); // sai quando receber um "#quit" do cliente
111.            
112.               printf("encerrando\n");
113.               WSACleanup();
114.               closesocket(local_socket);
115.               closesocket(remote_socket);
116.            
117.               system("PAUSE");
118.               return 0;
119.           }
