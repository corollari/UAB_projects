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
  int N= 200000;
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
  /*for (i=0; i<N; i++)
    for (j=0; j<N; j++) 
      R[j] = R[j] + ( X[i] - V1[j] ) * ( X[i] - V2[j] );
  */  
  float Rj0;
  float Rj1;
  float Rj2;
  float Rj3;
  float V1j0;
  float V2j0;
  float V1j1;
  float V2j1;
  float V1j2;
  float V2j2;
  float V1j3;
  float V2j3;
  for (j = 0; j<N; j+=4)
  {
    Rj0 = 0.0f;
    Rj1 = 0.0f;
    Rj2 = 0.0f;
    Rj3 = 0.0f;
    V1j0 = V1[j];
    V2j0 = V2[j];
    V1j1 = V1[j+1];
    V2j1 = V2[j+1];
    V1j2 = V1[j+2];
    V2j2 = V2[j+2];
    V1j3 = V1[j+3];
    V2j3 = V2[j+3];
    for (i = 0; i<N; i+=4)
    {
      Rj0 = Rj0 + ( X[i] - V1j0) * (X[i]-V2j0);
      Rj1 = Rj1 + ( X[i+1] - V1j1) * (X[i+1]-V2j1);
      Rj2 = Rj2 + ( X[i+2] - V1j2) * (X[i+2]-V2j2);
      Rj3 = Rj3 + ( X[i+3] - V1j3) * (X[i+3]-V2j3);
    }
    R[j] = Rj0;
    R[j+1] = Rj1;
    R[j+2] = Rj2;
    R[j+3] = Rj3;
  }
    
  for (S=0.0, i=0; i<N; i++)
    S = S + R[i];

  printf("CheckSum = %f\n", S);

  free(R); free(X);  free(V1);  free(V2);
}
