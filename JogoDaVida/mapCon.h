#pragma once

//	C++	//
#include <vector>

// Personal	//
#include "settings.h"


class MapCon {
public:
	// Inicia sociedade com estado padrao
	void setFirstGrid();

	// Calcula proxima geração
	int** nextGen(int flag = JOGO_DA_VIDA);

	// Obtem quantidade de vivos
	int NSocietya();

	int NSocietyb();
	
	int NSocietyc();
	
	// Imprime interface visual da sociedade dentro de um quadrado específico
	void showState(int initial = 0, int end = LENGTH);

	// Da novo valor à grid
	void setGrid(int** newGrid);

	MapCon();
	~MapCon();

	int** grid;

private:

	// Obtem quantidade de vizinhos
	int getNeighbours(int i, int j);

	// Aplica as regras de sobrevivência
	int applyRules(int ng, int i, int j, int flag = JOGO_DA_VIDA);

	// Retifica a posição de acordo com o tamanho do campo
	int rp(int i);
	
};
