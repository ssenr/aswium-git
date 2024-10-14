
//Server side for now

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

//designed for chat between client and server
void chat(int connfd){
    char buff[MAX];
    int n;
    for(;;){    //infinite loop
        bzero(buff,MAX);
        read(connfd, buff, sizeof(buff));
        printf("from client: %s\t to client: ",buff);
        bzero(buff,MAX);
        n = 0;
        while((buff[n++] = getchar()) != '\n');
        write(connfd,buff,sizeof(buff));

        if(strncmp("exit",buff,4)==0){
            printf("Server exit\n");
            break;
        }
    }
}

void serve()
{
    int serverfd, connfd,len;
    struct sockaddr_in address, cli;
    int opt = 1;
    socklen_t addrlength = sizeof(address);
    char buffer[1024] = {0};
    char* msg = "Message recieved";

    //creating file descriptor
    serverfd = socket(AF_INET ,SOCK_STREAM,0);
    if (serverfd==-1){     //ipv4/6, tcp, protocol 0
        perror("socket creation failed");    //print error
        exit(0);
    } 
    else{
        printf("Socket created\n");
        bzero(&address,sizeof(address));
    }

    //forcefully attaching socket to port8080 (standard port for web servers)
    /*
    manipulate options for socket referred byfile descriptor sockfd, helps in reuse of address and port(optional)
    prevent error of address already in use
    */
    if (setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){    
        perror("setsockopt failed?");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = hton1(INADDR_ANY); //dont change
    address.sin_port = htons(8080);

    //attaching socket to port 8080
    /*
        binds socket to address and port number specified in addr
        INADDR_ANY to specify IP address
    */
    if(bind(serverfd,(struct sockaddr* )&address,sizeof(address))!=0){
        perror("bind failed\n");
        exit(0);
    }
    else{
        printf("socket binded\n");
    }

    if(listen(serverfd,5)!=0){
        perror("listen function failed\n");
        exit(0);
    }
    else{
        printf("server listening\n");
        len = sizeof(cli);
    }

    if((new_socket = accept(serverfd,(struct sockaddr*)&address,&addrlength))<0){
        perror("accept error\n");
        exit(0);
    }
    else{
        printf("server accepted\n");
    }

    chat(connfd);


    close(serverfd);
   

}

