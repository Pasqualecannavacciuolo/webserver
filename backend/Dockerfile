# Usa un'immagine di base con un ambiente C preinstallato
FROM gcc:latest

# Imposta la directory di lavoro
WORKDIR /usr/src/server

# Copia il codice sorgente all'interno dell'immagine
#COPY db.json /usr/src/server/
COPY server.c server.h /usr/src/server/
COPY handlers.c handlers.h /usr/src/server/
COPY responses.c responses.h /usr/src/server/
COPY endpoints/libreria.c endpoints/libreria.h /usr/src/server/endpoints/
COPY endpoints/utenti.c endpoints/utenti.h /usr/src/server/endpoints/
COPY endpoints/register.c endpoints/register.h /usr/src/server/endpoints/
COPY endpoints/prestiti.c endpoints/prestiti.h /usr/src/server/endpoints/
COPY endpoints/login.c endpoints/login.h /usr/src/server/endpoints/
COPY connection/json_connection_manager.c connection/json_connection_manager.h /usr/src/server/connection/
COPY log/logging.c log/logging.h /usr/src/server/log/

# Compila il codice sorgente
RUN gcc -o server server.c handlers.c responses.c endpoints/libreria.c endpoints/utenti.c endpoints/register.c endpoints/login.c endpoints/prestiti.c connection/json_connection_manager.c log/logging.c


# Esponi la porta su cui il tuo server C sta ascoltando
EXPOSE 5193

# Avvia il tuo server C quando viene eseguita l'immagine
CMD ["./server"]