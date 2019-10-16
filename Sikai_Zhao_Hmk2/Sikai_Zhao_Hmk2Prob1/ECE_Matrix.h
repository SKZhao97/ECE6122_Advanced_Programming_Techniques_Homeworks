/*
Author: Sikai Zhao
Class: ECE6122
Last Date Modified: September 15th, 2019
Description: Define the Class ECE_Matrix
*/
#ifndef TEST_1_ECE_MATRIX_H
#define TEST_1_ECE_MATRIX_H
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

class ECE_Matrix {
    int Cols;                                    //Number of rows
    int Rows;                                    //Number of columns
    vector<vector<double> > inMatrix;               //2-demension vector to store the matrix
public:
    ECE_Matrix();                                   //Default Constructor
    ECE_Matrix(int iLevel, double iVal);            //Constructor for matrix whose rows equals cols
    ECE_Matrix(int iRows, int iCols, double iVal);  //Constructor for normal matrix
    explicit ECE_Matrix(const string& filename);    //Constructor for matrix from file
    ECE_Matrix transpose() const ;                  //Transpose
    ECE_Matrix &operator=(const ECE_Matrix&);       //Operator overload for "="
    ECE_Matrix &operator+=(const ECE_Matrix&);      //Operator overload for "+="
    ECE_Matrix &operator-=(const ECE_Matrix&);      //Operator overload for "-="

    friend ostream& operator<<(ostream& os, const ECE_Matrix&);             //Operator overload for "<<"
    friend ECE_Matrix operator+(const ECE_Matrix&, const ECE_Matrix&);      //Operator overload for "<<"(2 matrix)
    friend ECE_Matrix operator-(const ECE_Matrix&, const ECE_Matrix&);      //Operator overload for "-"(2 matrix)
    friend ECE_Matrix operator+(const ECE_Matrix&, double val);             //Operator overload for "+"(matrix and number)
    friend ECE_Matrix operator+(double val, const ECE_Matrix&);             //Operator overload for "+"(number and matrix)
    friend ECE_Matrix operator-(const ECE_Matrix&, double val);             //Operator overload for "-"(matrix and number)
    friend ECE_Matrix operator-(double val, const ECE_Matrix&);             //Operator overload for "-"(number and matrix)
    friend ECE_Matrix operator*(const ECE_Matrix&, double val);             //Operator overload for "*"(matrix and number)
    friend ECE_Matrix operator*(double val, const ECE_Matrix&);             //Operator overload for "*"(number and matrix)
    friend ECE_Matrix operator/ (const ECE_Matrix&, double val);            //Operator overload for "/"(matrix and number)
};
#endif //TEST_1_ECE_MATRIX_H
