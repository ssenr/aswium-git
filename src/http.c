#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include "utils.h"
#include "http.h"

char* http_header_ok() // index.html
{
  char* index_html = read_html("./src/html/index.html");
  char* http_header = "HTTP/1.1 200 OK\r\n\n";

  int len_header = strlen(http_header);
  int len_html = strlen(index_html);

  char* str = (char*)malloc((len_header + len_html + 1)* sizeof(char));
  strcpy(str, http_header);
  str[strlen(str)] = '\0'; 
  strcat(str, index_html);

  return str;
}
