#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void serve(void)
{
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
  if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
    printf("\n Invalid address/ address not supported \n");
    return -1;
  }
  if((status = connect(clientfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))<0){
    printf("\nConnection failed \n");
    return -1;
  }
  send(clientfd,msg,strlen(msg),0);
  return -1;
  printf("msg from client side sent\n");
  valread = read(clientfd,buffer,1024 -1);
  printf("%s\n", buffer);
  close(clientfd);
}
