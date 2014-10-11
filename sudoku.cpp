#include "stdafx.h"
#include "sudoku.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Sudoku::Sudoku()
{
	char number[10];
	cout << "Grid number : ";
	cin >> number;
	string gridfile = "C:/Users/Florian/Downloads/C++/SudokuSolver/SudokuSolver/grids/grid";
	gridfile.insert(gridfile.size(), number);
	gridfile.insert(gridfile.size(), ".txt");

	ifstream streamGrid(gridfile);
	if (!streamGrid){ cout << "Unable to read grid file" << endl; return; }

	string lineRead;
	for (int i = 0; i < 9; ++i){
		getline(streamGrid, lineRead);
		for (int j = 0; j < 9; ++j){
			if (lineRead[j] == '.') { grid[i][j] = 0; initialGrid[i][j] = 0; }
			else { grid[i][j] = lineRead[j] - 48; initialGrid[i][j] = lineRead[j] - 48; }
		}
	}
}


Sudoku::~Sudoku()
{
}

void Sudoku::printGrid(){
	for (int i = 0; i < 9; ++i){
		for (int j = 0; j < 9; ++j){
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}

}

void Sudoku::bruteForce(){
	int value = 1;
	bool advance = false;
	int i = 0, j = 0;
	while (i!=8 || j!=8){
		if (j == 8){
			cout << "jsuis a 8";
		}
		cout << i << "," << j<<endl;
			//cout << "je matte " << i << "," << j << endl;
			if (checkColumn(j, value) == 0 && checkRow(i, value) == 0 && checkSquare(i, j, value) == 0){
				//cout << value << " marche en " << i << "," << j<<endl;
				grid[i][j] = value;

				keepAdvancing:
				if (j == 8){ ++i; j = 0; }
				else ++j;
				if (initialGrid[i][j] != 0) goto keepAdvancing;
				cout << "javance en " << i << "," << j << endl;
				value = 1;
				//cout << endl << endl;
				//printGrid();
			}

			else if (value == 9){//backtrack
				
				keepBacktracking:
				if (j != 0) --j;
				else{ 
					--i; j = 8;}
				if (initialGrid[i][j] != 0) goto keepBacktracking;
				cout << "backtrack en " << i << "," << j << endl;

				if (grid[i][j] != 9) {
					value = grid[i][j] + 1; grid[i][j] = 0;
				}
				else goto keepBacktracking;

				//cout << endl << endl;
				//printGrid();
			}

			else{
				//cout << value << " marche pas en " << i << "," << j << endl;
				++value; //cout << endl << endl; printGrid();
			}
		
	}
	printGrid();
	
}

int Sudoku::checkCell(int i, int j, int value){
	return 0;

}

int Sudoku::checkRow(int i, int value){
	int *ptr = &grid[i][0];
	if (*ptr == value) { return -1; }
	for (i = 1; i <= 9; ++i)
	{
		++ptr;
		if (*ptr == value) { return -1; }
	}
	{return 0; }
}

int Sudoku::checkColumn(int i, int value){
	int *ptr = &grid[0][i];
	if (*ptr == value) {  return -1; }
	for (i = 1; i < 9; ++i)
	{
		ptr+=9;
		if (*ptr == value) { return -1; }
	}
	{ return 0; }
}

int Sudoku::checkSquare(int i,int j, int value){
	int squareI = floor(i / 3);
	int squareJ = floor(j / 3);
	int *ptr = &grid[squareI*3][squareJ*3];
	if (*ptr == value) { return -1; }
	for (i = 1; i <=3; ++i)
	{
		++ptr;
		if (*ptr == value) {  return -1; }
		++ptr;
		if (*ptr == value) { return -1; }
		if (i != 3){
			ptr += 7;
			if (*ptr == value) { return -1; }
		}
	}
	return 0;
}