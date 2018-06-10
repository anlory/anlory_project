#include"net.h"


int main(int argc, char *argv[])
{
  int listen_fd, conn_fd;
  struct sockaddr_un sin,cin;
  // 1.create listen fd;
  if((listen_fd = socket(AF_UNIX,SOCK_STREAM,0)) < 0){
    perror("socket");
    exit(1);
  }
  //2. init addr
  sin.sun_family = AF_UNIX;
  strcpy(sin.sun_path,PATH);
  
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







