#ifndef SERVER_H
#define SERVER_H

// Includi i file di intestazione necessari
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>

#include "handlers.h"
#include "responses.h"
#include "endpoints/libreria.h"
//#include "formatters/libro.h"
#include "endpoints/prestiti.h"
//#include "formatters/prestito.h"
#include "log/logging.h"

#define PROTOCOL_PORT 5193
#define QUEUE_LEN 6
#define MAX_CHILDREN 6
#define CHILD_TIMEOUT_SECONDS 60 // Timeout in secondi per i processi figli inattivi
#define INITIAL_CHILDREN 3      // Numero iniziale di processi figli da creare

int socket_descriptor, client_fd;
pid_t pid;
struct sockaddr_in server_address, client_addr;
socklen_t client_len = sizeof(client_addr);

pid_t children[MAX_CHILDREN] = {0};
int num_children = 0;

/**
 * Gestisce il segnale SIGINT ricevuto per la terminazione del server.
 * La funzione stampa un messaggio di avviso, chiude il descrittore del socket
 * specificato e termina il server con lo stato di uscita EXIT_SUCCESS.
 *
 * @param socket_descriptor Il descrittore del socket da chiudere prima di terminare il server.
 */
void handle_int_signal(int socket_descriptor);

#endif