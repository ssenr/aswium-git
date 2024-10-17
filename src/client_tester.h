#ifndef client_tester_h
#define client_tester_h

#include <sys/socket.h>
#include <netinet/in.h>

struct client_tester{
    int socket;
    int domain;
    int service;
    int protocol;
    int port;

    unsigned long interface;
    char* (*request)(struct Client *client, char *server_ip, void* request, unsigned long size);

};

struct client_tester clientConstructor(int domain, int service, int protocol, int port, unsigned long interface);

#endif 