#ifndef sbhd_INCLUDED
#define sbhd_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

unsigned char red[] =    { 27, '[', '3', '1', 'm', 0 }, reset[] =   { 27, '[', '0', 'm', 0 };
unsigned char green[] =  { 27, '[', '3', '2', 'm', 0 }, brcyan[] =  { 27, '[', '9', '6', 'm', 0 }; 
unsigned char brblue[] = { 27, '[', '9', '4', 'm', 0 }, brwhite[] = { 27, '[', '9', '7', 'm', 0 };

CONSOLE_SCREEN_BUFFER_INFO info;
unsigned long priorMode;
HANDLE hStdout;
boolean nho = 1;                                                            /* nho true, for not hex only, will output */
                                                                            /* count message and printable characters */
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
