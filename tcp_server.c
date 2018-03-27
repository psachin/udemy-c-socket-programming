/*
  Usage:
  $ make
  $ ./tcp_server

  Execute tcp_client in other terminal
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char server_message[256] = "You have reached the server";

	/* create server socket */
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* socket size */
	socklen_t socksize = sizeof(struct sockaddr_in);

	/* server address */
	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_port = htons(9002), /* or 0 */
		.sin_addr.s_addr = INADDR_ANY, /* INADDR_ANY or inet_addr("127.0.0.1") or inet_addr("192.168.1.1") */
	};

	/* clients address */
	struct sockaddr_in client;

	/* bind socket to IP address */
	 bind(server_socket,
	      (struct sockaddr *) &server,
	      sizeof(server));
	 printf("Server listening on %s:%d\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

	 /* listen(SOCKET, NUMBER_OF_CONN) */
	 listen(server_socket, 5);

	 while (1) {
	     /* accept(SOCKET, STRUCT_SOCK_ADDR, SIZE_OF_SOCKET) */
	     int client_socket = accept(server_socket, (struct sockaddr *) &client, &socksize);

	     /* Client addr info */
	     printf("Client addr: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

	     /* send(SOCKET, DATA, SIZE_OF_MESSAGE) */
	     send(client_socket, server_message, sizeof(server_message), 0);
	 }

	 /* finally close the socket */
	 /* close(server_socket); */
	 return EXIT_SUCCESS;
}
