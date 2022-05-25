#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
void main()
{
	int sockid;
	struct sockaddr_in server,client;
	int arr[5];
	int min,max;
	float avg;
	if((sockid=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("Error");
		return;
	}
	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	bind(sockid,(struct sockaddr*)&server,sizeof(server));
	int len=sizeof(client);
	int n=recvfrom(sockid,&arr,5*sizeof(int),MSG_WAITALL,(struct sockaddr*)&client,&len);
	min=arr[0];
	max=arr[0];
	avg=arr[0];
	for(int i=1;i<5;i++)
	{
	if(arr[i]>max)
	    max=arr[i];
	if(arr[i]<min)
	    min=arr[i];
	avg+=arr[i];
	}
	avg=avg/5;
	sendto(sockid,&min,sizeof(int),MSG_CONFIRM,(struct sockaddr*) &client,len);
	sendto(sockid,&max,sizeof(int),MSG_CONFIRM,(struct sockaddr*) &client,len);
	sendto(sockid,&avg,sizeof(float),MSG_CONFIRM,(struct sockaddr*) &client,len);
	printf("Message sent to client"); 
	
}

