/*
Author: Sikai Zhao
Class: ECE 6122
Date: August 24th, 2019

Discription: Homework 1 Question 1
*/

#include <iostream>
using namespace std;

/*
 * Function name: Main
 * Summary: Implement the algorithm to calculate the amount of number 1 to be added to the starting number
 * Parameters: Input the starting number, n
 * Return: The message of the amount of 1 to be added
 */
int main()
{
    int operatingNum = 0;
    int addedNum = 0;               // Define and initialize the stating number and amount of added number

    cout << "Please enter the starting number n: " ;
    cin >> operatingNum;            //Input the staring number
    while (operatingNum != 1)       //Do the add and check until operatingNum equals to 1
    {
        if (operatingNum % 7 == 0)  //Check if operatingNum can be divided by 7
        {
            operatingNum /= 7;      //Divide it
        }
        else
        {
            operatingNum++;         //Add 1 to the operatingNum
            addedNum++;             //Count the amount of number 1 added
        }
    }
    cout << "The sequence had " << addedNum << " instances of the number 1 being added" << endl;    //Output the result
    //while (true){                 //If we want to repeat this process for a single run, we can put the code in while loop
    //addedNum = 0;                 //Initiate the variable after a loop
    // operatingNum = 0;}

    return 0;
}