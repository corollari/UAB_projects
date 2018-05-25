#include <stdlib.h>
#include <stdio.h>

void initVec ( float V[], const int N, const int seed ) {
  int i;
  srand48 (seed);  // set initial seed for random number generation
  for (i=0; i<N; i++)
    V[i]=drand48();
}


int main (int argc, char **argv)
{
  int N= 50000;
  int i, j;
  float S, *R,*X, *V1, *V2;

  if (argc>1) {  N= atoi(argv[1]); }
  if (N%4 != 0) {
     printf("argumento: N (N must be multiple of 4)\n");
     return 1;
  }

  // allocate memory
  R  = (float *) malloc ( N*sizeof(float) );
  X  = (float *) malloc ( N*sizeof(float) );
  V1 = (float *) malloc ( N*sizeof(float) );
  V2 = (float *) malloc ( N*sizeof(float) );


  if (!R || !X || !V1 || !V2) {
     printf("Memory Allocation Error: there is not enough memory for all data\n");
     return 1;
  }
  
  printf("Map and reduce: N= %d elements\n", N);
 
  // Init input data
  initVec(  X, N, 0 );
  initVec( V1, N, 1 );
  initVec( V2, N, 2 );

  for (i=0; i<N; i++)
    R[i]= 0.0f;


  // REDUCE transformation: Generate 1D vector from 2D matrix
  for (i=0; i<N; i++)
    for (j=0; j<N; j++) 
      R[j] = R[j] + ( X[i] - V1[j] ) * ( X[i] - V2[j] );

  for (S=0.0, i=0; i<N; i++)
    S = S + R[i];

  printf("CheckSum = %f\n", S);

  free(R); free(X);  free(V1);  free(V2);
}
