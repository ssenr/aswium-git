
//Server side for now

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char const* argv[])
{
    int serverfd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlength = sizeof(address);
    char buffer[1024] = {0};
    char* msg = "Message recieved";

    //creating file descriptor
    if ((serverfd = socket(AF_INET ,SOCK_STREAM, 0 )) < 0){     //ipv4/6, tcp, protocol 0
        perror("socket failed");    //print error
        exit(EXIT_FAILURE);
    }  

    //forcefully attaching socket to port8080 (standard port for web servers)
    /*
    manipulate options for socket referred byfile descriptor sockfd, helps in reuse of address and port(optional)
    prevent error of address already in use
    */
    if (setsockopt(serverfd,SOL_ROCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){    
        perror("setsockopt failed?");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.sin_addr = INADDR_ANY; //dont change
    address.sin_port = htons(8080);

    //attaching socket to port 8080
    /*
        binds socket to address and port number specified in addr
        INADDR_ANY to specify IP address
    */
    if(bind(serverfd,(struct sockaddr* )&address,sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if(listen(serverfd,3)<0){
        perror("listen function failed");
        exit(EXIT_FAILURE);
    }
    if(new_socket = accept(serverfd,(struct sockaddr*)&address,&addrlength)){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket,buffer,1024 -1); //1 is subtracted for the null terminator
    printf("%s\n",buffer);
    send(new_socket, msg, strlen(msg),0);
    printf("msg sent\n");
    close(new_socket);
    close(serverfd);
    return 0;

}

