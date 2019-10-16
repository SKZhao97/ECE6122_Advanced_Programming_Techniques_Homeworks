/*
Author: Sikai Zhao
Class: ECE6122
Last Date Modified: September 15th, 2019
Description: Implement the functions and operators of Class ECE_Matrix
*/
#include "ECE_Matrix.h"
ECE_Matrix::ECE_Matrix()                                    //Default Constructor
{
    Rows=0;
    Cols=0;
}

ECE_Matrix::ECE_Matrix(int iLevel, double iVal)             //Constructor for the matrix that row equals to col
{
    Rows = iLevel;
    Cols = iLevel;
    for (int i =0;i<iLevel;i++)
    {
        vector<double> temp(iLevel,iVal);                   //Initialize the elements to be val
        inMatrix.push_back(temp);
    }
}

ECE_Matrix::ECE_Matrix(int iRows, int iCols, double iVal)   //Constructor for narmal matrix
{
    Rows = iRows;
    Cols = iCols;
    for (int i = 0;i<Rows;i++)
    {
        vector<double> temp(Cols,iVal);                     //Initialize the elements to be val
        inMatrix.push_back(temp);
    }
}

ECE_Matrix::ECE_Matrix(const string& filename)              //Constructor for Matrix from file
{
    int iRows, iCols;
    ifstream infile;
    infile.open(filename.c_str());                                  //Open the input file
    infile>>iRows>>iCols;                                   //Input the number of rows and columns
    Rows=iRows;
    Cols=iCols;
    inMatrix.resize(Rows);
    for (int i=0;i<Rows;i++)                                //Use for loop to initialize the 2-D vector
    {
        if (!infile.eof())
        {
            inMatrix[i].resize(Cols);
            for (int j=0;j<Cols;j++)
            {
                if (!infile.eof())
                {
                    infile>>inMatrix[i][j];
                }
            }
        }
    }
    infile.close();                                         //Close the file
}

ECE_Matrix ECE_Matrix::transpose() const                    //Implement the transpose of Matri
{
    ECE_Matrix Tran(Cols, Rows, 0);
    for (int i = 0; i < Tran.Rows; i++)
        for (int j = 0; j < Tran.Cols; j++)
            Tran.inMatrix[i][j]=inMatrix[j][i];
    return Tran;
}

ECE_Matrix& ECE_Matrix::operator=(const ECE_Matrix& matrix) //Operator "=" reload for two matrix
{
    if (this == &matrix)                                    //Check if it's self-assignment
    {
        return *this;
    }
    this->Cols = matrix.Cols;                               //Set the numbers of rows and columns
    this->Rows = matrix.Rows;
    //Size = matrix.Size;
    this->inMatrix.resize(this->Rows);
    for (int i=0;i<this->Rows;i++)
    {
        this->inMatrix[i].resize(this->Cols);
        for(int j=0;j<this->Cols;j++)
        {
            this->inMatrix[i][j]=matrix.inMatrix[i][j];     //Assignment
        }
    }

    return *this;                                           //Return
}

ECE_Matrix& ECE_Matrix::operator+=(const ECE_Matrix& matrix)        //Operator "+=" overload for two matrix
{
    int newRows=max(this->Rows, matrix.Rows), newCols=max(this->Cols,matrix.Cols);    //Reset the rows and cols
    ECE_Matrix temp(newRows, newCols,0);                        //Create intermidiate object
    for (int i1=0;i1<this->Rows;i1++)
        for(int j1=0;j1<this->Cols;j1++)
            temp.inMatrix[i1][j1]+=matrix.inMatrix[i1][j1];
    for (int i2=0;i2<matrix.Rows;i2++)
        for(int j2=0;j2<matrix.Cols;j2++)
            temp.inMatrix[i2][j2]+=matrix.inMatrix[i2][j2];         //Implement the addition operation
    *this = temp;                                                   //Assign result to the first object
    return *this;
}

ECE_Matrix& ECE_Matrix::operator-=(const ECE_Matrix& matrix)       //Operator "-=" overload for two matrix
{
    int newRows=max(this->Rows, matrix.Rows), newCols=max(this->Cols,matrix.Cols);  //Reset the rows and cols
    ECE_Matrix temp(newRows, newCols,0);                      //Create intermediate object
    for (int i1=0;i1<this->Rows;i1++)
        for(int j1=0;j1<this->Cols;j1++)
            temp.inMatrix[i1][j1]+=matrix.inMatrix[i1][j1];
    for (int i2=0;i2<matrix.Rows;i2++)
        for(int j2=0;j2<matrix.Cols;j2++)
            temp.inMatrix[i2][j2]-=matrix.inMatrix[i2][j2];         //Implement the substraction operation
    *this=temp;
    return *this;                                                   //Assign result to the first operator
}

ostream& operator<<(ostream& os, const ECE_Matrix& matrix)          //Operator "<<" overload for matrix
{
    for (int i=0;i<matrix.Rows;i++)
    {
        for (int j=0;j<matrix.Cols;j++)
        {
            os<<scientific<<setw(3) << setprecision(3)<<setfill('0')<<matrix.inMatrix[i][j]<<" ";
        }
        os<<endl;                                                   //Set the format for output
    }
    return os;
}

