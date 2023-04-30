/**************************************************
file: demo_tx.c
purpose: simple demo that transmits characters to the serial port
and print them on the screen, exit the program by pressing Ctrl-C

compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx
**************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"


int main()
{                        /* nr = 0 is /dev/ttyS0 (COM1 on windows), bdrate 9600 is 9600 baud */
  int i=0, cport_nr=1, bdrate=9600;

  char mode[]={'8','N','1',0}, str[2][512];


  strcpy(str[0], "The quick brown fox jumped over the lazy dog.\n");

  strcpy(str[1], "Happy serial programming!\n");

  if(RS232_OpenComport(cport_nr, bdrate, mode, 0)) {
    printf("Can not open comport\n");

    return(0);
  }

  while(1) {
    RS232_cputs(cport_nr, str[i]);
    printf("sent: %s", str[i]);   if(i)   printf("\n");

#ifdef _WIN32
    Sleep(200);
#else
    usleep(200000);  /* sleep for 0.2 Second */
#endif

    i++;

    i %= 2;
  }

  return(0);
}