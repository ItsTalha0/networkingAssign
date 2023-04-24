
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


void brainFunction(char *earfile,char *mouthfile,char *context,char *id)
{
	
	int fd = open(mouthfile,O_WRONLY | O_CREAT,0644);
	int i =0;
	sleep(10);
	while(1)
	{
		dprintf(fd,"%s%s0000hello this is%d\n",context,id,i++);
	}


}



int main(int args,char *argv[])
{
	int listenPort = atoi(argv[1]);
	char earFile[3] = "e";
	char mouthFile[3] = "m";
	strcat(earFile,argv[2]);
	strcat(mouthFile,argv[2]);
	int pide = fork();
	if( pide == 0){
		char *argu[3];
		argu[0] = "mouth";
		argu[1] = mouthFile;
		argu[2] = NULL;
		int re = execv("mouth",argu);
		
		}
	else
	{
		int pid = fork();
		if( pid == 0)
		{
			char *argu1[4];
			argu1[0] = "ear";
			argu1[1] = argv[1];
			argu1[2] = earFile;
			argu1[3] = NULL;
			int re = execv("ear",argu1);
			if(re==-1)
				perror("error:\n");
		}
		else
		{
			brainFunction(earFile,mouthFile,argv[3],argv[1]);
		}
	}
}