ECE_Matrix operator+(const ECE_Matrix& matrix1, const ECE_Matrix& matrix2)  //Operator "+" overload for two matrix
{
    int newRows=max(matrix1.Rows, matrix2.Rows), newCols=max(matrix1.Cols,matrix2.Cols);    //Reset rows and cols
    ECE_Matrix temp(newRows, newCols,0);        //Create new object
    for (int i1=0;i1<matrix1.Rows;i1++)
        for(int j1=0;j1<matrix1.Cols;j1++)
            temp.inMatrix[i1][j1]+=matrix1.inMatrix[i1][j1];
    for (int i2=0;i2<matrix2.Rows;i2++)
        for(int j2=0;j2<matrix2.Cols;j2++)
            temp.inMatrix[i2][j2]+=matrix2.inMatrix[i2][j2];        //Implement the addition operation
    return temp;                                                    //Directly return the new object
}

ECE_Matrix operator-(const ECE_Matrix& matrix1, const ECE_Matrix& matrix2)  //Operator "-" overload for two matrix
{
    int newRows=max(matrix1.Rows, matrix2.Rows), newCols=max(matrix1.Cols,matrix2.Cols);    //Reset rows and cols
    ECE_Matrix temp(newRows, newCols,0);                      //Create new object
    for (int i1=0;i1<matrix1.Rows;i1++)
        for(int j1=0;j1<matrix1.Cols;j1++)
            temp.inMatrix[i1][j1]+=matrix1.inMatrix[i1][j1];
    for (int i2=0;i2<matrix2.Rows;i2++)
        for(int j2=0;j2<matrix2.Cols;j2++)
            temp.inMatrix[i2][j2]-=matrix2.inMatrix[i2][j2];       //Implement the addition operation
    return temp;                                                   //Directly return the new object
}

ECE_Matrix operator+(const ECE_Matrix& matrix, double val)         //Operator "+" overload for a matrix and a number
{
    ECE_Matrix temp(matrix.Rows,matrix.Cols, 0);              //Create new object
    for (int i=0;i<matrix.Rows;i++)
        for(int j=0;j<matrix.Cols;j++)
            temp.inMatrix[i][j]=matrix.inMatrix[i][j]+val;         //Add val to every element
    return temp;
}

ECE_Matrix operator+(double val, const ECE_Matrix& matrix)         //Operator "+" overload for a number and a matrix
{
    ECE_Matrix temp(matrix.Rows,matrix.Cols,0);
    for (int i=0;i<matrix.Rows;i++)
        for(int j=0;j<matrix.Cols;j++)
            temp.inMatrix[i][j]=val+matrix.inMatrix[i][j];         //Add val to every element
    return temp;                                                   //Directly return the new object
}

ECE_Matrix operator-(const ECE_Matrix& matrix, double val)         //Operator "+" overload for a matrix and a number
{
    ECE_Matrix temp(matrix.Rows,matrix.Cols,0);               //Create new object
    for (int i=0;i<matrix.Rows;i++)
        for(int j=0;j<matrix.Cols;j++)
            temp.inMatrix[i][j]=matrix.inMatrix[i][j]-val;         //Substract val from every element
    return temp;                                                   //Directly return the new object
}

ECE_Matrix operator-(double val, const ECE_Matrix& matrix)         //Operator "+" overload for a number and a matrix
{
    ECE_Matrix temp(matrix.Rows,matrix.Cols,0);
    for (int i=0;i<matrix.Rows;i++)
        for(int j=0;j<matrix.Cols;j++)
            temp.inMatrix[i][j]=val-matrix.inMatrix[i][j];         //Substract the value of every element from val
    return temp;                                                   //Directly return the new object
}

ECE_Matrix operator*(const ECE_Matrix& matrix, double val)         //Operator "+" overload for a matrix and a number
{
    ECE_Matrix temp(matrix.Rows,matrix.Cols,0);               //Create a new object
    for (int i=0;i<matrix.Rows;i++)
    {
        for (int j=0;j<matrix.Cols;j++)
        {
            temp.inMatrix[i][j]=matrix.inMatrix[i][j]*val;         //Multiply every element by val
        }
    }
    return temp;                                                   //Directly return the new object
}

ECE_Matrix operator*(double val,const ECE_Matrix& matrix)          //Operator "+" overload for a number and a matrix
{
    ECE_Matrix temp(matrix.Rows, matrix.Cols, 0);             //Create a new object
    for (int i=0;i<matrix.Rows;i++)
    {
        for (int j=0;j<matrix.Cols;j++)
        {
            temp.inMatrix[i][j]=matrix.inMatrix[i][j]*val;         //Multiply every element by val
        }
    }
    return temp;                                                   //Directly return the new object
}

ECE_Matrix operator/(const ECE_Matrix& matrix, double val)         //Operator "/" overload for a matrix and a number
{
    ECE_Matrix temp(matrix.Rows,matrix.Cols,0);               //Create a new object
    if (val !=0)                                                   //Check if the elements are divided by zero
    {
        for (int i=0;i<matrix.Rows;i++)
        {
            for (int j=0;j<matrix.Cols;j++)
            {
                temp.inMatrix[i][j]=matrix.inMatrix[i][j]/val;     //If not, divide every element by val
            }
        }
    }
    else{
        for (int i=0;i<matrix.Rows;i++)
        {
            for (int j=0;j<matrix.Cols;j++)
            {
                temp.inMatrix[i][j]=0;                             //If yes, assign all the elements zero
            }
        }
    }
    return temp;                                                   //Directly return the new object
}
