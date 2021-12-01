exe: ConcurrencyParallelism.o mapCon.o
	g++ -o exe ConcurrencyParallelism.o mapCon.o -fopenmp -pthread

ConcurrencyParallelism.o: ConcurrencyParallelism.cpp settings.h mapCon.h
						 g++ -c ConcurrencyParallelism.cpp -fopenmp -pthread

mapCon.o: mapCon.cpp settings.h
		 g++ -c mapCon.cpp -fopenmp -pthread 
