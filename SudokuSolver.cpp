// SudokuSolver.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "sudoku.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Sudoku sudoku;
	sudoku.printGrid();
	sudoku.bruteForce();
	system("pause");
	return 0;
}


