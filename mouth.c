#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>


int freadline(int fd,char *buff,int size);
int sendMessage(int port,char *buff,int size);

int sendMessage(int port,char *buff,int size)
{
	printf("%s --%d\n",buff,port);
}





int unendingFuntion(char *file){
	system("echo \"pstarted\" > test");
	int fd,PORT,message_id;
	char buff[1024];  //buff where message is to be stored
	char pbuff[5];
	/*----------------------------------------Socket initialisation Part---------------------------------------------*/
	int sockfd;
	struct sockaddr_in   receiverAddr;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
	perror("socket failed");
	exit(EXIT_FAILURE);
	}
	memset(&receiverAddr, 0, sizeof(receiverAddr));
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_addr.s_addr = INADDR_ANY;
	
	fd = open(file,O_RDWR|O_CREAT,0644);
	if(fd < 0)
	{ 
		printf("\n ee \n"); 
	}
	else
	{
		int i=0;
		//printf("\nfd ==> %d\n",fd); 
		int t;     	// = freadline(fd,buff,1024);	
		int sendErro;
		int errorFd = open("logs",O_WRONLY|O_CREAT,0644);
		char tempBuff[6];
		while( (t=freadline(fd,buff,1024))>=0 )
		{
			buff[t] = '\0';
			if( buff[0] != '\0' )
			{
				PORT = atoi(strncpy(pbuff,buff,4));
				message_id = atoi(strncpy(pbuff,&buff[8],4));
				//printf("%d\n",message_id);
				receiverAddr.sin_port = htons(PORT);
				sendErro=sendto(sockfd,(const char *)&buff[4],t-4, 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
				//sendMessage(port,&buff[4],t);
				if(sendErro > 0)
				{
					sprintf(tempBuff,"s%4d\n",message_id);
					write(errorFd,tempBuff,6);
				}
				else
				{
					
					sprintf(tempBuff,"f%4d\n",message_id);
					write(errorFd,tempBuff,6);
				
					//dprintf(errorFd,"f%d\n",message_id);
				}
			}
			buff[0] = '\0';
		}
	}
	close(fd);
}





int freadline(int fd,char *buff,int size)
{
	//printf("fread called\n");

	int i=0,bytesRead;
	
	while( ((bytesRead=read(fd,&buff[i],1))==1) && (buff[i]!='\n') && i < size )
	{ 
		//printf("%c",buff[i]);
		i=i+1; 
	}
	//printf("\n%d %d\n",bytesRead, i);
	return i;
}


void main(int arg,char *args[])
{
		
	unendingFuntion(args[1]);	
}


