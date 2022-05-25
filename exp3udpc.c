#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
void main()
{
	int sockid;
	char buffer[1024];
	char * msg="Welcome";
	struct sockaddr_in server;
	if((sockid=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("Error");
		return;
	}
	memset(&server,0,sizeof(server));
	server.sin_port=htons(8080);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sendto(sockid,(const char*)msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*)&server,sizeof(server));
	printf("Message sent to server\n");
	int len=sizeof(struct sockaddr_in);
	int n=recvfrom(sockid,(char *)buffer,1024,MSG_WAITALL,(struct sockaddr*)&server,&len);
	buffer[n]='\0';
	printf("%s\n",buffer);
	close(sockid);
}
