#
# author: MCU65C         email: mcu65c@outlook.com
#

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -Wformat-nonliteral -Wformat-security -Wtype-limits -O2

objects = rs232.o

all: sbhd sbsend

sbhd : $(objects) sbhd.o
	$(CC) $(objects) sbhd.o -o sbhd

sbsend : $(objects) sbsend.o
	$(CC) $(objects) sbsend.o -o sbsend

sbhd.o : sbhd.c rs232.h
	$(CC) $(CFLAGS) -c sbhd.c -o sbhd.o

sbsend.o : sbsend.c rs232.h
	$(CC) $(CFLAGS) -c sbsend.c -o sbsend.o

rs232.o : rs232.h rs232.c
	$(CC) $(CFLAGS) -c rs232.c -o rs232.o

clean :
	$(RM) sbhd sbsend $(objects) sbhd.o sbsend.o rs232.o


