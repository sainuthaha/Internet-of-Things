#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/wait.h>
#include<ctype.h>
#include<sys/time.h>

int main()
{
	

	int sockid,newid,clientsocket[30],max,sd,num,num1,num2,i,j,k,activity,l;
	char buf[1024],op[50];
	fd_set readfds;
	for(i=0;i<30;i++)
	clientsocket[i]=0;
	if( (sockid=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
	perror("socket ");
	exit(-1);
	}
	struct sockaddr_in client,server;

	server.sin_family=AF_INET;
	server.sin_port=htons(3000);
	inet_pton(AF_INET,"192.168.43.114",&(server.sin_addr));
	bzero(&server.sin_zero,8);
	socklen_t addr_size=sizeof(struct sockaddr);

	if(bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1)
	{
	   perror("bind ");
	   exit(-1);
	}
	 if(listen(sockid,5)==-1)
	{
	  perror("listen ");
	  exit(-1);
	}
	printf("waiting for connections \n");
	int flag=0;
	while(1)
	{
		     FD_ZERO(&readfds);
		     FD_SET(sockid,&readfds);
		     max=sockid;
		     for(i=0;i<30;i++)
		     {
		       sd=clientsocket[i];
		       if(sd>max)
			 max=sd;
		       if(sd>0)
			 FD_SET(sd,&readfds);
		     }
		     activity=select(max+1,&readfds,NULL,NULL,NULL);
		     if(FD_ISSET(sockid,&readfds))
		     {
				  if( (newid=accept(sockid,(struct sockaddr*)&client,&addr_size))==-1)
				  {
				     perror("accept ");
				     exit(-1);
				  }
                           
               			  //printf("client connected\n");
                         	  for(i=0;i<30;i++)
				  {
				     if(clientsocket[i]==0)
				     {
					clientsocket[i]=newid;
					printf("adding to list of sockets as %d \n",i);
					break;
				     }
                                    
				  }
				  
	            }
		      //int flag=0;
                      int i;
		      for(i=0;i<30;i++)
		      {
				  sd=clientsocket[i];
                                  //sleep(1);
				  if(FD_ISSET(sd,&readfds))
				  {
                                     
	
				     for(i=0;i<10;i++)
                                     {
                                     printf("Temperature:");
                                     num=recv(sd,buf,9,0);
                                     
                                     buf[num]='\0';
                                     printf("buffer:%s**\n",buf);
                                     num=0;
                                     printf("Humidity:");
                                     num=recv(sd,buf,9,0);
                                     buf[num]='\0';
                                     printf("buffer:%s**\n",buf);
                                     num=0;
                                     }

                                 }
                      }
     }

}







