#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdatomic.h>
#include <stdlib.h>

const uint8_t MIN_THREAD = 0;
#define MAX_THREAD 3

int queue[MAX_THREAD];

void* foo(void *argumenty);
int curennt_in_service;


struct thread_data {
	int number;
	int queue;
	_Atomic int curennt_in_service;
} TD;

pthread_mutex_t start_mutex;

int main()
{    
   printf("Uruchamiam watki....\n");
   pthread_mutex_init(&start_mutex, NULL);

    queue[0] = 0;
    queue[1] = 1;
    queue[2] = 2;
    
    TD.curennt_in_service = 1;
	
	printf("\nWatki powinny wykonac sie w takiej kolejnosci:");
	for(int i=0; i < MAX_THREAD - MIN_THREAD; i++)
		printf("%d -> ", queue[i]);
 
    for(int numerek = MIN_THREAD; numerek<MAX_THREAD; numerek++){
    	
    	TD.number = numerek;
    	TD.queue = queue[numerek];
    	
    	printf("Uruchamiam watek nr %d \n", numerek);
    	
    	pthread_t id_wystartowanego_watku_1;
    	
		pthread_create(&id_wystartowanego_watku_1, NULL, foo, &TD);
		pthread_detach(id_wystartowanego_watku_1);
		
	}
	
	printf("\nKoniec uruchamiania....\n");
	//while(1){
		//printf("A");
	//};
    exit(EXIT_SUCCESS);
}

void* foo(void *argumenty) {
	
	struct thread_data *TD = argumenty;
	
	///critical section - copy starting data
	printf("czekam na mutex");
    pthread_mutex_lock(&start_mutex);
    printf("doczekalem sie");
	struct thread_data TD_lokalny;
	TD_lokalny.number = TD->number;
	TD_lokalny.queue = TD->queue;
	
	
	//pthread_detach(pthread_self());
	sleep(1);
	printf("W�tek nr %d, ma miejsce w kolejce nr %d\n", (TD_lokalny.number), (TD_lokalny.queue));
	pthread_mutex_unlock(&start_mutex);
	
	//if((IN_REG1 & 2) && IN_REG1 & 0x01)

    
	while(TD->curennt_in_service != TD_lokalny.queue ){
		printf("%d", TD_lokalny.queue);	
	}
	TD->curennt_in_service++;
	
	///
	
	if(TD->curennt_in_service < (MAX_THREAD - 1))
		return 0;
	pthread_exit(NULL);

	//po przej�ciu spin_locka
}

