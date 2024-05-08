#include "register.h"

void register_user(int client_socket, const char *json_body) {

    // Controllo se il body e' un json valido
    /*if (!isValidJson(json_body)) {
        log_to_error("POST", "/utenti", "400", "Il Body non e' un json valido");
        // Invia una risposta HTTP con stato 400 Bad Request se il body JSON è mal formato
        char *response = format_http_response(400, "Il Body non e' un json valido");
        send(client_socket, response, strlen(response), 0);
        free(response);
        return;
    }*/

    // Controllo se il body e' un json valido
    /*if(valida_json(json_body) != 1) {
        log_to_error("POST", "/utenti", "400", "Il Body non e' un json valido");
        perror("Il Body non e' un json valido");
        char *response = format_http_response(400, "Il Body non e' un json valido");
        send(client_socket, response, strlen(response), 0);
        free(response);
        return;
    }*/

    // Connect to JSON server
    int json_socket = connect_to_json_server();
    if (json_socket < 0) {
        perror("Errore nella connessione al server JSON");
        return;
    }

    // Costruisci la richiesta HTTP POST
    char request[4096];
    int request_length = snprintf(request, sizeof(request),
                                  "POST /utenti HTTP/1.1\r\n"
                                  "Host: %s\r\n"
                                  "Content-Type: application/json\r\n"
                                  "Content-Length: %zu\r\n\r\n"
                                  "%s",
                                  "127.0.0.1", strlen(json_body), json_body);

    if (send(json_socket, request, request_length, 0) < 0) {
        log_to_error("POST", "/utenti", "504", "Errore nell'invio della richiesta al server JSON");
        perror("Errore nell'invio della richiesta");
        close(json_socket);
        return;
    }

    // Invia l'intestazione HTTP Content-Type al client
    const char *header = "HTTP/1.1 201 CREATED\r\nContent-Type: application/json\r\n\r\n";
    if (send(client_socket, header, strlen(header), 0) < 0) {
        log_to_error("POST", "/utenti", "505", "Errore nell'invio dei dati al client");
        perror("Errore nell'invio dell'intestazione al client");
        close(client_socket);
        close(json_socket);
        return;
    }

    // Invia il corpo della risposta JSON al client
    const char *response_message = "{\"status\": 201, \"messaggio\": \"Utente registrato con successo\"}";
    if (send(client_socket, response_message, strlen(response_message), 0) < 0) {
        log_to_error("POST", "/utenti", "505", "Errore nell'invio dei dati al client");
        perror("Errore nell'invio dei dati al client");
        close(client_socket);
        close(json_socket);
        return;
    }

    log_to_success("POST", "/utenti", "201");

    // Chiusura delle connessioni
    close(json_socket);
}


int valida_json(const char *json_string) {
    // Verifica che la stringa JSON non sia vuota
    if (json_string == NULL || strlen(json_string) == 0 || *json_string == '\0') {
        return 0;
    }

    // Controlla la presenza di tutti i campi richiesti
    if (strstr(json_string, "\"nome\"") == NULL ||
        strstr(json_string, "\"cognome\"") == NULL ||
        strstr(json_string, "\"nome_utente\"") == NULL ||
        strstr(json_string, "\"data_nascita\"") == NULL ||
        strstr(json_string, "\"codice_fiscale\"") == NULL ||
        strstr(json_string, "\"email\"") == NULL ||
        strstr(json_string, "\"password\"") == NULL ||
        strstr(json_string, "\"tipo_utente\"") == NULL) {
        return 0; // Uno o più campi mancanti
    }

    // Trova il numero di parentesi graffe
    int num_parenthesis = 0;
    const char *parenthesis_char = json_string;
    while (*parenthesis_char != '\0') {
        if (*parenthesis_char == '{' || *parenthesis_char == '}') {
            num_parenthesis++;
        }
        parenthesis_char++;
    }

    // Controlla se il numero di parentesi è un multiplo di 2
    if (num_parenthesis % 2 != 0) {
        return 0; // Il JSON non è formattato correttamente
    }
    
    // Trova il numero di virgolette doppie (")
    int num_quotes = 0;
    const char *quotes_char = json_string;
    while (*quotes_char != '\0') {
        if (*quotes_char == '"') {
            num_quotes++;
        }
        quotes_char++;
    }

    // Controlla se il numero di virgolette doppie è un multiplo di 2
    if (num_quotes % 2 != 0) {
        return 0; // Il JSON non è formattato correttamente
    }

    // Se la stringa JSON supera tutti i controlli, ritorna 1 (JSON valido)
    return 1;
}
