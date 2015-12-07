/*
  Usage:
  $ make
  $ ./http_client IP_ADDRESS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* to handle string data */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>		/* inet_aton() */

int main(int argc, char *argv[])
{
	char *address;
	address = argv[1];

	/* create client socket */
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* define remote address */
	struct sockaddr_in remote_address = {
		.sin_family = AF_INET,
		.sin_port = htons(80),
	};

	inet_aton(address, &remote_address.sin_addr.s_addr);

	connect(client_socket,
		(struct sockaddr *) &remote_address,
		sizeof(remote_address));

	/* A GET request */
	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];

	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);

	/* print response */
	printf("%s\n", response);

	close(client_socket);
	return 0;
}
