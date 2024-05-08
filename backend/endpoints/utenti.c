#include "utenti.h"


void get_all_utenti(int client_socket) {
    char buffer[4096] = {0};

    // Connect to JSON server
    int json_socket = connect_to_json_server();
    if (json_socket < 0) {
        perror("Errore nella connessione al server JSON");
        return;
    }

    // Send request to JSON server
    char request[100];
    sprintf(request, "GET /utenti HTTP/1.1\r\nHost: %s:%d\r\n\r\n", "127.0.0.1", JSON_SERVER_PORT);
    if (send(json_socket, request, strlen(request), 0) < 0) {
        log_to_error("GET", "/utenti", "504", "Errore nell'invio della richiesta al server JSON");
        perror("Errore nell'invio della richiesta al server JSON");
        close(json_socket);
        return;
    }

    // Receive response from JSON server and send to client
    ssize_t bytes_received;
    while ((bytes_received = read(json_socket, buffer, sizeof(buffer))) > 0) {
        if (send(client_socket, buffer, bytes_received, 0) < 0) {
            log_to_error("GET", "/utenti", "505", "Errore nell'invio dei dati al client");
            perror("Errore nell'invio dei dati al client");
            close(json_socket);
            return;
        }
        memset(buffer, 0, sizeof(buffer));
    }

    if (bytes_received < 0) {
        log_to_error("GET", "/utenti", "506", "Errore nella lettura della risposta dal server JSON");
        perror("Errore nella lettura della risposta dal server JSON");
    }

    log_to_success("GET", "/utenti", "200");

    // Close sockets
    close(json_socket);
    close(client_socket);
}


void get_utente_by_id(int client_socket, int id) {
    char buffer[4096] = {0};
    char endpoint[100];
    snprintf(endpoint, sizeof(endpoint), "/utenti/%d", id);

    // Connect to JSON server
    int json_socket = connect_to_json_server();
    if (json_socket < 0) {
        perror("Errore nella connessione al server JSON");
        return;
    }

    // Send request to JSON server
    char request[100];
    sprintf(request, "GET /utenti/%d HTTP/1.1\r\nHost: %s:%d\r\n\r\n", id, "127.0.0.1", JSON_SERVER_PORT);
    if (send(json_socket, request, strlen(request), 0) < 0) {
        log_to_error("GET", (char *) endpoint, "504", "Errore nell'invio della richiesta al server JSON");
        perror("Errore nell'invio della richiesta al server JSON");
        close(json_socket);
        return;
    }

    // Receive response from JSON server and send to client
    ssize_t bytes_received;
    while ((bytes_received = read(json_socket, buffer, sizeof(buffer))) > 0) {
        if (send(client_socket, buffer, bytes_received, 0) < 0) {
            log_to_error("GET", (char *) endpoint, "505", "Errore nell'invio dei dati al client");
            perror("Errore nell'invio dei dati al client");
            close(json_socket);
            return;
        }
    }

    if (bytes_received < 0) {
        log_to_error("GET", (char *) endpoint, "506", "Errore nella lettura della risposta dal server JSON");
        perror("Errore nella lettura della risposta dal server JSON");
    } else {
        // Controllo se l'utente non e' stato trovato nel database
        if (strstr(buffer, "404 Not Found") != NULL) {
            log_to_error("GET", (char *) endpoint, "404", "Utente non trovato nel database");
        } else {
            log_to_success("GET", (char *) endpoint, "200");
        }
    }
    
    // Resetto il buffer
    memset(buffer, 0, sizeof(buffer));

    // Close sockets
    close(json_socket);
    close(client_socket);
}