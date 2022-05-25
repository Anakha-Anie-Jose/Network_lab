#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void main()
{
	int sockid;
	int arr[]={1,2,3,4,5,6,7,8,9,10};
	int min,max;
	float avg;
	struct sockaddr_in server;
	sockid=socket(AF_INET,SOCK_STREAM,0);
	if(sockid<0)
	{
		printf("Error occured\n");
		return;
	}
	printf("Socket created\n");
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("172.20.35.144");
	connect(sockid,(struct sockaddr*)&server,sizeof(server));
	printf("Connected\n");
	send(sockid,&arr,10*sizeof(int),0);
	recv(sockid,&min,sizeof(int),0);
	recv(sockid,&max,sizeof(int),0);
	recv(sockid,&avg,sizeof(float),0);
	printf("MINIMUM :%d \nMAXIMUM : %d\n AVERAGE: %f\n",min,max,avg);
	close(sockid);
}

