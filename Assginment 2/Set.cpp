// Set.cpp
// part of ENCM 501 Winter 2026 Assignment 2

#include <set>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct timespec TIMESPEC;

// This choice of clock seems to give the highest resolution on macOS.
#define WHICH_CLOCK CLOCK_MONOTONIC_RAW

// Number of elements in an array will be this number.
#define N_OF_ELEMENTS ((unsigned long) 2e6) // 2 million

// Insert a[0] ... a[n-1] into the_set.
void array2set(std::set<unsigned>& the_set,
	       const unsigned *a,
	       unsigned long n)
{
  for (unsigned long i = 0; i < n; i++)
    the_set.insert(a[i]);
}

// Compute the sum of all the items in the_set.
unsigned long set_sum(const std::set<unsigned>& the_set)
{
  unsigned long sum = 0;
  std::set<unsigned>::iterator it = the_set.begin();
  while (it != the_set.end()) {
    sum += *it;
    it++;
  }
  return sum;
}

double timespec2ns(const TIMESPEC *ts)
{
  return 1.0e9 * ts->tv_sec + ts->tv_nsec;
}

int main(void)
{
  TIMESPEC seed, start, finish;
  unsigned *p;
  unsigned long sum;
  double summing_time;

  printf("Running code in Set.cpp with N_OF_ELEMENTS = %lu\n",
         N_OF_ELEMENTS);

  // Make an array and puts some values into it.
  p = new unsigned[N_OF_ELEMENTS];
  for (unsigned long i = 0; i < N_OF_ELEMENTS; i++)
    p[i] = i;

  // Use REALTIME clock to nearest ms to seed pseudorandom number generator.
  clock_gettime(CLOCK_REALTIME, &seed);
  srandom(seed.tv_sec * 1000 + seed.tv_nsec / 1000000);

  // Shuffle the array.
  std::shuffle(p, p + N_OF_ELEMENTS, std::default_random_engine());

  // Create an empty set.
  std::set<unsigned> the_set;

  // Insert all the array elements into the set.
  array2set(the_set, p, N_OF_ELEMENTS);
  
  // Note the start time.
  clock_gettime(WHICH_CLOCK, &start);

  sum = set_sum(the_set);

    // Note the finish time.
  clock_gettime(WHICH_CLOCK, &finish);

  summing_time = timespec2ns(&finish) - timespec2ns(&start);
  printf("Measured time spent in sum : %.2f ns.\n", 
         summing_time);

  printf("Checking that sum is correct ...\n");
  printf("Expected %lu, got %lu.\n", 
         N_OF_ELEMENTS * (N_OF_ELEMENTS - 1) / 2, sum);

  delete [] p;
  return 0;
}
