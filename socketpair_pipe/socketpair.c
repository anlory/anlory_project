#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define SIZE 1024

void *func_thread1(void *arg)
{
	char buf[SIZE] = {0};
	int cnt = 0;
	int fd = (int)arg;
	while(1)
	{
		sprintf(buf,"hello main  %d\n",cnt++);
		write(fd,buf,strlen(buf));
		int len = read(fd,buf,SIZE);
		buf[len] = '\0';
		printf("%s",buf);
		bzero(buf,SIZE);
		sleep(3);
	}
	return NULL;
}

int main(int agrc,char**argv)
{
	int fd[2];
	pthread_t thread1_t;
	
	/*1. create socketpair*/
	int ret = socketpair(AF_UNIX,SOCK_STREAM,0,fd);
	if(ret < 0){
		perror("socketpair");
		exit(-1);
	}
	/*2. create thread1*/
	pthread_create(&thread1_t, NULL,
                          func_thread1, fd[1]);
	char buf[SIZE] = {0};
	int cnt = 0;
	char * p = buf;

	while(1){
		int len = read(fd[0],buf,SIZE);
		buf[len] = '\0';
		printf("%s",buf);
		bzero(buf,SIZE);
		sprintf(buf,"hello thread  %d\n",cnt++);
		write(fd[0],buf,strlen(buf));	
		sleep(3);
	}
	return 0;
}

