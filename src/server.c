#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <regex.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE     2048

void* handle_client(void* fd)
{
    int client_fd = *((int*) fd);
    char* buffer = (char*)malloc(BUFFER_SIZE);
}

void run_server()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    if ( server_fd < 0)
    {
        perror("Socket initilization failed.");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int bind_status = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (bind_status < 0)
    {
        perror("Binding socket to port failed.");
        exit(EXIT_FAILURE);
    }

    // MAX CONNECTIONS = 10
    int listen_status = listen(server_fd, 10);

    if (listen_status < 0)
    {
        perror("Listening to socket failed.");
        exit(EXIT_FAILURE);
    }

    // HANDLE CLIENT CONNECTIONS
    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int* client_fd = malloc(sizeof(int));

        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd < 0)
        {
            perror("Accept Failed");
            continue;
        }

        // Create new thread for every connection
        // Handle connection by calling handle_client function and passing client file descriptor
        pthread_t thread_id;
        pthead_creat(&thread_id, NULL, handle_client, (void*) client_fd);
        pthread_detach(thread_id);
    }
}
