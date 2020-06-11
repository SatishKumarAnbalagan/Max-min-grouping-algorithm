//
//  main.cpp
//  Max_min_grouping
//
//  Created by Satish Kumar Anbalagan on 10/19/19.
//  Copyright © 2019 Satish Kumar Anbalagan. All rights reserved.
//
 
#include <iostream>
using namespace std;
 
#define ERROR_CODE_SUCESS               (0)
#define ERROR_CODE_FAILURE              (-1)
#define ERROR_CODE_INVALID_INPUT        (-1000)
#define ERROR_CODE_INVALID_PARAMETER    (-1001)
 
int **C = NULL;
int **Bmin = NULL;
int *G = NULL;
int *B = NULL;
 
/*
Function to print an array.
@param:
arr - array.
n - length of array.
*/
void printArray(int arr[], int n)
{
   for (int i = 0; i < n; i++)
       cout << arr[i] << " ";
   cout << "\n" << endl;
}
 
/*
Function to print a 2-Dimension array.
@param:
arr - 2D array.
row - number of rows.
column - number of column.
*/
void print2dArray(int **arr, int row, int column)
{
   for (int p = 0; p < row; p++)
   {
       for (int q = 0; q < column; q++)
       {
           cout << arr[p][q] << " ";
       }
       cout <<  "\n" << endl;
   }
}
 
/*
Function to create 1st row of the 2D array.
@param:
arr - input array.
C - pointer to 2D array.
length - number of column.
*/
void createInitialRow(int arr[], int **C, int length )
{
   int presentSum = 0;
   for(int i = 0; i < length; i++)
   {
       C[0][i] = presentSum + arr[i];
       presentSum = C[0][i];
   }
}
 
/*
Utility function to find the summation of number.
@param:
arr - array.
lBound - lower bound index of the array.
hBound - higher bound index of the array.
@return:
sum - summation output.
*/
int findSummation(int *pArr, int lBound , int hBound)
{
   int sum = 0;
   for (int z = lBound; z <= hBound; z++)
   {
       sum += pArr[z];
   }
   return sum;
}
 
/*
Function to initialise all the required global resources.
@param:
pArr - input array.
M - Number of rows.
N - Number of columns.
@return:
ERROR_CODE_SUCESS if sucess, else ERROR_CODE_FAILURE.
*/
int initialise(int *pArr, int M, int N)
{
   //Memory Allocation , if not.
   if(!C)
   {
       C = new int*[M];
   }
 
   if(!Bmin)
   {
       Bmin = new int*[M];
   }
 
   if(!G)
   {
       G = new int [M];
   }
 
   if(!B)
   {
       B = new int [M];
   }
 
   if ((C != NULL) && (Bmin != NULL) && (G != NULL) && (B != NULL))
   {
       for (int l = 0; l < M; l++)
       {
           C[l] = new int [N];
           Bmin[l] = new int [N];
       }
      
       for (int j = 0; j < M; j++)
       {
           for (int i = 0; i < N; i++)
           {
               C[j][i] = 0;
               Bmin[j][i] = 0;
           }
       }
      
       G[M] = {0};
       B[M] = {0};
       
       createInitialRow(pArr, C, N);
 
       return ERROR_CODE_SUCESS;
   }
   else
   {
       cout << "NULL pointer. Memory unavailable !!!" << endl;
       return ERROR_CODE_FAILURE;
   }
}
 
/*
Function to Deinitialise all the required global resources.
@param:
M - Number of rows.
*/
void Deinitialise(int M)
{
   //2D array
   for (int l = 0; l < M; l++)
   {
       delete[] C[l];
       delete[] Bmin[l];
   }
   delete[] C;
   delete[] Bmin;
   delete[] G;
   delete[] B;
}
 
/*
Function to create summation array.
@param:
A - input array.
M - Number of rows.
*/
void createSummationArray(int *A, int M)
{
   int lBound = 0;
   for(int pos = 0; pos < M; pos++)
   {
       B[pos] = findSummation(A, lBound, (lBound + G[pos] - 1));
       lBound += G[pos];
   }
}
 
/*
Function for minimum and maximum grouping and returns optimal group array.
@param:
A - input array.
N - Number of columns.
M - Number of rows.
@return:
G - optimal group array.
*/
int* Max_Min_grouping(int *A, int N, int M)
{
   int sum = 0;
   int min = 0;
   int col = N-1;
   int i,j;
   int gSum = 0;
 
   for (j = M-1; j >=0; j--)
   {
       for (i = N-1; i >= j; i--)
       {
           if (j > 0)
           {
               for (int k = j-1; k < i; k++)
               {
                   G = Max_Min_grouping(A, N-G[M], M-1);
                   sum = findSummation(A, (k+1), i);
                   min = C[j-1][k] < sum ? C[j-1][k] : sum;
                   if (min > C[j][i])
                   {
                       C[j][i] = min;
                       Bmin[j][i] = k;
                   }
               }
           }
       }
       if(j != 0)
       {
           G[j] =  col - Bmin[j][col];
           col = Bmin[j][col];
           gSum += G[j];
       }
       else
       {
           G[j] =  N - gSum;
       }
    }
 
   return G;
}
 
/* Main function */
int main(int argc, const char * argv[])
{
   //int A[] = {3, 9, 7, 8, 2, 6, 5, 10, 1, 7, 6, 4};
   //int N = sizeof(A)/sizeof(A[0]);
   int N = 0;
   int M = 0;
   int length = 0;
  
   cout << "\nEnter Length of the input array : " << endl;
   cin >> N;
   if(N <= 1)
   {
       cout << "Input array length not valid, should be atleast > 1. Quit !!!" << endl;
       return ERROR_CODE_INVALID_INPUT;
   }
  
   int *A = new int [N];
   if(A == NULL)
   {
       cout << "Input array - Null pointer . Quit !!!" << endl;
       return ERROR_CODE_INVALID_INPUT;
   }
  
   cout << "\nEnter the input array : " << endl;
   while(length < N)
   {
       cin >> A[length];
       length ++;
   }
  
   cout << "\nEnter Length of the group array and summation array : " << endl;
   cin >> M;
  
   if ((M >= N) || (M <= 1) )
   {
       cout << "Group array length not valid. Valid range : 1 < M < " << N << ". Quit !!!" << endl;
       return ERROR_CODE_INVALID_INPUT;
   }
  
   if (initialise(A, M, N))
   {
       cout << "Initialisation failed. Quit !!!" << endl;
       return ERROR_CODE_FAILURE;
   }
 
   if(! Max_Min_grouping(A, N, M))
   {
       cout << "Optimal group array not created, Max_Min_grouping failed. Quit !!!" << endl;
       return ERROR_CODE_FAILURE;
   }
 
   //Final C - Minimum element array of Bmin
   cout << "\nC Array : " << endl;
   print2dArray(C, M, N);
 
   //Final Bmin - Bmin Array :
   cout << "\nBmin Array : " << endl;
   print2dArray(Bmin, M, N);
 
   // Final G - Optimal Grouping Array
   cout << "\nOptimal Grouping Array : " << endl;
   printArray(G, M);
 
   // Final B - Group Summation Array
   createSummationArray(A, M);
   cout << "\nGroup Summation Array : " << endl;
   printArray(B, M);
 
   Deinitialise(M);
  
   return ERROR_CODE_SUCESS;
}
