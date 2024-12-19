#include <stdio.h>
#include "fanyi.h"
#include "html.h"
#include "server.h"

int main(void)
{
    //char* request = "GET /src/resources/spongebob.png HTTP/1.1";
    //printf("Hello, World!");
    run_server();
    //char* x = get_requested_resource_path(request);
    char* file_ext = get_file_ext("./src/html/index.html");
    char* mt = get_mime_type(file_ext);
    //char* fd = get_file_data("./src/html/index.html");
    long fs = get_file_size("./src/html/index.html");
    char* header = build_header(mt, fs);
    printf("%s\n", header);
}