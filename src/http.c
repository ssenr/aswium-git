#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include "utils.h"

char* http_header_ok()
{
  char* index_html = read_html("./src/html/index.html");

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  strcat(http_header, index_html);

  return index_html;
}

