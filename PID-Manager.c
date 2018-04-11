#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<sys/types.h>
#include<unistd.h>
#define MIN_PID 100
#define MAX_PID 1000
#define SIZE MAX_PID-MIN_PID
// Declare our Bitmap
int bit_map[SIZE];

int allocate_map() {
	for(int i = 0; i < SIZE; i++) {
		bit_map[i] = 0; // Mark all as Available in Bitmap
	}
  printf("Process Bitmap initialized... \n");
	return 1;
}
int allocate_pid() {
	for(int i = 0; i < SIZE; i++) {
		if(bit_map[i] == 0) { // just make sure that pid is available
			bit_map[i] = 1; // Allocate a Pid to new process
      printf("New Process Allocated with PID : %d \n",(i+MIN_PID));
			return i + MIN_PID;
		}
	}
	return 1;
}
void release_pid(int pid) {
    if(MIN_PID<=pid<MAX_PID) {
      bit_map[pid-MIN_PID] = 0;
      printf("Process Released with PID : %d \n",pid);
    }
}

void *myThreadFun(void *vargp) {
    int pid = allocate_pid(); // Allocate a PID to each thread
    printf("Thread created will expire in 10ms \n");
    sleep(10); // Each thread run for 10 ms(time)
    release_pid(pid); // Finally Release PID to simulate releasing
    return NULL;
}

int main() {
    allocate_map();
    pthread_t tid;
    printf("Let's start creating Thread...\n");
    for (i = 0; i < 100; i++) { // Creating 100 Threads for testing
      pthread_create(&tid, NULL, myThreadFun, NULL);
    }
    exit(0);
}

