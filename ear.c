#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUFLEN 1024
//#define LISTENPORT 1234
#define MAX_MESSAGES = 1024;





void messagePush(char  buff[], int size,char *ee)
{
	int fd,bw;
	fd = open(ee,O_WRONLY| O_CREAT | O_APPEND,0644);
	if(fd < 0)
	{
		perror("Cannot open file erroor");
		exit(1);
	}
	else
	{
		bw = write(fd,buff,size);
		bw = write(fd,"\n",1);
	}
	close(fd);
}

void listenatport(int portNumber,char *ee){
	
  int sockfd, len, n;
  char buffer[BUFLEN];
  struct sockaddr_in receiverAddr, senderAddr;    // look for sockaddr_in

  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)   // getting the socket file discriptor sock fd is a number
  {
    perror("socket system call failed");
    exit(EXIT_FAILURE);
  }

  memset(&receiverAddr, 0, sizeof(receiverAddr));
  memset(&senderAddr, 0, sizeof(senderAddr));

  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_addr.s_addr = INADDR_ANY;
  receiverAddr.sin_port = htons(portNumber);

  if(bind(sockfd, (const struct sockaddr *)&receiverAddr, sizeof(receiverAddr)) < 0)  //binding the created socket to addr and port of reciever
  {
    perror("bind syscall failed");
    exit(EXIT_FAILURE);
  }
  len = sizeof(senderAddr);
  //printf("sear waiting for data to be received: \n");
  while(1)
  {
  
  n = recvfrom(sockfd, (char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *) &senderAddr, &len);  // this function gets the data from socket ??
  //printf("%d\n",n);
  buffer[n] = '\0';
  //printf("data received by sear is: %s\n", buffer);
  messagePush(buffer,n,ee);
  //printf("--------------\n");
  }
}


int main(int c,char *argc[])
{
	int portNumber = atoi(argc[1]);
	listenatport(portNumber,argc[2]);
}

