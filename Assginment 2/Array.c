// Array.c
// part of ENCM 501 Winter 2026 Assignment 2

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct timespec TIMESPEC;

// This choice of clock seems to give the highest resolution on macOS.
#define WHICH_CLOCK CLOCK_MONOTONIC_RAW

// Number of elements in an array will be this number.
#define N_OF_ELEMENTS ((unsigned long) 2e6) // 2 million

void fill_array(unsigned *a, unsigned long n)
{
  unsigned long i;

  // Array element values: 0, 1, ..., n - 1.
  for (i = 0; i < n; i++)
    a[i] = i;
}

unsigned long sum(const unsigned *a, unsigned long n)
{
  unsigned long i;
  unsigned long sum;

  // Add up all the array elements.
  sum = 0;
  for (i = 0; i < n; i++)
    sum += a[i];
  
  return sum;
}

double timespec2ns(const TIMESPEC *ts)
{
  return 1.0e9 * ts->tv_sec + ts->tv_nsec;
}

int main(void)
{
  TIMESPEC start, finish;
  unsigned *p;
  unsigned long the_sum;
  double summing_time;
  
  printf("Running code in Array.c with N_OF_ELEMENTS = %lu\n",
         N_OF_ELEMENTS);

  // Allocate and fill the array.
  p = malloc( N_OF_ELEMENTS * sizeof(unsigned) );
  fill_array(p, N_OF_ELEMENTS);  

  // Note the start time.
  clock_gettime(WHICH_CLOCK, &start);

  the_sum = sum(p, N_OF_ELEMENTS);

  // Note the finish time.
  clock_gettime(WHICH_CLOCK, &finish);

  summing_time = timespec2ns(&finish) - timespec2ns(&start);
  printf("Measured time spent in sum : %.2f ns.\n", 
         summing_time);

  printf("Checking that sum is correct ...\n");
  printf("Expected %lu, got %lu.\n", 
         N_OF_ELEMENTS * (N_OF_ELEMENTS - 1) / 2, the_sum);

  free(p);
  return 0;
}
