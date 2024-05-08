#include "json_connection_manager.h"

int connect_to_json_server() {
    int json_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (json_socket < 0) {
        perror("Errore nella creazione del socket");
        return -1; 
    }

    struct sockaddr_in json_server_addr;
    json_server_addr.sin_family = AF_INET;
    json_server_addr.sin_port = htons(JSON_SERVER_PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &json_server_addr.sin_addr) <= 0) {
        perror("Indirizzo errato / non supportato");
        close(json_socket);
        return -1;
    }


    if (connect(json_socket, (struct sockaddr *)&json_server_addr, sizeof(json_server_addr)) < 0) {
        perror("Connessione al server fallita");
        close(json_socket);
        return -1;
    }

    return json_socket;
}