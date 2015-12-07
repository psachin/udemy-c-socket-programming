#
#	Makefile for Socket Programming in C
#
# Usage:
# make        # will compile binary specified by BINARY
# make clean  # will remove ALL binaries and objects

.PHONY = all clean

CC = gcc			# compiler to use

LINKERFLAG = -lm
DEBUGFLAG = -Wall -g		# Warning all. -g produce additional
                                # debug msg to be used with gdb

all:	tcp_client.o tcp_server.o http_server.o
	@echo "Linking.."
	${CC} ${LINKERFLAG} tcp_client.o -o tcp_client
	${CC} ${LINKERFLAG} tcp_server.o -o tcp_server
	${CC} ${LINKERFLAG} http_server.o -o http_server

tcp_client.o: tcp_client.c
	@echo "Creating object.."
	${CC} -c $<

tcp_server.o: tcp_server.c
	@echo "Creating object.."
	${CC} -c $<

http_server.o: http_server.c
	@echo "Creating object.."
	${CC} -c $<

clean:
	@echo "Cleaning up..."
	-rm -rvf *~ \#* \%* *.o
	-rm -rvf tcp_client tcp_server http_server
