#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

char* index_html = "<!DOCTYPE html><html><head><title>ASWIUM-GIT</title></head><body><h1> Herro!</h1><p>Mark your calendars, Oct 18th!</p></body></html>";

char* http_header_ok()
{
  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  strcat(http_header, index_html);

  return index_html;
}

