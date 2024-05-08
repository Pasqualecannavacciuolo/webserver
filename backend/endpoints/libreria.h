#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../connection/json_connection_manager.h"
#include "../log/logging.h"

#ifndef LIBRERIA_H
#define LIBRERIA_H


/**
 * @brief Ottiene tutti i dati dalla risorsa "libri" sul server JSON remoto
 *        e li invia al client che ha fatto la richiesta al web server.
 * 
 * @param client_socket Il socket associato alla connessione con il client che ha fatto la richiesta al web server.
 */
void get_all_libri(int client_socket);

#endif