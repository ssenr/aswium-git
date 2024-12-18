#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <regex.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE     1048576

// Strangely similar to code from Jeffery Yu, found at:
// https://dev.to/jeffreythecoder/how-i-built-a-simple-http-server-from-scratch-using-c-739

char* index_html= "<!DOCTYPE html><html><head><link href=\"./src/html/index.css\" rel=\"stylesheet\" /><title>ASWIUM-GIT</title></head><body><h1> Herro!</h1><p>Mark your calendars, Oct 18th!</p><img src=\"./src/resources/spongebob.png\"></body></html>";

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

void* handle_client(void* fd)
{
    int client_fd = *((int*) fd);
    
    // 1 Megabyte Buffer
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_recieved = recv(client_fd, buffer, BUFFER_SIZE, 0);
    // printf("Recieved request:\n%s\n", buffer);

    // CSS
    if (strncmp(buffer, "GET /src/html/index.css HTTP/1.1", 24) == 0)
    {
        FILE* file = fopen("./src/html/index.css", "rb");
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char* file_data = malloc(file_size);
        fread(file_data, 1, file_size, file);
        fclose(file);


        char response_header[BUFFER_SIZE];
        snprintf(response_header, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/css\r\n"
                 "Content-Length: %ld\r\n"
                 "Connection: close\r\n"
                 "\r\n",
                 file_size);

        send(client_fd, response_header, strlen(response_header), 0);
        send(client_fd, file_data, file_size, 0);
        free(file_data);

    }

    // FAVICON LOL
    if (strncmp(buffer, "GET /favicon.ico HTTP/1.1", 24) == 0)
    {
        FILE* file = fopen("./src/resources/favicon.ico", "rb");
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char* file_data = malloc(file_size);
        fread(file_data, 1, file_size, file);
        fclose(file);


        char response_header[BUFFER_SIZE];
        snprintf(response_header, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: image/x-icon\r\n"
                 "Content-Length: %ld\r\n"
                 "Connection: close\r\n"
                 "\r\n",
                 file_size);

        send(client_fd, response_header, strlen(response_header), 0);
        send(client_fd, file_data, file_size, 0);
        free(file_data);
    }

    // Spongebob
    if (strncmp(buffer, "GET /src/resources/spongebob.png HTTP/1.1", 24) == 0)
    {
        FILE* file = fopen("./src/resources/spongebob.png", "rb");
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char* file_data = malloc(file_size);
        fread(file_data, 1, file_size, file);
        fclose(file);

        char response_header[BUFFER_SIZE];

        snprintf(response_header, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: image/png\r\n"
                 "Content-Length: %ld\r\n"
                 "Connection: close\r\n"
                 "\r\n",
                 file_size);

        send(client_fd, response_header, strlen(response_header), 0);
        send(client_fd, file_data, file_size, 0);
        free(file_data);
    }

    if (bytes_recieved > 0)
    {
        regex_t regex;
        regcomp(&regex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);

        regmatch_t matches[2];
        
        if (regexec(&regex, buffer, 2, matches, 0) == 0)
        {
            char* header = http_header_ok();
            int len = strlen(header);
            send(client_fd, header, len, 0);
            free(header);
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
    struct sockaddr_in server_addr;
    if ( server_fd < 0)
    {
        perror("Socket initilization failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int bind_status = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (bind_status < 0)
    {
        perror("Binding socket to port failed");
        exit(EXIT_FAILURE);
    }

    // MAX CONNECTIONS = 10
    int listen_status = listen(server_fd, 10);

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