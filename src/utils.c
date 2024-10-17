#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void error(const char* message)
{
  fprintf(stderr, "Error: %s\n", message);
}

char* read_html(const char* file_path) 
{
  FILE *file_ptr;
  static char html[MAX_HTML_LENGTH];
  char buf;

  int iteration = 0;

  file_ptr = fopen(file_path, "r");
  if (file_ptr == NULL)
  {
    error("Invalid file path or file permissions");
    return NULL;
  }

  while((buf = fgetc(file_ptr)) != EOF)
  {
    if (iteration > MAX_HTML_LENGTH)
    {
      error("HTML file too large.");
      fclose(file_ptr);
      return NULL;
    }

    html[iteration] = buf;
    iteration++;
  }

  fclose(file_ptr);
  return html;
}
