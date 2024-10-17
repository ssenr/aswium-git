#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "http.h"
#include "utils.h"

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

  int client_socket;

  char* response_header = http_header_ok();

  printf("%s", response_header);

  while(1)
  {
    client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, response_header, sizeof(response_header), 0);
    close(client_socket);
  }

  free(response_header);

}
