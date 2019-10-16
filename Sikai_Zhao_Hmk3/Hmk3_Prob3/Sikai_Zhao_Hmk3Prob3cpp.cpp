/*
Author: Sikai Zhao
Class: ECE6122
Last Date Modified: Oct 5th, 2019
Description: Using openMP to find the maximum sum path of the input triangle of numbers
*/
#include <iostream>
#include <fstream>
#include <omp.h>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;
int maxSum = 0;               //Define the integer that store the maximum sum
/*
 * Function name: maxPath
 * Summary: Search and find the path in the triangle with maximum sum and store the maximum and path
 * Parameters:
 * 1. matrix: the matrix that stores the triangle of numbers (vector<vector<int>>)
 * 2. pathArray: the 3-D vector that stores maximum path staring from each element(vector<vector<vector<int>>>)
 * 3. m: the number of rows and columns of the matrixes, namely the levels of the triangle
 * Return: The maximum sum, and stores the path in global variable, Path.
 */
int maxPath(vector<vector<int> > matrix, int m)
{
	for (int i = m - 2; i >= 0; i--)                //Start from the second line from below
	{
//#pragma omp for
		for (int j = 0; j <= i; j++)                //Check all the numbers on the line
		{
			if (matrix[i + 1][j] > matrix[i + 1][j + 1])//Compare the element under current number and the one on its right
			{
				matrix[i][j] += matrix[i + 1][j];   //Update the maximum sum for the current number
			}
			else
			{
				matrix[i][j] += matrix[i + 1][j + 1];
			}
		}
	}
	maxSum = matrix[0][0];                           //Store the maximum sum
	return maxSum;
}
/*
* Function name: main
* Summary: input the triangle of number from file and define the matrix, then call the function to find the maximum
 * sum path, finally output the results to the file
* Parameters:
* input the triangle and its number of levels from file
* Return: find the maximum sum and path and write the path to the output3.txt
*/
int main(int argc, char** argv)
{
	const int NUM_THREAD = 2;               //Store the number of threads for openMP
	int iLevel;                             // Define the integer to store the levels of the triangle
	ifstream infile;
	infile.open(argv[1]);
	//infile.open("data_triangle.txt");     // Open the .txt file that stores the triangle
	infile >> iLevel;                       // Input the number of level which is the first line
	clock_t start, end;
	start = clock();
omp_set_num_threads(NUM_THREAD);            //Set the number of threads for openMP
#pragma omp parallel                        //Start a team of parallel threads
{
#pragma omp single                          //Let a single thread to implement the input and search
{
	vector<vector<int> > inMatrix(iLevel);  // Define the matrix of vector to store the triangle
	for (int i = 0; i < iLevel; i++)
	{
		if (!infile.eof())
		{
			inMatrix[i] = vector<int>(iLevel, 0);
			for (int j = 0; j <= i; j++)
			{
				if (!infile.eof())
				{
					infile >> inMatrix[i][j]; //Input the triangle from file to inMatrix
				}
				for (int k = i + 1; k < iLevel; k++)
					inMatrix[i][k] = 0;       //Set the positions 0 where there is no number
			}
		}
	}
	infile.close();                           //Close the .txt file
	maxPath(inMatrix, iLevel);                //Call the function that find the path
    }
}

	ofstream outfile;
	outfile.open("output3.txt");              //Open the output3.txt file to store the result
	outfile << maxSum << endl;
	outfile.close();                          //Close the file
	end = clock();
	cout << "Total time is: " << fixed<< setprecision(30)<<double(end - start) / CLOCKS_PER_SEC;
	return 0;
}
