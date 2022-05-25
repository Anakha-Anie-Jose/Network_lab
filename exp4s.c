#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
void main()
{
	int sockid,cliid;
	int buf[10];
	int min,max;
	float avg;
	struct sockaddr_in server,client;
	sockid=socket(AF_INET,SOCK_STREAM,0);
	if(sockid<0)
	{
		printf("Error\n");
		return;
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("172.20.32.228");
	if(bind(sockid,(struct sockaddr*)&server,sizeof(server))<0)
	{
		printf("Bind failed\n");
		return;
	}
	printf("Listening");
	listen(sockid,3);
	int c=sizeof(struct sockaddr_in);
	cliid=accept(sockid,(struct sockaddr*)&server,(socklen_t *)&c);
	printf("Accepted\n");
	recv(cliid,&buf,10*sizeof(int),0);
	min=buf[0];
	max=buf[0];
	avg=buf[0];
	for(int i=1;i<10
	;i++)
	{
		if(min>buf[i])
			min=buf[i];
		else if(max<buf[i])
			max=buf[i];
		avg+=buf[i];
	}
	avg=avg/10;
	send(cliid,&min,sizeof(int),0);
	send(cliid,&max,sizeof(int),0);
	send(cliid,&avg,sizeof(float),0);
	printf("Connection over\n");
	close(sockid);
}


