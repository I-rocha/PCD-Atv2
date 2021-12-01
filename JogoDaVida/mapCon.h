#pragma once

//	C++	//
#include <vector>

// Personal	//
#include "settings.h"


class MapCon {
public:
	// Inicia sociedade com estado padrao
	void setFirstGrid();

	// Calcula proxima gera��o
	int** nextGen(int flag = JOGO_DA_VIDA);

	// Obtem quantidade de vivos
	int NSocietya();

	int NSocietyb();
	
	int NSocietyc();
	
	// Imprime interface visual da sociedade dentro de um quadrado espec�fico
	void showState(int initial = 0, int end = LENGTH);

	// Da novo valor � grid
	void setGrid(int** newGrid);

	MapCon();
	~MapCon();

	int** grid;

private:

	// Obtem quantidade de vizinhos
	int getNeighbours(int i, int j);

	// Aplica as regras de sobreviv�ncia
	int applyRules(int ng, int i, int j, int flag = JOGO_DA_VIDA);

	// Retifica a posi��o de acordo com o tamanho do campo
	int rp(int i);
	
};
