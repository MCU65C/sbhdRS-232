/**************************************************
file: sbhd.c    (serial bytes hexadecimal dump)
purpose: a tool to print analyse all bytes received on a serial port, especially
         those bytes not representing printable string characters, exit the program by pressing Ctrl-C

compile the project using the accompanying make file, or alternatively
compile just this one executable: gcc sbhd.c rs232.c -Wall -Wextra -o2 -o sbhd
**************************************************/

#include "sbhd.h"

int quit(int exCode)
{
  SetConsoleMode(hStdout, priorMode);                                       /* console to prior mode, before this run */
  SetConsoleTextAttribute(hStdout, info.wAttributes);
  exit(exCode);
}

void strAndHexToConsole(unsigned char *strhex, unsigned char *strstr)
{
  if(nho)   printf("%s%s\n", brcyan, strstr);
  printf("%s\n", strhex);
}

void usage()
{
  printf("\nplease enter a valid port# and baudrate after program name, where 1 = COM1, ie...");
  printf("\n\n./sbhd 1 19200\n./sbhd 1 1000000 --H");
  printf("\n\n--H optional for HEX only output.");
}

void handle_sigint(int sig)
{
  sig = sig;                                                                /* only to prevent compiler 'unused var' */
  quit(2);
}

int main(int argc, char *argv[])
{
  signal(SIGINT, handle_sigint);

  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hStdout, &info);
  GetConsoleMode(hStdout, &priorMode);                                      /* { set windows console mode to */
  SetConsoleMode(hStdout, 7);                                               /*   use UNIX terminal escape codes */

  long br;
  char *end;
  if(argc > 2) {
    br = strtol(argv[2], &end, 10);
    if(br < 300)   { usage();   quit(1); }
  }
  else { usage();   quit(1); }
  boolean rb = 1;                                                           /* toggle red and brblue */
  int i, n,
    cport_nr = 0,                                                           /* /dev/ttyS0 (COM1 on windows) */
    bdrate = br;                                                            /* baud rate from cmd line */

  long p = strtol(argv[1], &end, 10);
  if(p > 0)   cport_nr = p - 1;

  if(argc > 3 && strlen(argv[3]) > 2)
    if(argv[3][0] == '-' && argv[3][1] == '-' && argv[3][2] == 'H')   nho = 0;

  unsigned char buf[4096], strhex[500], strstr[100];

  char mode[]={'8','N','1',0};

  if(RS232_OpenComport(cport_nr, bdrate, mode, 0))   { printf("Can not open comport\n");   return(0); }

  printf("\nListening on port %d, baudrate %d\n", cport_nr + 1, bdrate);

  while(1) {
    n = RS232_PollComport(cport_nr, buf, 4095);

    if(n > 0) {
      if(nho)   printf("%sreceived %i bytes.%s\n", green, n, reset);
      buf[n] = 0;                                                           /* null termed string */

      for(i=0; i < n; i++) {
        int j = i % 32;
        char c = buf[i];
        if(c < 0x20)    sprintf((char *)strstr + j * 2, " .");              /* dot replaces unreadable character */
        else            sprintf((char *)strstr + j * 2, " %c", c);
        if((rb = !rb))  sprintf((char *)strhex + j * 7, "%s%02X", red, c);  /* if does toggle and evaluate bool */
        else            sprintf((char *)strhex + j * 7, "%s%02X", brblue, c);
        if(j == 31)     strAndHexToConsole(strhex, strstr);   
      }

      if(n != 32)   strAndHexToConsole(strhex, strstr);
    }

#ifdef _WIN32
    Sleep(100);
#else
    usleep(100000);                                               /* sleep for 100 milliSeconds */
#endif
  }

  quit(0);
}

