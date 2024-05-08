docker build -t c_web_server .
docker run -d --rm --name server -p 5193:5193 c_web_server /usr/src/server/server