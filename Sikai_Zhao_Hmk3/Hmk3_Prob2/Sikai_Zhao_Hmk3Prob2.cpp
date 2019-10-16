/*
Author:Sikai Zhao
Class: ECE6122
Last Date Modified: Oct 4, 2019
Description:
Use openMP to Find the four adjacent numbers in the matrix that have the largest product. Four threads are
created to do the four kinds of adjacent number check respectively.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <omp.h>
#include <ctime>
using namespace std;
/*
 * Function name: main
 * Summary: input a matrix from file and find the four adjacent numbers in the matrix that have the largest product,
 * finally write the results to the file
 * Parameters:
 * 1. input matrix from .txt file
 * 2. the number of rows and columns of the matrix, namely the first line of the .txt
 * Return: output the largest product of four adjacent numbers and the four numbers
 */
int main(int argc, char** argv) {
	int iRows, iCols;                               //Numbers of rows and columns of the matrix
	ifstream infile;
	infile.open(argv[1]);

	clock_t start, end;
	infile >> iRows >> iCols;                           //Input the numbers of rows and columns, namely the first line
	vector<vector<int> > inMatrix(iRows);            //Define the 2-D vector that stores the matrix

	for (int i = 0; i < iRows; i++)
	{
		if (!infile.eof())
		{
			inMatrix[i] = vector<int>(iCols);
			for (int j = 0; j < iCols; j++)
			{
				if (!infile.eof())
				{
					infile >> inMatrix[i][j];       //Initialize the 2-D vector according to the matrix
				}
			}
		}
	}
	infile.close();                               //Close the file

	int largeProduct = 0;                           //Define the integers that store the largest prioduct
	//int procNum[4];                                 //Define the array that stores the four numbers for largeset product
	start = clock();
		for (int y = 0; y < iRows; y++)
			for (int x = 0; x < iCols; x++)             //Check all the elements
			{
#pragma omp sections                                    //Define the openMP sections
{

#pragma omp section                                     //openMP thread for horizontal numbers
				if (x + 3 < iRows)                       //Check four horizontal numbers (left-right)
				{
					int curProduct = inMatrix[x][y] * inMatrix[x + 1][y] * inMatrix[x + 2][y] * inMatrix[x + 3][y];//Calculate product
					if (largeProduct < curProduct)
					{
						largeProduct = curProduct;
						//Store the numbers and proiduct if the priduct is larger than the current one
					}
				}
#pragma omp section                                     //openMP thread for vertical numbers
				if (y + 3 < iCols)                      //Do the same operations to the four vertical numbers(up-down)
				{
					int curProduct = inMatrix[x][y] * inMatrix[x][y + 1] * inMatrix[x][y + 2] * inMatrix[x][y + 3];
					if (largeProduct < curProduct)
					{
						largeProduct = curProduct;
					}
				}
#pragma omp section                                     //openMP thread for diagonal numbers(left-down)
				if (x + 3 < iRows && y + 3 < iCols)     //Do the same operations to the four diagonal numbers(left-down)
				{
					int curProduct = inMatrix[x][y] * inMatrix[x + 1][y + 1] * inMatrix[x + 2][y + 2] * inMatrix[x + 3][y + 3];
					if (largeProduct < curProduct)
					{
						largeProduct = curProduct;
					}
				}
#pragma omp section                                     //openMP thread for diagonal numbers(right-down)
				if (x + 3 < iRows && y - 3 >= 0)        //Do the same operations to the four diagonal numbers(right-down)
				{
					int curProduct = inMatrix[x][y] * inMatrix[x + 1][y - 1] * inMatrix[x + 2][y - 2] * inMatrix[x + 3][y - 3];
					if (largeProduct < curProduct)
					{
						largeProduct = curProduct;
					}
				}
			}
	}
	ofstream outfile;
	outfile.open("output2.txt");             //Open the output2.txt file
	outfile << largeProduct << endl;
	outfile.close();                                //Close the files
	end = clock();
	cout << "Total time" <<fixed<< setprecision(12)<< double(end - start) / CLOCKS_PER_SEC << endl;
}
