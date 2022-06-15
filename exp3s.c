#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
void main()
{
int sockid,cllid,valread;
char buf[1000];
struct sockaddr_in server,client;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid<0)
{
printf("Error\n");
return;
}
server.sin_family=AF_INET;
server.sin_port=htons(8080);
server.sin_addr.s_addr=INADDR_ANY;
if(bind(sockid,(struct sockaddr*)&server,sizeof(server))<0)
{
printf("Bind  failed\n");
return;
}
if(listen(sockid,3)<0)
{
printf("Listening Failed!!\n");
return;
}
int addreslen=sizeof(server);
if((cllid=accept(sockid,(struct sockaddr*)&server,(socklen_t*)&addreslen))<0)
{
printf("Accept Failed!!\n");
return;
}
valread=read(cllid,buf,1000);
printf("Message Received from client: %s\n",buf);
char* msg="Hello, Server this side";
send(cllid,msg,strlen(msg),0);
printf("Message sent to client");
}




