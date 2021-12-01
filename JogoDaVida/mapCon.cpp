// C++	//
#include <iostream>
#include <omp.h>

// Personal	//
#include "mapCon.h"

MapCon::MapCon() {
	// Alocando
	grid = (int**)malloc(LENGTH * sizeof(int*));

#pragma omp parallel for
	for (int i = 0; i < LENGTH; i++)
		grid[i] = (int*)malloc(LENGTH * sizeof(int));

	if (!grid) std::cout << "Error to allocate grid on first usage" << std::endl;

	//	Limpando grid
#pragma omp parallel for
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			grid[i][j] = MORTO;
		}
	}

}

void MapCon::showState(int initial, int end) {
	//	Imprime
	for (int i = initial; i < end; i++) {
		for (int j = initial; j < end; j++) {

			if (grid[i][j] == 1)
				std::cout << (char)254;
			else
				std::cout << " ";
			std::cout << " | ";
		}
		std::cout << std::endl << std::endl;
	}
}

void MapCon::setFirstGrid() {
	// Glider
	int lin = 1, col = 1;

	grid[lin][col + 1] = VIVO;
	grid[lin + 1][col + 2] = VIVO;
	grid[lin + 2][col] = VIVO;
	grid[lin + 2][col + 1] = VIVO;
	grid[lin + 2][col + 2] = VIVO;

	// R-Pentonimo
	lin = 10; col = 30;

	grid[lin][col + 1] = VIVO;
	grid[lin][col + 2] = VIVO;
	grid[lin + 1][col] = VIVO;
	grid[lin + 1][col + 1] = VIVO;
	grid[lin + 2][col + 1] = VIVO;

}

int MapCon::rp(int i) {
	int limited_number;
	limited_number = i % LENGTH;	//valor negativo ou positivo dentro do tamanho do grid

	return (limited_number >= 0) ? limited_number : LENGTH - std::abs(limited_number);	// Anda para tras se necessário
}

int MapCon::getNeighbours(int i, int j) {
	int ng = 0;	// quantidade de vizinhos

	ng += grid[rp(i - 1)][rp(j - 1)];
	ng += grid[rp(i - 1)][rp(j)];
	ng += grid[rp(i - 1)][rp(j + 1)];

	ng += grid[rp(i)][rp(j - 1)];
	ng += grid[rp(i)][rp(j + 1)];

	ng += grid[rp(i + 1)][rp(j - 1)];
	ng += grid[rp(i + 1)][rp(j)];
	ng += grid[rp(i + 1)][rp(j + 1)];

	return ng;
}

int MapCon::applyRules(int ng, int i, int j, int flag) {
	int state = 0;
	state = grid[i][j];
	if (grid[i][j] == VIVO) {
		// Se vivo

		if (ng < 2 || ng > 3) {
			// Se menos que 2 vizinhos ou acima de 3
			state = MORTO;
		}
	}
	else if (grid[i][j] == MORTO) {
		// Se morto

		if (flag == JOGO_DA_VIDA) {
			// Versão jogo da vida

			if (ng == 3) {
				// Com 3 vizinhos
				state = VIVO;
			}
		}
		else if (flag == HIGHLIFE) {
			// Versão Highlife

			if (ng == 3 || ng == 6) {
				// Com 3 vizinhos ou 6
				state = VIVO;
			}
		}
	}
	else {
		std::cout << "Some error occured, cell with invalid state" << std::endl << "Cell will be considered DEAD";
		state = MORTO;
	}
	return state;
}

int** MapCon::nextGen(int flag) {
	int** newGrid;
	int t_ng = 0;	// Quantidade de vizinhos

	// Alocação de memoria da proxima geração
	newGrid = (int**)malloc(LENGTH * sizeof(int*));

#pragma omp parallel for
	for (int i = 0; i < LENGTH; i++) {
		newGrid[i] = (int*)malloc(LENGTH * sizeof(int));
	}

	if (newGrid == NULL) std::cout << "Failed to create new generation grid" << std::endl;

#pragma omp parallel for private(t_ng)
	for (int i = 0; i < LENGTH; i++) {
		// Cada linha

		for (int j = 0; j < LENGTH; j++) {
			// Cada coluna

			t_ng = getNeighbours(i, j);						// Quantidade de vizinhos
			newGrid[i][j] = applyRules(t_ng, i, j, flag);	// Aplicação das regras sobre a celula
		}
	}
	return newGrid;
}

int MapCon::NSocietya() {
	int society = 0;

#pragma omp parallel for
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
#pragma omp critical
			society += grid[i][j];
		}
	}
	return society;
}


int MapCon::NSocietyb() {
	int society = 0;

#pragma omp parallel for reduction(+:society)
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			society += grid[i][j];
		}
	}
	return society;
}


int MapCon::NSocietyc() {
	int society = 0;

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			society += grid[i][j];
		}
	}
	return society;
}



void MapCon::setGrid(int** newGrid) {
	for (int i = 0; i < LENGTH; i++)
		free(grid[i]);
	free(grid);
	grid = newGrid;
}

MapCon::~MapCon() {
	free(grid);
}
