#include"net.h"


int main(int argc, char *argv[])
{
  // 1.create listen fd;
  int sockfd = socket(AF_UNIX,SOCK_STREAM,0);

  

  //2. init addr
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path,PATH);


  //3. bind addr and fd
  if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) < 0){
    perror("bind");
    exit(1);
  }
  //4. listening
  if(listen(sockfd,8) < 0){
    perror("listen");
    exit(1);
  }

  //5. wait to accept

  struct sockaddr_un cli_addr;
  socklen_t len = sizeof(cli_addr);
  int conn_fd;
  printf("listening ...\n");
  if(( conn_fd = accept(sockfd,(struct sockaddr*)&cli_addr,&len) ) < 0){
      perror("accept");
      exit(1);
  }

  printf("client %s  connnected\n",cli_addr.sun_path);
  
  //6. read\write

  char buf[1024];
  int ret;
  while(1){
    bzero(buf,1024);

    if((ret = read(conn_fd,buf,1024)) <0){
      perror("read");
      exit(1);
    }else if (ret == 0){
      printf("client disconnected\n");
      break;
    }else{
      printf("receive data: %s \n",buf);
    }
  }

  close(sockfd);
  close(conn_fd);


  return 0;
}







