#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../connection/json_connection_manager.h"
#include "../log/logging.h"

#ifndef UTENTI_H
#define UTENTI_H


/**
 * @brief Ottiene tutti i dati dalla risorsa "utenti" sul server JSON remoto
 *        e li invia al client che ha fatto la richiesta al web server.
 * 
 * @param client_socket Il socket associato alla connessione con il client che ha fatto la richiesta al web server.
 */
void get_all_utenti(int client_socket);

/**
 * @brief Ottiene tutti i dati di un utente cercandolo nel database secondo un parametro l'ID
 *        e li invia al client che ha fatto la richiesta al web server.
 * 
 * @param client_socket Il socket associato alla connessione con il client che ha fatto la richiesta al web server.
 * @param id L'ID dell'utente da ricercare.
 */
void get_utente_by_id(int client_socket, int id);

#endif