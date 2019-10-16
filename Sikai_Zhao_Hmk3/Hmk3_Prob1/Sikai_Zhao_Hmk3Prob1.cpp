/*
Author:Sikai Zhao
Class: ECE6122
Last Date Modified: Oct 4, 2019
Description:
Use multithreading to find the number of lattice path, which is calculated based on "log" combination.
Because the factorials are large and cause overflow, I calculate the log of each number and calculate their sum and exp
Replacing the multiply with addition shortens the execution time used and increase the possible height and width. But to
satisfy the instruction of using multithreading, two threads were created and they increase the time.
*/
#include <iostream>
#include <iomanip>
#include <thread>
#include <cmath>
#include <cstring>
#include <stdlib.h>
#include <ctime>

using namespace std;
double sum1, sum2;              //Define global variable to store the sum of log, namely the log of factorial
/*
 * Function name: SUM1
 * Summary: Calculate the sum of log(m+1) to log(n), done by thread1
 * parameter:
 * 1. n: Height + Width
 * 2. m: The smaller one of Width and Height
 * Return: The sum of log(m+1) to log(n)
 */
double SUM1(int n, int m)       //The for loop of thread 1
{
    for (int i=m+1; i<=n; i++)
    {
        sum1 += log((double)i);
    }
    //cout<<sum1<<endl;
}
/*
 * Function name: SUM2
 * Summary: Calculate the sum of log(2) to log(n-m), done by thread2
 * parameter:
 * 1. n: Height + Width
 * 2. m: The smaller one of Width and Height
 * Return: The sum of log(2) to log(n-m)
 */
double SUM2(int n, int m)
{
    int k = n-m;
    for (int j=2; j<=k; j++)
    {
        sum2 += log((double)j);
    }
    //cout<<sum2<<endl;
}

/*
 * Function name: get_arg
 * Summary: Deal with input command line arguments: -h and -w
 * parameter:
 * 1. *str: the letter to check command line arguments
 * 2. argc: the number of input parameter
 * 3. **argv: the array of input parameters
 * Return: The position of the command line argument in the array
 */
int get_arg(const char *str, int argc, char **argv) {
    int i = 0;
    for (i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], str)) {
            if (i == argc - 1) {
                printf("Argument missing for %s\n", str);
                exit(1);
            }
            return i;
        }
    }
    return -1;
}
int main(int argc, char *argv[])
{
    int width=0, height=0, i=0;;                      //Initialize the width and height and i
    if((i = get_arg("-h", argc, argv)) > 0)
        height= atoi(argv[i+1]);
    if((i = get_arg("-w", argc, argv)) > 0)
        width = atoi(argv[i+1]);                      //If get_arg returns valid number, get the height and width
    int N=width+height;                 //Calculate the numbers for combination: N, the sum of height and width and
    int M=(width <= height? width:height);            //M, the smaller one of heigth and width

    clock_t start, end;
    start = clock();                    //Store the start time

    thread first (SUM1, N, M);
    thread second (SUM2, N, M);         //Create two threads to calculate the two for loops

    first.join();
    second.join();                      //Wait until the two thread finish

    cout.setf(ios::scientific, ios::floatfield);
    cout<<"Number of Routes: "<<std::fixed<<setprecision(0)<<round(exp(sum1-sum2))<<endl;//Output the number of routes
    end = clock();      //Store the end time
    cout<<"Total execution time is "<<setprecision(20)<<double(end-start)/CLOCKS_PER_SEC<<endl; //Output the time used
    return 0;
}