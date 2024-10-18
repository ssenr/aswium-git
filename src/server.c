#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <regex.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "http.h"
#include "utils.h"

/*
* PRIVATE FUNCTIONS
*/

void* handle_http_request(void* arg)
{
  int client_socket = * ((int*)arg); // Cast arg to int* then dereferennce it
  char* buf = (char*) malloc(MAX_HEADER_LENGTH * sizeof(char));
  
  ssize_t request_size = recv(client_socket, buf, MAX_HEADER_LENGTH, 0);

  if (request_size == 0)
  {
    error("Invalid Request");
    return NULL;
  }

  regex_t regex;
  int regex_status;

  // GET REQUEST SYNTAX
  // GET <request-target>["?"<query>] HTTP/1.1
  regex_status = regcomp(&regex, "^GET /([^ ])*", REG_EXTENDED);

  regex_status = regexec(&regex, buf, 0, NULL, 0);

  if (regex_status == 0)
  {
    char* response_header = http_header_ok(); 
    send(client_socket, response_header, (size_t) strlen(response_header), 0);
    free(response_header);
  }

  regfree(&regex);
  close(client_socket);
  free(arg);
  return NULL;
}

/*
* PUBLIC FUNCTIONS
*/

void run()
{
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr = INADDR_ANY;

  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  listen(server_socket, 5);

  while(1)
  {
    int* client_socket = (int*) malloc(sizeof(int));

    *client_socket = accept(server_socket, NULL, NULL);

    pthread_t thread;
    pthread_create(&thread, NULL, handle_http_request, (void*) client_socket);
    pthread_detach(thread);
  }
}
