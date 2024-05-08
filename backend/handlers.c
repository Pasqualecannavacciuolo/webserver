#include "handlers.h"

void handle_client(int client_fd)
{
    // IMPORTANTE - assegnare un buffer sufficientemente grande per evitare effetti indesiderati (stampe caratteri non voluti es: �X�)
    char buffer[4096];
    ssize_t bytes_received;

    // Leggi la richiesta HTTP dal client
    bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
        perror("Errore durante la lettura della richiesta HTTP");
        close(client_fd);
        return;
    }

    // Aggiungi il terminatore di stringa al buffer
    buffer[bytes_received] = '\0';

    // Stampa la richiesta HTTP ricevuta dal client
    printf("Richiesta HTTP ricevuta:\n%s", buffer);
    

    // Estrai il metodo HTTP dalla richiesta
    char method[16]; // Metodo HTTP (GET, POST, ecc.)
    char buffer_copy2[4096]; // Copia del buffer originale
    strncpy(buffer_copy2, buffer, sizeof(buffer_copy2)); // Copia il buffer originale nella copia
    if (extract_method(buffer_copy2, method) == -1)
    {
        fprintf(stderr, "Errore nel parsing della richiesta HTTP\n");
        close(client_fd);
        return;
    }

    // Analizza la richiesta HTTP per estrarre l'endpoint
    char endpoint[256]; // Assumendo una lunghezza massima per l'endpoint
    char buffer_copy[4096]; // Copia del buffer originale
    strncpy(buffer_copy, buffer, sizeof(buffer_copy)); // Copia il buffer originale nella copia
    if (extract_endpoint(buffer_copy, endpoint) == -1)
    {
        fprintf(stderr, "Errore nel parsing della richiesta HTTP\n");
        close(client_fd);
        return;
    }

    // Estrai il metodo HTTP dalla richiesta
    // Trova la fine delle intestazioni HTTP
    char *end_of_headers = strstr(buffer, "\r\n\r\n"); // Trova la fine delle intestazioni HTTP
    if (end_of_headers == NULL)
    {
        printf("Nessun terminatore delle intestazioni trovato\n");
        return; // Non è stata trovata la fine delle intestazioni, quindi non c'è un body
    }

    // Trova l'inizio del corpo della richiesta
    char *start_of_body = end_of_headers + 4; // Passa oltre il terminatore di fine intestazioni

    // Alloca memoria per il corpo e copialo
    int body_length = bytes_received - (start_of_body - buffer); // Calcola la lunghezza del body
    char *body = (char *)malloc(body_length + 1);
    if (body == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione della memoria\n");
        exit(EXIT_FAILURE);
    }

    // Copia il corpo dalla posizione di start_of_body
    memcpy(body, start_of_body, body_length);
    body[body_length] = '\0'; // Assicurati che il body sia terminato correttamente

    handle_request_by_endpoint(client_fd, endpoint, method, body);

    // Chiudi la connessione con il client
    close(client_fd);
}

void handle_request_by_endpoint(int client_fd, const char *endpoint, const char *method, const char *body)
{   

    // Rimuove gli spazi bianchi dal metodo HTTP
    char cleaned_method[16]; // Metodo HTTP senza spazi bianchi
    strcpy(cleaned_method, method);
    remove_non_alpha(cleaned_method);
    
    // Controlla il metodo HTTP per distinguere tra GET e POST
    if (strcmp(cleaned_method, "POST") == 0)
    {
        // Se il metodo è POST, possiamo gestire la richiesta POST in base all'endpoint
        if (strcmp(endpoint, "/utenti") == 0)
        {
            // Registra l'utente utilizzando la funzione register_user
            register_user(client_fd, body);
        }
        else
        {
            // Altri endpoint non supportati per il metodo POST
            log_to_error("POST", (char *) endpoint, "404", "Endpoint non supportato per il metodo POST");
            char *response = format_http_response(404, "Endpoint non supportato per il metodo POST");
            send(client_fd, response, strlen(response), 0);
            free(response);
            close(client_fd);
            return;
        }
    }
    else if (strcmp(cleaned_method, "GET") == 0)
    {
        // Se il metodo è GET, possiamo gestire la richiesta GET in base all'endpoint
        
        // Gestione degli endpoint per il metodo GET
        if (strcmp(endpoint, "/libreria") == 0)
        {
            get_all_libri(client_fd);
        }
        else if (strcmp(endpoint, "/prestiti") == 0)
        {
            get_all_prestiti(client_fd);
        }
        else if (strcmp(endpoint, "/utenti") == 0)
        {
            get_all_utenti(client_fd);
        }
        else if (strncmp(endpoint, "/utenti/", 8) == 0)
        {
            // Gestione per endpoint "/utenti/{id}"
            int id = atoi(endpoint + 8);
            if (id > 0)
            {
                get_utente_by_id(client_fd, id);
            }
            else
            {
                // ID non valido
                char *response = format_http_response(400, "ID utente non valido");
                send(client_fd, response, strlen(response), 0);
                log_to_error("GET", (char *)endpoint, "400", "ID utente non valido");
                free(response);
            }
        }
        else
        {
            // Nessun endpoint corrispondente trovato per il metodo GET
            char *response = format_http_response(404, "Nessun endpoint corrispondente trovato per il metodo GET");
            send(client_fd, response, strlen(response), 0);
            log_to_error("GET", (char *)endpoint, "404", "Nessun endpoint corrispondente trovato per il metodo GET");
            free(response);
        }
    }
    
}


int extract_endpoint(char *request, char *endpoint)
{    
    // Controllo degli argomenti
    if (request == NULL || endpoint == NULL)
    {
        return -1; // Errore nei parametri
    }

    // Cerca la prima riga della richiesta HTTP
    char *first_line = strtok(request, "\r\n");
    if (first_line == NULL)
    {
        return -1; // Errore nel parsing della richiesta HTTP
    }

    // Estrae il metodo e l'endpoint dalla prima riga
    char method[16], path[256];
    if (sscanf(first_line, "%s %s", method, path) != 2)
    {
        return -1; // Errore nel parsing della riga della richiesta
    }

    // Validazione dell'endpoint per prevenire buffer overflow
    size_t path_length = strlen(path);
    if (path_length >= 256)
    {
        return -1; // Errore: lunghezza dell'endpoint troppo lunga
    }

    // Copia l'endpoint estratto nella stringa 'endpoint'
    strncpy(endpoint, path, path_length);
    endpoint[strlen(path)] = '\0'; // Assicura che la stringa sia terminata correttamente

    return 0; // Parsing della richiesta HTTP completato con successo
}


int extract_method(char *request, char *method) {
    // Controllo degli argomenti
    if (request == NULL || method == NULL) {
        return -1; // Errore nei parametri
    }

    // Cerca lo spazio per separare il metodo dall'endpoint
    size_t i;
    for (i = 0; request[i] != ' ' && i < 16; ++i) {
        method[i] = request[i];
    }
    method[i] = '\0'; // Termina il metodo con il terminatore null

    // Assicurati che ci sia un terminatore di stringa anche se non viene raggiunta la lunghezza massima
    if (i == 16 && request[i] != ' ') {
        method[15] = '\0';
    }

    return 0; // Parsing della richiesta HTTP completato con successo
}


void remove_non_alpha(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        // Se il carattere corrente è alfanumerico o uno spazio, lo mantieni nella stringa
        if (isalnum(str[i]) || isspace(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Aggiungi il terminatore di stringa
}