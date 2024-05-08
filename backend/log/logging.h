#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


#ifndef LOGGING_H
#define LOGGING_H


void log_to_success(char method[6], const char endpoint[100], char status[3]);
void log_to_error(char method[6], char endpoint[100], char status[3], char error_description[256]);

#endif
