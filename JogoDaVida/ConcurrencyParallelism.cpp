// Concurrency and Parallelism
// Israel da Rocha


// C++	//
#include <iostream>
#include <omp.h>
#include <ctime> 
#include <chrono>
#include <pthread.h>
#include <unistd.h>
#include <vector>

//	Personal	//
#include "mapCon.h"
#include "settings.h"

int gate1 = 0, gate2 = 0, icont = 0;
std::vector<bool> wants;
std::vector<int> total_neighbour;
int** finalGrid;

void* sum(void* tid);

int main()
{
	MapCon* obj = new MapCon();
	int** newGrid;
	int i = 1;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;
	std::chrono::duration<double, std::milli> execTime[3];
	std::chrono::duration<double, std::milli> serialExecTime;
	int qthread[] = {1,2,4,8};

	omp_set_num_threads(N_TRHEADS);
	
	obj->setFirstGrid();

	obj->showState(0,50);
//	for (i = 1; i < N_GEN; i++) {
//		
//		newGrid = obj->nextGen(JOGO_DA_VIDA);
//		
//		obj->setGrid(newGrid);
//
//	}
	std::cout << "Ultima geração" << std::endl;

	obj->showState(0,50);

	std::cout << "-Info-" << std::endl;
	std::cout << "a - Critical Section" << std::endl << "b - Parallel" << std::endl << "c - Serial" << std::endl << std::endl;

	for(int j = 0; j < 4; j++){
	std::cout << "##############################################" << std::endl << std::endl;

		omp_set_num_threads(qthread[j]);	// Thread_num

		startTime = std::chrono::high_resolution_clock::now();
		std::cout << "Geracao " << i << ": " << obj->NSocietya() << std::endl;
		endTime = std::chrono::high_resolution_clock::now();
		execTime[0] = endTime-startTime;

		startTime = std::chrono::high_resolution_clock::now();
		std::cout << "Geracao " << i << ": " << obj->NSocietyb() << std::endl;
		endTime = std::chrono::high_resolution_clock::now();
		execTime[1] = endTime-startTime;


		startTime = std::chrono::high_resolution_clock::now();
		std::cout << "Geracao " << i << ": " << obj->NSocietyc() << std::endl;
		endTime = std::chrono::high_resolution_clock::now();
		execTime[2] = endTime-startTime;
		serialExecTime = execTime[2];

		std::cout << std::endl;
		std::cout << "- Time for " << qthread[j] << " Threads -" << std::endl;
		std::cout << "a - " << execTime[0].count()/1000 << "s" << std::endl; 
		std::cout << "b - " << execTime[1].count()/1000 << "s" << std::endl; 
		std::cout << "c - " << execTime[2].count()/1000 << "s" << std::endl;
		std::cout << std::endl;
		std::cout << "-Speedup-" << std::endl;
		std::cout << "a - " << (serialExecTime.count()/execTime[0].count()) << std::endl; 
		std::cout << "b - " << (serialExecTime.count()/execTime[1].count()) << std::endl; 
		std::cout << "c - " << (serialExecTime.count()/execTime[2].count()) << std::endl;
	}

//
//	finalGrid = obj->grid;
//	int n_threads = 2;
//	wants = std::vector<bool>(n_threads, false);
//	
//	pthread_t threads[n_threads];	
//	int tids[n_threads];			// Threads IDs
//	total_neighbour = std::vector<int>(n_threads,0);
//
//
//	for(int i = 0; i < n_threads; i++){
//		tids[i] = i+1;
//		pthread_create(&threads[i], NULL, sum, &tids[i]);
//	}
//	for(int i = 0; i < n_threads; i++){
//		pthread_join(threads[i], NULL);
//	}
//	std::cout << std::endl;
//	for(int i = 0; i < 50; i++){
//		for(int j = 0; j < 50; j++)
//			std::cout << finalGrid[i][j] << " ";
//		std::cout << std::endl;
//
//	}
//	for(int i = 0; i < wants.size(); i++)
//		std::cout << "Wants is " << wants[i] << " " << std::endl;
//	std::cout << "Wants size is " << wants.size() << std::endl;
//	int total_sum = 0;
//	for(int i : total_neighbour){
//		total_sum += i;
//	}
//	std::cout << "Result from impossible is: " << total_sum << std::endl;
}


void* sum(void* tid){
	int myID, myIdx, iMatrix;
	bool init1 = false, init2 = false, isAllFalse = false;

	myID = *(int*)tid;
	myIdx = myID-1;


	while(icont < LENGTH){

		do{
			do{
				init1 = false;
				init2 = false;
				isAllFalse = false;

				wants[myID] = true;
				gate1 = myID;
				
				if(gate2 != 0){
					wants[myIdx] = false;
					init1 = true;
				}

			} while(init1);

			gate2 = myID;
			
			if(gate1 != myID){
				wants[myIdx] = false;

				// Wait all to be false
				while(!isAllFalse){
					for(bool state : wants){
						isAllFalse = (!state && true);
					}
				}
				std::cout << "AfterIsAllFalse" << std::endl;

				if(gate2 != myID){
					init2 = true;
				}
			}

		}while(init2);
		wants[myIdx] = true;
		
		// Seção Crítica
		iMatrix = icont;
		std::cout << "myID is " << myID << std::endl;
		icont++;
		// Fim da Seção Crítica
		
		gate2 = 0;
		wants[myIdx] = false;

		// Pós-protocolo
		
		for(int jMatrix; jMatrix < LENGTH; jMatrix++){
//			std::cout << "[i] [j]: " << iMatrix << " " << jMatrix << std::endl;
			total_neighbour[myIdx] += finalGrid[iMatrix][jMatrix];		
		}

	}
}
