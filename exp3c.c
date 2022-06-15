#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
void main()
{
int sockid,valread;
struct sockaddr_in client;
char * msg="Hello, Client this side";
char buf[1000];
if((sockid=socket(AF_INET,SOCK_STREAM,0))<0)
{
printf("Error!!\n");
return;
}
client.sin_family=AF_INET;
client.sin_port=htons(8080);
client.sin_addr.s_addr=INADDR_ANY;
if(connect(sockid,(struct sockaddr*)&client,sizeof(client))<0)
{
printf("Connection Failed!!\n");
return;
}
send(sockid,msg,strlen(msg),0);
printf("Message sent to server\n");
valread=read(sockid,buf,1000);
printf("Message from server: %s",buf);
}
