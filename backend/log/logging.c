#include "logging.h"

void log_to_success(char method[6], const char endpoint[100], char status[3]) {
    char content[256];
    content[0] = '\0'; // Inizializza il buffer (content)

    snprintf(content, sizeof(content), "[%s] - %s - %s\n", method, status, endpoint);

    int fd = open("logs/server.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        return;
    }

    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Errore nella scrittura nel file");
    }

    close(fd);
}

void log_to_error(char method[6], char endpoint[100], char status[3], char error_description[256]) {
    char content[256];
    content[0] = '\0'; // Inizializza il buffer (content)

    if(strlen(method)>6) {
        perror("La dimensione del method non e' corretta");
        return;
    }

    if(strlen(endpoint)>100) {
        perror("La dimensione di endpoint non e' corretta");
        return;
    }

    if(strlen(status)>3) {
        perror("La dimensione di status non e' corretta");
        return;
    }

    if(strlen(error_description)>256) {
        perror("La dimensione di error_description non e' corretta");
        return;
    }

    snprintf(content, sizeof(content), "[%s] - %s - %s: %s\n", method, status, endpoint, error_description);

    int fd = open("logs/errors.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        return;
    }

    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Errore nella scrittura nel file");
        return;
    }

    close(fd);
}
