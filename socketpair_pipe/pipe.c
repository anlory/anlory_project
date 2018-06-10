#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define SIZE 1024

int fd1[2],fd2[2]; //fd1[0]:read,  fd1[1]:write

void *func_thread1(void *arg)
{
	char buf[SIZE] = {0};
	int cnt = 0;
	while(1)
	{
		sprintf(buf,"hello main  %d\n",cnt++);
		write(fd1[1],buf,strlen(buf));
		int len = read(fd2[0],buf,SIZE);
		buf[len] = '\0';
		printf("%s",buf);
		bzero(buf,SIZE);
		sleep(3);
	}
	return NULL;
}

int main(int agrc,char**argv)
{
	pthread_t thread1_t;
	
	/*1. create pipe*/
	pipe(fd1);
	pipe(fd2);
	/*2. create thread1*/
	pthread_create(&thread1_t, NULL,
                          func_thread1, NULL);
	char buf[SIZE] = {0};
	int cnt = 0;
	char * p = buf;
	printf("buf[SIZE] sizeof:%d,  strlen:%d\n",sizeof(buf),strlen(buf));
	printf(" char * p  sizeof:%d,  strlen:%d\n",sizeof(p),strlen(p));
	while(1){
		int len = read(fd1[0],buf,SIZE);
		buf[len] = '\0';
		printf("%s",buf);
		bzero(buf,SIZE);
		sprintf(buf,"hello thread  %d\n",cnt++);
		write(fd2[1],buf,strlen(buf));	
		sleep(3);
	}
	return 0;
}

