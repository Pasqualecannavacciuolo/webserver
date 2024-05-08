#ifndef HANDLERS_H
#define HANDLERS_H

// Includi le librerie necessarie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <ctype.h>

#include "responses.h"
#include "log/logging.h"

#include "endpoints/libreria.h"
#include "endpoints/prestiti.h"
#include "endpoints/utenti.h"
#include "endpoints/register.h"
// Prototipi delle funzioni

/**
 * Gestisce una richiesta HTTP da un client.
 * Legge la richiesta HTTP dal client, stampa la richiesta ricevuta,
 * genera e invia una risposta HTTP statica al client, e chiude la connessione.
 *
 * @param client_fd Il descrittore del file del client connesso.
 */
void handle_client(int client_fd);


/**
 * Estrae l'endpoint dalla richiesta HTTP.
 *
 * @param request La richiesta HTTP dalla quale estrarre l'endpoint.
 * @param endpoint Puntatore alla stringa in cui memorizzare l'endpoint estratto.
 * @return 0 se l'endpoint è stato estratto con successo, -1 in caso di errore nei parametri o nel parsing.
 *
 * La funzione estrae l'endpoint dalla prima riga della richiesta HTTP. L'endpoint estratto
 * viene copiato nella stringa 'endpoint'.
 *
 * Esempio di utilizzo:
 *   char request[4096];
 *   char endpoint[256];
 *   // Inizializza 'request' con la richiesta HTTP ricevuta
 *   // ...
 *   if (extract_endpoint(request, endpoint) == 0) {
 *       printf("Endpoint richiesto: %s\n", endpoint);
 *   } else {
 *       printf("Errore nell'estrazione dell'endpoint.\n");
 *   }
 */
int extract_endpoint(char *request, char *endpoint);


int extract_method(char *request, char *method);


void remove_non_alpha(char *str);


/**
 * @brief Gestisce la richiesta HTTP in base all'endpoint specificato.
 *
 * Questa funzione riceve l'endpoint della richiesta HTTP e gestisce la richiesta
 * in base all'endpoint specificato. Se l'endpoint corrisponde a "/libreria", viene
 * restituito un elenco di libri in formato JSON. Se l'endpoint è "/", viene
 * restituita una risposta di default. Se l'endpoint non è riconosciuto, viene restituito
 * un messaggio di errore "404 Not Found".
 *
 * @param client_fd Il descrittore del socket per il client che ha inviato la richiesta.
 * @param endpoint L'endpoint della richiesta HTTP da gestire.
 * 
 * @return Void. La funzione invia la risposta al client utilizzando il socket fornito.
 */
void handle_request_by_endpoint(int client_fd, const char *request, const char *method, const char *body);


#endif
