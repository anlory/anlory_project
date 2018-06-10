#include <stdio.h>
#include <pthread.h>

#define NLOOP  50
int counter = 0;

//初始化mutex
pthread_mutex_t mutext = PTHREAD_MUTEX_INITIALIZER;

void * do_add(void *arg)
{
	int i;
	for(i = 0; i < NLOOP; i++){
		pthread_mutex_lock(&mutext);
		counter++;
		printf("thread %d:%d\n", (int)arg,counter);
		
		pthread_mutex_unlock(&mutext);
		sleep(1);
	}
	return NULL;
}


int main(int argc,char ** argv)
{
	pthread_t t1,t2;
	int t1_arg = 1;
	int t2_arg = 2;
//创建两个线程进行对conuter++
	pthread_create(&t1,NULL,do_add,t1_arg);
	pthread_create(&t2,NULL,do_add,t2_arg);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	return 0;
}

