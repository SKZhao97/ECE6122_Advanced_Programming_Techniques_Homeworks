/*
Author: Sikai Zhao
Class: ECE 6122
Date: August 28th, 2019

Discription: Homework 1 Question 3
*/

#include <iostream>
using namespace std;

unsigned long knightNum;                        //Define the number of knights
const unsigned long Max=1000;                   //Define the maximum for the following Arrays
unsigned long knightValue[Max];                 //Define an Array to store the number of knight, the subscript is the seats in order of clockwise
unsigned long knightTable[Max];                 //Define an Array to store if a certain knight has been arranged, the subscript is number of knights
unsigned long fibonacciArray[Max];              //Define an Array to store Fibonacci numbers
bool Succeed=false;                             //Define a symbol of having found the solution
bool Match=false;                               //Define a symbol that the sum of nearby two knights is fibonacci number


/*
 * Function name: Fibonacci
 * Summary: Calculate fibonacci number based on mathematical calculation
 * Parameters:
 *      fibNum: An unsigned long int meaning it is the "fibNum th" fibonacci number
 * Return: The value of "fibNum th" fibonacci number, unsigned long
 */
unsigned long Fibonacci(unsigned long fibNum)
{
    unsigned long firstNum = 0;
    unsigned long secondNum = 1;
    unsigned long thirdNum = 0;
    for (unsigned long i = 2; i <= fibNum; i++)             //Calculate the fibonacci number
    {
        thirdNum = firstNum + secondNum;
        firstNum = secondNum;
        secondNum = thirdNum;
    }
    return thirdNum;
}

/*
 * Function name: fibonacciCheck
 * Summary: Check if a input number is a fibonacci number
 * Parameters:
 *      checkNum: An unsigned long int to be checked, which is the sum of the number of nearby two knights
 * Return: Bool Match, if checkNum is fibonacci number, Match is true, else is false
 */
bool fibonacciCheck(unsigned long checkNum)  // A funtion to check if the nearby two numbers add to be fibonacci number
{
    Match = false;
    for (int i=0;i<Max;i++)                 //Find if checkNum is in the Array of the fibonacci Array
    {
        if (fibonacciArray[i] == checkNum)
        {
            Match = true;                   //If found, mark the symbol as true
            break;                          //Exit the loop
        }
    }
    return Match;
}

/*
 * Function name: Permutation
 * Summary: Find the solution of how to arrange the knights based on simplified permutation
 * Parameters:
 *      knightPosition: An unsigned long int, meaning the "knightPosition th" seat
 * Return: if there is solution, output the first solution,. which is unsigned long knightValue[]
 */
void Permutation(unsigned long knightPosition)      //A function to get permutation based on hash table
{
    if (knightPosition == knightNum + 1)            //Check is a permutation is finished, the knightPosition will be knightNum+1 when it happens
    {
        cout<<"The knights should sit clockwise as follows: K, ";
        Succeed=true;                               //Mark the succeed symbol as true
        for (unsigned long i = 1; i < knightNum; i++)
            cout<<knightValue[i]<<", ";
        cout<<knightValue[knightNum]<<endl;         //Output the knightArray
        cout<<endl;
        return;
    }
    for (unsigned long j = 1; j <= knightNum; j++)
    {
        if (knightTable[j] == false)                //Check if the knight number has not been used
        {
            knightValue[knightPosition] = j;        //If the knight has not been arranged, then arrange a position
            if(knightPosition!=1&&fibonacciCheck(knightValue[knightPosition]+knightValue[knightPosition-1])==false)
                continue;                           //Check if the sum is a fibonacci number and jump to next loop if not
            knightTable[j] = true;
            Permutation(knightPosition + 1);    //Recursion to operate the next position
            knightTable[j] = false;                 //Clear the records after return
            if(Succeed==true)                       //Check if we have already got the first solution, if yes, break
                break;                              //If we want to output all the possible solutions, we can delete these two lines
        }
    }
}

/*
 * Function name: Main
 * Summary: Input the amount of knights, calculate the fibonacci numbers needed, find the solution and output no solution message
 * Parameters: Input the amount of knights
 * Return: if there is no solution, output "No Solution Found"
 */
int main()
{
    cout<<"Please input the number of knights: ";
    cin>>knightNum;                                 //Input the number of knights
    for (unsigned long i=0;;i++)
    {
        if (Fibonacci(i) > knightNum * 2 - 1)
            break;
        fibonacciArray[i] = Fibonacci(i);           //List all the possible Fibonacci numbers
    }
    Permutation(1);                    //Find the solution based on recursion
    if(Succeed==false)
        cout<<"No Solution Found!"<<endl;           //Output the message if no solution found
    return 0;
}