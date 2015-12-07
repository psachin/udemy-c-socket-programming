/*
  Usage:
  $ make
  $ ./http_server

  Open the browser's URL: localhost:8001
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* to handle string data */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char *argv[])
{
	/* open html file */
	FILE *html_data;
	html_data = fopen("index.html", "r"); /* page to serve */
	if (!html_data) {
		printf("index.html: Not found!\n");
		return -1;
	}

	char response_data[1024];
	fgets(response_data, 1024, html_data);

	char http_header[4096] = "HTTP/1.1 200 OK\r\n\n";
	strcat(http_header, response_data);

	/* create server socket */
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* define server address */
	struct sockaddr_in server_address = {
		.sin_family = AF_INET,
		.sin_port = htons(8001),
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
	 while(1) {
		 client_socket = accept(server_socket, NULL, NULL);
		 send(client_socket, http_header, sizeof(http_header), 0);
		 printf("HTTP/1.1 OK\n");
		 close(client_socket);
	 }
	 close(server_socket);
	 return 0;
}
