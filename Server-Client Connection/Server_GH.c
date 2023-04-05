/* Server code */

#include<stdio.h>
#include<sys/socket.h>
#include"apue.h"
#include<arpa/inet.h>
#include<sys/types.h>

#define BUF_SIZE 1024
#define LISTEN_PORT 8080

int main(int argc, char *argv[])
{ 
	int sock_listen, sock_recv;
	int i, addr_size, bytes_received;
	int incoming_len;
	int recv_msg_size;
	int client_socket[30];
	int max_clients = 30;
	struct sockaddr_in my_addr, recv_addr;
	int select_ret;
	int max_sd, sd;
	int activity;
	
	fd_set readfds;

	struct timeval timeout={0,0};	
	struct sockaddr remote_addr;
	
	char buf[BUF_SIZE];
	
	for(int i = 0; i < max_clients; i++){
	
	   client_socket[i] = 0;

	}

	/* create socket for listening */
	sock_listen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_listen < 0)
	{
		printf("socket() failed\n");
		exit(0);
	}

	/* make local address structure */
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons((unsigned short)LISTEN_PORT);

	/* bind socket to the local address */
	i = bind(sock_listen, (struct sockaddr *) &my_addr, sizeof(my_addr));
	if (i < 0)
	{
		printf("bind() failed\n");
		exit(0);
	}

	/* listen */
	i = listen(sock_listen, 5);
	if (i < 0)
	{
		printf("listen() failed\n");
		exit(0);
	}

	/* get new socket to receive data on */
	addr_size = sizeof(recv_addr);
	// sock_recv = accept(sock_listen, (struct sockaddr *) &recv_addr, &addr_size);

	while (1)
	{
	
		FD_ZERO(&readfds);
		
		FD_SET(sock_listen, &readfds);
		
		max_sd = sock_listen;
		
		for(int i = 0; i < max_clients; i++){
		
		   sd = client_socket[i];
		   
		   if(sd > 0){
		   
		      FD_SET(sd, &readfds);
		  
		   }
		   
		   if(sd > max_sd){
		   
		      max_sd = sd;
		   
		   }   
		
		}
		
		activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
		
		if((activity < 0) && (errno != EINTR)){
		
		   printf("select error");
		
		}
		
		if(FD_ISSET(sock_listen, &readfds)){
		
		   if((sock_recv = accept(sock_listen, (struct sockaddr *) &recv_addr, &addr_size)) < 0){
		   
		      perror("accept");
		      exit(EXIT_FAILURE);
		   
		   
		   }
		   
		   bytes_received = recv(sock_recv, buf, BUF_SIZE, 0);
		   buf[bytes_received] = 0;
		   printf("Received: %s\n", buf);
		   if(strcmp(buf, "shutdown") == 0){
		   
		      break;
		   
		   }
		
		}
		
	}

	close(sock_recv);
	close(sock_listen);
}

/*

// Client code

#define BUF_SIZE 1024
#define SERVER_IP "192.168.0.1"
#define SERVER_PORT 8080

int main(int argc, char *argv[])
{
	int sock_send;
	int i;
	int send_len, bytes_sent;

	char text[80], buf[BUF_SIZE];

	struct sockaddr_in addr_send;

	/* create socket for sending data 
	sock_send = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_send < 0)
	{
		printf("socket() failed\n");
		exit(0);
	}

	/* create socket address structure to connect to
	memset(&addr_send, 0, sizeof(addr_send));
	addr_send.sin_family = AF_INET;
	addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
	addr_send.sin_port = htons((unsigned short) SERVER_PORT);

	/* connect to server
	i = connect(sock_send, (struct sockaddr *) &addr_send, sizeof(addr_send));	
	if (i < 0)
	{
		printf("connect() failed\n");
		exit(0);
	}

	while (1)
	{
		/* send some data
		printf("Send? ");
		scanf("%s", text);
		if (strcmp(text, "quit") == 0)
			break;

		strcpy(buf, text);
		send_len = strlen(text);
		bytes_sent = send(sock_send, buf, send_len, 0);
	}

	close(sock_send);
}

*/
	
