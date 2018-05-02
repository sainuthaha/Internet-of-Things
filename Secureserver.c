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
#include <openssl/des.h>
#include <openssl/rand.h>


int main()
{
	DES_cblock key;
   
        DES_key_schedule keysched;

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
                                     //sleep(50);
				     num=recv(sd,buf,4,0);
                                      
				     buf[num]='\0';
                                     printf("Received key:%s\n",buf);
                                     num=0;
                                     int lower=5000;
                                     int upper=9999;
   
                                     int no = rand() %(upper+1 -lower)+lower;
     
                                     //int no = (rand() + lower) % (upper + 1);
                                     char result[10];
                                     sprintf(result,"%d",no);

                                    
                                     send(sd,result,strlen(result),0);
                                     printf("Send key:%s\n",result);
                                     int a=atoi(buf);
                                     int b=no;
                                     double x=(0.1*4*a*b*b)/(a*a+b*b)*10;
                                     double y=(0.1*4*a*a*b)/(a*a+b*b)*10;
                                     int k=x*y;
                                     //int k;
                                     //k=(int)ke;
                                     printf("%d\n",k);
                                     printf("Key for the session = %d\n",(int)k);
                                      
                                     char res[8];
                                     sprintf(res,"%d",k);
     
  

                                    for (i=0;i<8;i++)
                                      key[i]=(unsigned char)res[i];
                                
                                     DES_set_key((C_Block *)(key), &keysched);
                                     unsigned char in[64], out[64];
                                     
                                    
                                     
				     for(i=0;i<10;i++)
                                     {
                                     
                                     memset(in, 0, sizeof(in));
                                     memset(out, 0, sizeof(out));
                                     memset(buf,0,sizeof(buf));
                                     num=recv(sd,buf,16,0);
                                     
                                     
                                     printf("Encypted temperature measure%s\n",buf);
                                     char  *pos = buf;
    
                                      int count;
    
                                      for ( count = 0; count < 8; count++) {
                                          sscanf(pos, "%2hhx", &in[count]);
                                          pos += 2;
                                      }
                                     DES_ecb_encrypt((C_Block *)in,(C_Block *)out, &keysched, DES_DECRYPT);
                                     printf("Decrypted temperature measure:%s\n",out);
                                     //free(pos);
                                     memset(in, 0, sizeof(in));
                                     memset(out, 0, sizeof(out));
                                     num=0;
                                     
                                     num=recv(sd,buf,16,0);
                                     buf[num]='\0';
                                     printf("Encrypted Humidity measure %s\n",buf);
                                     char *po= buf;
    
                                    
    
                                      for ( count = 0; count < 8; count++) {
                                          sscanf(po, "%2hhx", &in[count]);
                                          po += 2;
                                      }
                                     //free(po);
                                     DES_ecb_encrypt((C_Block *)in,(C_Block *)out, &keysched, DES_DECRYPT);
                                     printf("Decrypted Humidity measure:%s\n",out);
                                     num=0;
                                     
                                     }
                                    
                                     

                                 }
                      }
     }

}






