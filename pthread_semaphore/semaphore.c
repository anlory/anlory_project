#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


#define NUM  5
int queue[5] = {0};
int counter = 0;

sem_t s_blank,s_product;

void * do_thread(void *arg)
{	
	int p =0;
	if((int)arg == 1){
		printf("here is consumer\n");
		while(1){
			sem_wait(&s_blank);
			queue[p] = rand()%100 +1;
			printf("Produce %d\n",queue[p]);
			sem_post(&s_product);
			p = (p+1)%NUM;
			sleep(rand()%5);
		}
		
	}else{
		printf("here is Producer\n");
		while(1){
			sem_wait(&s_product);
			printf("Consume %d\n",queue[p]);
			queue[p] = 0;
			sem_post(&s_blank);
			p = (p+1)%NUM;
			sleep(rand()%5);
		}
	}
	return NULL;
}


int main(int argc,char ** argv)
{
	pthread_t t[2];
	int i;
	sem_init(&s_blank,0,NUM);
	sem_init(&s_product,0,0);
	
	for(i;i<2;i++)
		pthread_create(&t[i],NULL,do_thread,i);
	


	for(i = 0;i<10;i++)
		pthread_join(t[i], NULL);
	sem_destroy(&s_blank);
	sem_destroy(&s_product);
	
	return 0;
}

