#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define leng 300
#define wide 200

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
      printf("please input source logo!\n");
      printf("./main [src] [des]!\n");
      return -1;
  }
  
  FILE *in,*out;
  unsigned short * buf;
  in = fopen(argv[1],"rb");
  out = fopen(argv[2],"wb");
  buf = malloc(leng*wide*2+70);
  fread(buf,1,leng*wide+70,in);
  int i;
  for(i =35;i<leng*wide+35;i++)
  {
    if(buf[i] != 0x0000)
      buf[i]=0xBDB7;
  }

  fwrite(buf,1,leng*wide*2+70,out);
  fclose(in);
  fclose(out);
  return 0;
}
