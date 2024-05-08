#ifndef JSON_CONNECTION_MANAGER_H
#define JSON_CONNECTION_MANAGER_H

// Includi le librerie necessarie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//#define JSON_SERVER_IP "127.0.0.1"
#define JSON_SERVER_PORT 3000

int connect_to_json_server();

#endif