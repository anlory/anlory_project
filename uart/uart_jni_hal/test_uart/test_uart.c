#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>


#define MAX_COM_NUM 2
#define BUFF_SIZE  1024



int fd;
int open_port(int num)
{
	
	char *dev[] = {"/dev/ttyHSL0","/dev/ttyHSL1"};
	if(num < 0  || num > MAX_COM_NUM){
		return -1;
	}
	fd = open(dev[num-1],O_RDWR|O_NOCTTY);
	if(fd < 0){
		perror("open serial port");
		return -1;
	}
	if(fcntl(fd,F_SETFL,0) < 0){
		perror("fcntl F_SETFL");
	}
	if(isatty(fd) == 0){
		perror("this is a not terminal device");
	}
	return fd;
}


int write_buf(char* buf,int len)
{
	int ret;
	ret = write(fd,buf,len);
	if(ret < 0){
		perror("write error");
	}
	return ret;
}

int read_buf(char* buf,int len)
{
	int ret,i = 0;
	char ch;
	while(1){
		ret = read(fd,&ch,1);
		if(ret < 0){
			perror("read error");
		}
		buf[i++] = ch;
		if(i==100)
			break;
	}
	return ret;
}


int main(int argc, char *argv[])
{
	int num,ret;
	char buff[BUFF_SIZE];
	char buf_w[] = "hello serial";
	
	if(argc < 2){
		printf("USAGE:\n");
		printf("./test_uart num(serial num)");
		exit(-1);
	}
	num = atoi(argv[1]);
	
	open_port(num);
	
      


  while(1){
   // printf("Input some words(enter 'quit' to exit):");
    memset(buff,0,1024);
	
	read_buf(buff,BUFF_SIZE);
	write_buf(buff,sizeof(buff));
	//printf("recv:%d: %s \n",num++,buff);
  }


  return 0;
}


