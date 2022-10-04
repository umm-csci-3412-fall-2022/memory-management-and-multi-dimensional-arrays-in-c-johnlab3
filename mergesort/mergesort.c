#include "mergesort.h"
#include <cstdlib>

int needsSorting(int rangeSize);
void mergeSortRange(int* input, int startIndex, int endIndex);
void mergeRanges(int* input, int startIndex, int midIndex, int endIndex);

void mergesort(int size, int values[]) {
  // This obviously doesn't actually do any *sorting*, so there's
  // certainly work still to be done.
  //
  // Remember that a key goal here is to learn to use
  // `malloc/calloc` and `free`, so make sure you explicitly
  // allocate any new arrays that you need, even if you
  // might not strictly need to.
  mergeSortRange(values, 0, size - 1);
  return;
}

void mergeSortRange(int* input, int startIndex, int endIndex) {
  if (!needsSorting(endIndex - startIndex + 1)) {
    return;
  }
  int midIndex = (endIndex + startIndex) / 2;
  mergeSortRange(input, startIndex, midIndex);
  mergeSortRange(input, midIndex, endIndex);
  mergeRanges(input, startIndex, midIndex, endIndex);
  return;
}

void mergeRanges(int* input, int startIndex, int midIndex, int endIndex) {
  int rangeSize = endIndex - startIndex + 1;
  int* sorted = (int*) malloc(rangeSize * sizeof(int));
  int firstIndex = startIndex;
  int secondIndex = midIndex;
  int copyIndex = 0;

  while (copyIndex < rangeSize) {
    if (firstIndex < midIndex && (secondIndex > endIndex || input[firstIndex] < input[secondIndex])) {
      sorted[copyIndex] = input[firstIndex];
      ++firstIndex;
    }
    else {
     sorted[copyIndex] = input[secondIndex];
     ++secondIndex;
    }
    ++copyIndex;
  }
  for (int i = 0; i < rangeSize; i++) {
    input[startIndex + i] = sorted[i];
  }
  free(sorted);
  return;
}

int needsSorting(int rangeSize) {
  return rangeSize >= 2;
}
