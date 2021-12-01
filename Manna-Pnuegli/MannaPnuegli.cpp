#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>

int request = 0;
int respond = 0;
int SOMA = 0;

void* client(void* id){
	int cid;
	int local;
	int sec = 1000000;

	cid = *(int*)id;	//Thread ID
	
	while(true){
		while(respond != cid){
			request = cid;
		}
		
		// Critical section
		std::cout << "Hi, I'm " << cid << " entering the CS" << std::endl;
		
		// Op
		local = SOMA;
		usleep((rand()%2)*0.5*sec);
		SOMA = local + 1;
		
		std::cout << "Soma is " << SOMA << std::endl;
		std::cout << "Hi, I'm " << cid << " leaving the CS" << std::endl << std::endl;
		respond = 0;
		
		// After Critical section
	}
}

void* server(void* ){
	int serv_sum = 0;
	while(true){
		while(request == 0);	// await
		respond = request;
		while(respond != 0);	// await
		request = 0;
		serv_sum++;
		std::cout << "Server sum: " <<  serv_sum << std::endl;
	}
}


int main(int argc, char** argv){
	int nt = -1;	//Number of threads
	char in;

	if(argc != 2){
		std::cout << "Error execution format" << std::endl;
		std::cout << "Correct: ./[executable] [num_threads]" << std::endl;
		return 1;
	}
	std::cout << "Press 'q' to stop execution of threads during processing" << std::endl;
	std::cout << "Press any button to continue now" << std::endl;

	getchar();
	system("clear");

	// Threads num
	nt = atoi(argv[1]);
	
	// Threads variables
	pthread_t tids[nt], sid;
	int cid[nt];

	//Creating server
	pthread_create(&sid, NULL, server, NULL);

	// Creating client
	for(int i = 0; i < nt; i++){
		cid[i] = i+1;
		pthread_create(&tids[i], NULL, client, &cid[i]);
	}
	
	// Exit option
	std::cin >> in;
	if(in == 'q'){
		std::cout << std::endl <<  "User wanted to quit" << std::endl;
		return 1;
	}

	pthread_exit(NULL);
	
	
return 1;
}

