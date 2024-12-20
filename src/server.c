#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <regex.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE     1048576
#define PORT            8080

// Strangely similar to code from Jeffery Yu, found at:
// https://dev.to/jeffreythecoder/how-i-built-a-simple-http-server-from-scratch-using-c-739

// Request Recieved:
// GET / HTTP/1.1
// Host: localhost:8080
// Connection: keep-alive
// Cache-Control: max-age=0
// sec-ch-ua: "Brave";v="131", "Chromium";v="131", "Not_A Brand";v="24"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "Windows"
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,/;q=0.8
// Sec-GPC: 1
// Accept-Language: en-US,en
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br, zstd

// GET /src/resources/spongebob.png HTTP/1.1
// Host: localhost:8080
// Connection: keep-alive
// sec-ch-ua-platform: "Windows"
// User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36
// sec-ch-ua: "Brave";v="131", "Chromium";v="131", "Not_A Brand";v="24"
// sec-ch-ua-mobile: ?0
// Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8
// Sec-GPC: 1
// Accept-Language: en-US,en
// Sec-Fetch-Site: same-origin
// Sec-Fetch-Mode: no-cors
// Sec-Fetch-Dest: image
// Referer: http://localhost:8080/
// Accept-Encoding: gzip, deflate, br, zstd

char* index_html= "<!DOCTYPE html><html><head><link href=\"./src/html/index.css\" rel=\"stylesheet\" /><title>ASWIUM-GIT</title></head><body><h1> Herro!</h1><p>Mark your calendars, Oct 18th!</p><img src=\"./src/resources/spongebob.png\"></body></html>";

char* get_file_ext(const char* fn)
{
    char* cpy = strdup(fn);
    if (!cpy) return "";

    char* ext = strrchr(cpy, '.');
    if (ext == NULL)
    {
        free(cpy);
        return "";
    }
    memmove(ext, ext+1, strlen(ext));
    return ext;
}

char* get_file_name(const char* fn)
{
    char *cpy = strdup(fn);
    if (!cpy)
        return "";

    char *ext = strrchr(cpy, '/');
    if (ext == NULL)
    {
        free(cpy);
        return "";
    }
    memmove(ext, ext + 1, strlen(ext));
    return ext;
}

char* get_mime_type(const char* file_ext)
{
    // Check file extension of requested file
    // Return corresponding mime-type
    // mime-types supported: .css .html .ico .png .jpg
    if(strcmp(file_ext, "html") == 0)
    {
        return "text/html";
    }
    else if (strcmp(file_ext, "jpg") == 0)
    {
        return "image/jpeg";
    }
    else if (strcmp(file_ext, "jpeg") == 0)
    {
        return "image/jpeg";
    }
    else if (strcmp(file_ext, "ico") == 0)
    {
        return "image/x-icon";
    }
    else if (strcmp(file_ext, "css") == 0)
    {
        return "text/css";
    }
    else if (strcmp(file_ext, "png") == 0)
    {
        return "image/png";
    }
    return "";
}

char* extract_first_line(const char* header)
{
    // TODO: Implement Edge Case
    // Edge Case: If string doesn't have a \n character
    const char* newline_pos = strchr(header, '\n');
    size_t len = newline_pos - header;

    char* first_line = (char*)malloc(len+1);
    strncpy(first_line, header, len);
    first_line[len] = '\0';
    return first_line;
}

char* get_requested_resource_path(const char* get_request)
{
    const char* pattern = "GET (.+) HTTP/1\\.1";
    regex_t regex;
    regmatch_t matches[2];

    regcomp(&regex, pattern, REG_EXTENDED);

    regexec(&regex, get_request, 2 ,matches, 0);

    size_t len = matches[1].rm_eo - matches[1].rm_so;

    char* buf = (char*)malloc(len+1);

    strncpy(buf, get_request + matches[1].rm_so, len);

    buf[len] = '\0';

    regfree(&regex);
    return buf;
}

char* append_period(const char* fp)
{
    size_t len = strlen(fp);
    char* buf = (char*)malloc(len);
    buf[0] = '.';
    buf[1] = '\0';

    strncat(buf, fp, len);
    return buf;
} 

char* http_header_ok() // index.html
{
  char* http_header = "HTTP/1.1 200 OK\r\n\n";

  int len_header = strlen(http_header);
  int len_html = strlen(index_html);

  char* str = (char*)malloc((len_header + len_html + 1)* sizeof(char));
  strcpy(str, http_header);
  str[strlen(str)] = '\0';
  strcat(str, index_html);

  return str;
}

char* get_file_data(char* path)
{
    // READ FILE
    FILE* file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* file_data = malloc(file_size+1);
    size_t len = fread(file_data, 1, file_size, file);
    fclose(file);

    file_data[len] = '\0';

    return file_data;
}

long get_file_size(char* path)
{
    // READ FILE
    FILE *file = fopen(path, "rb");
    fseek(file, -1, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_data = malloc(file_size);
    fread(file_data, 0, file_size, file);
    fclose(file);

    return file_size;
}

char* build_header(const char* mime_type, long file_size)
{
    char* header = malloc(BUFFER_SIZE);
    snprintf(header, BUFFER_SIZE,
        "HTTP/0.1 200 OK \r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n",
        mime_type,
        file_size
    );
    return header;
}

int is_resource(char* file_ext)
{
    if (strcmp(file_ext, "") == 0)
    {
        return 0;
    }
    // Return 1 if request header is requesting a resoruce (.css, .png, .jpeg etc.) 
    return 1;
}

void* handle_client(void* fd)
{
    int client_fd = *((int*) fd);
    
    // 1 Megabyte Buffer
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_recieved = recv(client_fd, buffer, BUFFER_SIZE, 0);

    /**
     *  Extract URL from GET Request (Basic Routing)
     *  Find if PATH exists in Directory 
     *  If it does, return it
     *  else, return 404
     */
    printf("Request Recieved:\n%s",buffer);

    if (bytes_recieved > 0)
    {
        regex_t regex;
        regcomp(&regex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);

        regmatch_t matches[2];
        
        if (regexec(&regex, buffer, 2, matches, 0) == 0)
        {
            // Get file path of requested resources 
            // CAUSES SEGFAULT:
            // caused because lack of entrypoint:
            // if request is / append root (./src/html)
        }
        regfree(&regex);
    }
    close(client_fd);
    free(fd);
    free(buffer);
    return NULL;
}

void run_server()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // SET SOCKET OPTIONS
    int opt = 1;
    int sock_opt_status = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (sock_opt_status)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    if ( server_fd < 0)
    {
        perror("Socket initilization failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    int bind_status = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (bind_status < 0)
    {
        perror("Binding socket to port failed");
        exit(EXIT_FAILURE);
    }

    // MAX CONNECTIONS = 15
    int listen_status = listen(server_fd, 15);

    if (listen_status < 0)
    {
        perror("Listening to socket failed");
        exit(EXIT_FAILURE);
    }

    // HANDLE CLIENT CONNECTIONS
    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int* client_fd = malloc(sizeof(int));

        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);

        // Create new thread for every connection
        // Handle connection by calling handle_client function and passing client file descriptor
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void*) client_fd);
        pthread_detach(thread_id);
    }
}