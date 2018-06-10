#include <stdio.h>
#include <pthread.h>

#define NLOOP  50
int counter = 0;
int x,y;
//初始化mutex
pthread_mutex_t mutext = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


/*创建线程当x>y时进行操作*/
void * do_thread(void *arg)
{	
	int i;
	int thread = (int)arg;
	printf("thread:%d; enter  do_thread\n",thread);
	while(1){
		pthread_mutex_lock(&mutext);
		//while(x <= y){
			printf("thread:%d;when time %d \n",x>y);
			pthread_cond_wait(&cond,&mutext);
		//}
		printf("thread:%d;when time %d \n",x>y);
		/*
			here x > y;do something;
		*/
		printf("thread:%d;do something...\n",thread);
		//sleep(1);
		pthread_mutex_unlock(&mutext);
	}
	return NULL;
}


int main(int argc,char ** argv)
{
	pthread_t t[10];

	int i = 0;
//创建两个线程进行对conuter++
	for(i;i<10;i++)
		pthread_create(&t[i],NULL,do_thread,i);
	
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutext);
		/*
			here modify x and y and 唤醒线程
		*/
		if((i++)%3 == 0 ){
			x = 5;
			y = 3;
		}else{
			y = 5;
			x = 3;
		}

		if(x>y){
			printf("man thread siganl===============================\n");
			//pthread_cond_signal(&cond);
			pthread_cond_broadcast(&cond);//唤醒所有的线程
		}
		
		pthread_mutex_unlock(&mutext);
	}
	for(i = 0;i<10;i++)
	pthread_join(t[i], NULL);

	
	return 0;
}

