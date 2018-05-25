#include <stdlib.h>
#include <stdio.h>

long int inline count ( long int V ) 
{  // count number of bits set in V
  int c=0;
  while (V) {
    if (V&1) c++;
    V = V >> 1;
  }
  return c;
}

long int inline countBits ( const long int V[], const int N ) 
{ // count number of bits set in all elements of vector V[]
  int i, cnt=0;
  for (i=0; i<N; i++)
    cnt += count (V[i]);
  return cnt;
}

void initVec ( long int V[], const int N, const int seed ) {
  int i;
  srand48 (seed);  // set initial seed for random number generation
  for (i=0; i<N; i++)
    V[i]=lrand48();
}

long int Vect[SZ];
long int volatile C;

void main () {
  int i;
  initVec (Vect, SZ, 0);
  C=0;
  for (i=0; i<REP; i++)
    C = countBits (Vect, SZ);
  printf("Result: %ld\n", C);
}
