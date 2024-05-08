#include "libreria.h"


void get_all_libri(int client_socket) {
    char buffer[4096] = {0};

    int json_socket = connect_to_json_server();
    if (json_socket < 0) {
        perror("Errore nella connessione al server JSON");
        return;
    }

    // Send request to JSON server
    char *request = "GET /libri HTTP/1.1\r\nHost: 127.0.0.1:5555\r\n\r\n";
    if (send(json_socket, request, strlen(request), 0) < 0) {
        log_to_error("GET", "/libreria", "504", "Errore nell'invio della richiesta al server JSON");
        perror("Errore nell'invio della richiesta al server JSON");
        close(json_socket);
        return;
    }

    // Receive response from JSON server and send to client
    ssize_t bytes_received;
    while ((bytes_received = read(json_socket, buffer, sizeof(buffer))) > 0) {
        if (send(client_socket, buffer, bytes_received, 0) < 0) {
            log_to_error("GET", "/libreria", "505", "Errore nell'invio dei dati al client");
            perror("Errore nell'invio dei dati al client");
            close(json_socket);
            return;
        }
        memset(buffer, 0, sizeof(buffer));
    }

    if (bytes_received < 0) {
        log_to_error("GET", "/libreria", "506", "Errore nella lettura della risposta dal server JSON");
        perror("Errore nella lettura della risposta dal server JSON");
    }

    log_to_success("GET", "/libreria", "200");

    // Close sockets
    close(json_socket);
}

