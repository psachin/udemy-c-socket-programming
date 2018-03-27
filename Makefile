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

BINARIES = tcp_client tcp_server

all:	${BINARIES}

%: %.o
	@echo "Compiling.."
	${CC} ${LINKERFLAG} $< -o $*

%.o: %.c
	@echo "Creating objects.."
	${CC} -c $<

clean:
	@echo "Cleaning up..."
	-rm -rvf *~ \#* \%* *.o
	-rm -rvf ${BINARIES}
