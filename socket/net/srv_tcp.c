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


  //3. bind addr and fd
  if(bind(listen_fd,(struct sockaddr*)&sin,sizeof(sin)) < 0){
    perror("bind");
    exit(1);
  }
  //4. listening
  if(listen(listen_fd,8) < 0){
    perror("listen");
    exit(1);
  }

  //5. wait to accept
  bzero(&cin,sizeof(cin));

  socklen_t len = sizeof(cin);

  printf("listening ...\n");
  if(( conn_fd = accept(listen_fd,(struct sockaddr*)&cin,&len) ) < 0){
      perror("accept");
      exit(1);
  }

  printf("client %s  connnected\n",inet_ntoa(cin.sin_addr));
  
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

  close(listen_fd);
  close(conn_fd);


  return 0;
}







