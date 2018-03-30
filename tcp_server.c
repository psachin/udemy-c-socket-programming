/*
  Usage:
  $ make
  $ ./tcp_server

  Execute tcp_client in other terminal


  Refer below files for upgraded version,
  - https://github.com/psachin/udemy-c-socket-programming/blob/network-programming-assignment-1/tcp_server.c
  - https://github.com/psachin/udemy-c-socket-programming/blob/network-programming-assignment-1/notes.org
*/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char *argv[])
{
	char server_message[256] = "You have reached the server";

	/* create server socket */
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* define server address */
	struct sockaddr_in server_address = {
		.sin_family = AF_INET,
		.sin_port = htons(9002),
		.sin_addr.s_addr = INADDR_ANY,
	};

	/* bind socket to IP address */
	 bind(server_socket,
	      (struct sockaddr *) &server_address,
	      sizeof(server_address));

	 /* listen(SOCKET, NUMBER_OF_CONN) */
	 listen(server_socket, 5);

	 /* accept */
	 int client_socket;
	 /* accept(SOCKET, STRUCT_SOCK_ADDR, SIZE_OF_SOCKET) */
	 client_socket = accept(server_socket, NULL, NULL);

	 /* send(SOCKET, DATA, SIZE_OF_MESSAGE) */
	 send(client_socket, server_message, sizeof(server_message), 0);

	 /* finally close the socket */
	 close(server_socket);
	 return 0;
}
