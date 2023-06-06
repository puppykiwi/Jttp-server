#ifndef JTTP_H
#define JTTP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const int buffsiz = 690000; // ~69KB, nice :)
const int PORT = 8080; // Port to listen on
const char *RESPONSE_HEADER = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
const char *HTML_FILE_PATH = "assets/index.html";

#endif