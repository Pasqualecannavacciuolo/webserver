#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../connection/json_connection_manager.h"
#include "../log/logging.h"
#include "../responses.h"

#ifndef REGISTER_H
#define REGISTER_H


void register_user(int client_socket, const char *json_body);

/**
 * @brief Verifica la validità di una stringa JSON.
 * 
 * Questa funzione analizza una stringa JSON per verificare se contiene tutti i campi richiesti
 * e se è formattata correttamente.
 * 
 * @param json_string La stringa JSON da validare.
 * 
 * @return 1 se la stringa JSON è valida, altrimenti 0.
 * 
 * @note La funzione considera una stringa JSON valida se contiene tutti i seguenti campi:
 *       "nome", "cognome", "nome_utente", "data_nascita", "codice_fiscale", "email",
 *       "password", "tipo_utente".
 *       Inoltre, esegue un controllo basilare sulla formattazione della stringa JSON,
 *       verificando che il numero di virgolette doppie sia corretto.
 *       Questa funzione non esegue controlli approfonditi sui valori dei campi.
 */
int valida_json(const char *json_string);

#endif