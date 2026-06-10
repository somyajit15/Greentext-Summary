#include <stdio.h>
#include <stdlib.h>










int main(){
  int n;
  printf("Enter the size of the matrix in power of 2:  ");
  scanf("%d", &n);

  int A[n][n], B[n][n], C[n][n];


  printf("Enter the elements of matrix A");

  for(int i = 0; i<n;i++){
    for(int j=0;j<n;j++){
        scanf("%d ", &A[i][j]);
    }
  }
  

    printf("Enter the elements of matrix B");

  for(int i = 0; i<n;i++){
    for(int j=0;j<n;j++){
        scanf("%d ", &B[i][j]);
    }
  }

   


  printf("The Resultant matrix C is : \n ");

  for(int i = 0; i<n; i++){
    for(int j=0; j<n; j++)
        printf("%d ", C[i][j]);
    printf("\n");    

    
  }
}