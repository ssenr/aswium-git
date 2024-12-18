#include <stdio.h>
#include "fanyi.h"
#include "html.h"
#include "packets.h"
#include "server.h"

int main(void)
{
    char* result;
    char* index_html = "/home/fatchick/aswium-git/src/test";
       result = read_html(index_html);
       printf("%s", result);
    return 0;
}