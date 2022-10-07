#include "mergesort.h"
#include <stdlib.h>

int needsSorting(int rangeSize);
void mergeSortRange(int* input, int startIndex, int endIndex);
void mergeRanges(int* input, int startIndex, int midIndex, int endIndex);

void mergesort(int size, int values[]) {
  mergeSortRange(values, 0, size);
  return;
}

void mergeSortRange(int* input, int startIndex, int endIndex) {
  //does the sort range on startIndex (inclusive) to endIndex (exclusive).
  if (!needsSorting(endIndex - startIndex)) {
    return;
  }
  int midIndex = (endIndex + startIndex) / 2;
  mergeSortRange(input, startIndex, midIndex);
  mergeSortRange(input, midIndex, endIndex);
  mergeRanges(input, startIndex, midIndex, endIndex);
  return;
}

void mergeRanges(int* input, int startIndex, int midIndex, int endIndex) {
  //merges from startIndex (inclusive) to endIndex (exclusive).
  int rangeSize = endIndex - startIndex;
  int* sorted = (int*) malloc(rangeSize * sizeof(int));
  int firstIndex = startIndex;
  int secondIndex = midIndex;
  int copyIndex = 0;

  while (copyIndex < rangeSize) {
    if (firstIndex < midIndex && (secondIndex >= endIndex || input[firstIndex] < input[secondIndex])) {
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
