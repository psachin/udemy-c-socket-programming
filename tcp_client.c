#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char *argv[])
{
	/* create a socket */
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	/*
	  AF_INET: Internet socket, this is standard protocol. Address family
	  SOCK_STREAM: Our data will be in a form of stream(TCP) as
	  opposed to datagram(UDP)
	  0: Default protocol-TCP
	 */

	/*
	  Before we connect, we need to specify address for the socket
	 */
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	/* connect */
	int conn_status = connect(network_socket,
				  (struct sockaddr *) &server_address,
				  sizeof(server_address));
	/* check for err */
	if (conn_status == -1) {
		printf("There was an error!\n");
		return conn_status;
	}

	/* recv(): receive data from server */
	char server_response[255];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	/* Print server response */
	printf("Server responded with: %s\n", server_response);

	/* finally close the socket */
	close(network_socket);
	return 0;
}
