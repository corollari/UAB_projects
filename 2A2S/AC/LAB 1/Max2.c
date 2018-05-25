#include <float.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SZ
#define SZ 50000
#endif

#ifndef REP
#define REP 100000
#endif

float inline max ( float v1, float v2) {
  return (v1 >= v2)? v1: v2;
}

float inline maxVec ( float V[], int N ) {
  int i;
  float Vmax1[4], Vmax2[4];
  Vmax1[0:4] = Vmax2[0:4] = FLT_MIN; 
  for (i=0; i<N; i+=8)  // assume N is always multiple of 8 
  {
    Vmax1[:] = Vmax1[0:4] > V[i:4]  ? Vmax1[:]: V[i:4];
    Vmax2[:] = Vmax2[0:4] > V[i+4:4]? Vmax2[:]: V[i+4:4];
  }
  return __sec_reduce_max( max(Vmax1[:], Vmax2[:]));
}

void initVec ( float V[], int N, int seed ) {
  int i;
  srand48(seed);  // set initial seed for random number generation
  for (i=0; i<N; i++)
    V[i]=drand48();
}

float Vect[SZ];
float volatile F;

void main () {
  int i;
  initVec (Vect, SZ, 0);
  F=0.0;
  for (i=0; i<REP; i++)
    F = maxVec (Vect, SZ);
  printf("Result: %f\n", F);
}
