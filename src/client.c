#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const* argv[]){
    int status, valread, clientfd;
    struct sockaddr_in serv_addr;
    char* msg = "client msg: ..."
    char buffer[1024] = {0};
    if((clientfd = socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\n socket creation error");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    //ip addr from txt to bin form
    if(inet_pton(AF_INET,"12"))
}
