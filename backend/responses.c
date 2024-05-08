#include "responses.h"

char* format_http_response(int status, char* jsonBody) {
    // Calcola la dimensione necessaria per la risposta HTTP
    size_t httpResponseSize = strlen("HTTP/1.1 XXX \r\n") +
                              strlen("Content-Type: application/json\r\n") +
                              strlen("Content-Length: ") + strlen(jsonBody) +
                              strlen("\r\n\r\n") + 1;

    // Verifica se la dimensione calcolata supera il limite massimo consentito
    if (httpResponseSize > MAX_RESPONSE_SIZE) {
        fprintf(stderr, "Dimensione della risposta HTTP supera il limite massimo consentito\n");
        return NULL; // Restituisci NULL per indicare un errore
    }

    // Alloca memoria per la risposta HTTP
    char *httpResponse = (char *)malloc(httpResponseSize);
    if (httpResponse == NULL) {
        free(httpResponse);
        return NULL; // Gestione dell'errore di allocazione di memoria
    }

    // Costruzione della risposta HTTP
    sprintf(httpResponse, "HTTP/1.1 %d ", status); // Inserisce lo status nella risposta

    // Aggiungi il Content-Type
    strcat(httpResponse, "\r\nContent-Type: application/json\r\n");

    // Aggiungi la lunghezza del corpo della risposta
    sprintf(httpResponse + strlen(httpResponse), "Content-Length: %ld\r\n", strlen(jsonBody));
        
    // Aggiungi fine delle intestazioni e inizio del corpo della risposta
    strcat(httpResponse, "\r\n");
    strcat(httpResponse, jsonBody);

    return httpResponse;
}
