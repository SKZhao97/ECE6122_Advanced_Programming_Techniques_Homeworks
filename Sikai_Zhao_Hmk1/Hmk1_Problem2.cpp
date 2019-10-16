/*
Author: Sikai Zhao
Class: ECE 6122
Date: August 24th, 2019
Discription: Homework 1 Question 2
*/

#include<iostream>
#include<iomanip>
using namespace std;

/*
 * Function name: Main
 * Summary: Calculate the value of an integral using the midpoint rule
 * Parameters: Input the value of the upperLimit of the integral, upperLimit and subdivision number, subdivisionNum
 * Return: The result of the calculation of the integral
 */
int main()
{
    unsigned long subdivisionNum;               //Define the amount of subdivision
    double upperLimit = 0;                      //Define the upperlimit
    double midPosition = 0;                     //Define the position of the mid[point
    double midHeigh = 0;                        //Define the height of the midpoint
    double recWidth = 0;                        //Define the width of each rectangular
    double interValue = 0;                      //Define the value of the integral

    cout << "Please enter a value for the upper limit (beta): ";
    cin >> upperLimit;
    cout << "Please enter the number of subdivisions to use: ";
    cin >> subdivisionNum;                      //Input the amount of subdivision and upperlimit
    recWidth = (upperLimit - 0)/subdivisionNum; //Calculate the width of the small rectangular

    for (int i = 0; i < subdivisionNum; i++)
    {
        midPosition = i * recWidth + recWidth / 2;      //Calculate the midpoint position
        midHeigh = 4 / (midPosition*midPosition + 1);   //Calculate the value of the function at midpoint
        interValue += midHeigh * recWidth;              //Calculate the sum of the area of all the small rectangular
    }

    cout << "The integral evaluates to:" << setprecision(16)<<interValue << endl;   //Output the result of calculation
    //while (true){}           //If we want to repeat the calculation at a single run, we can put the code in while loop
}