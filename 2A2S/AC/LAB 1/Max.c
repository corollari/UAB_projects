#include <float.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SZ
#define SZ 50000
#endif

#ifndef REP
#define REP 100000
#endif

float inline max ( const float v1, const float v2) 
  { if (v1 >= v2) return v1;  return v2; }

float inline maxVec ( const float V[], const int N ) {
  int i;
  float Vmax= FLT_MIN; // Minimum float value
  for (i=0; i<N; i++)
    Vmax = max (Vmax, V[i]);
  return Vmax;
}

void initVec ( float V[], const int N, const int seed ) {
  int i;
  srand48 (seed);  // set initial seed for random number generation
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
