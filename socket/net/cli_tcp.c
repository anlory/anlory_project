#include"net.h"


int main(int argc, char *argv[])
{
  int listen_fd, conn_fd;
  struct sockaddr_in sin,cin;
  // 1.create listen fd;
  if((listen_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
    perror("socket");
    exit(1);
  }
  //2. init addr
  bzero(&sin,sizeof(sin));
  sin.sin_family = AF_INET;
  if(argc != 3){
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = inet_addr(IP);
  }else{
    sin.sin_port = htons(atoi(argv[1]));
    sin.sin_addr.s_addr = inet_addr(argv[2]);
  }
  //3. comunicate  with server
  
  if(connect(listen_fd, (struct sockaddr*)&sin,sizeof(sin)) <0){
    perror("connect");
    exit(1);
  }


  char buf[1024];
  while(1){
    fgets(buf,1024,stdin);
    write(listen_fd,buf,strlen(buf));
    if(strncmp(buf,"quit",4) == 0){
      break;
    }
  }
  close(listen_fd);
  return 0;
}







