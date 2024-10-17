#include "client_tester.h"

#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

char *request(struct client_tester *client, char *server_ip, void *request, unsigned long size);

struct client_tester clientConstructor(int domain, int service, int protocol, int port, unsigned long interface){
    struct client_tester client;
    client.domain = domain;
    client.port = port;
    client.interface = interface;
    client.socket = socket(domain, service, protocol);
    client.request = request;
    return client;

}

char *request(struct client_tester *client, char *server_ip, void *request, unsigned long size){
    struct sockaddr_in server_address;
    server_address.sin_family = client->domain;
    server_address.sin_port = htons(client->port);
    server_address.sin_addr.s_addr = (int)client->interface;
    //makes the connection
    inet_pton(client->domain, server_ip, &server_address.sin_addr);
    connect(client->socket,(struct sockaddr*)&server_address, sizeof(server_address));
    //sends the request
    send(client->socket, request,size, 0);
    //reads the response
    char *response = malloc(30000);
    read(client->socket,response, 30000);
    return response;
}

void test(){
    client_tester tester;
    char server_ip[] = "127.0.0.1";
    clientConstructor(AF_INET, SOCK_STREAM, 0, 8080, )
    request(&tester, &server_ip, )
}