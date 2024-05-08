#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_RESPONSE_SIZE 8192 // Dimensione massima consentita per la risposta HTTP

#ifndef RESPONSES_H
#define RESPONSES_H


/**
 * Formatta una risposta HTTP con il corpo JSON specificato.
 * La funzione prende il corpo JSON come parametro e genera una stringa che rappresenta
 * una risposta HTTP con intestazioni appropriate e il corpo JSON specificato.
 *
 * @param jsonBody Il corpo JSON da includere nella risposta HTTP.
 * @param status Lo status della risposta HTTP.
 * @return Puntatore a una stringa allocata dinamicamente contenente la risposta HTTP formattata.
 *         Il chiamante è responsabile di liberare la memoria allocata.
 *         Se si verifica un errore durante l'allocazione di memoria, la funzione restituirà NULL.
 */
char* format_http_response(int status, char* jsonBody);

#endif
