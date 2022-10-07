#include "array_merge.h"
#include "../mergesort/mergesort.h"
#include <stdlib.h>
#include <stdio.h>

int* array_merge(int num_arrays, int* sizes, int** values) {
  if (num_arrays == 0) {
    int* output = (int*) malloc(sizeof(int));
    output[0] = 0;
    return output;
  }
  //Find the total length of all of the arrays
  int total_size = 0;

  for (int i = 0; i < num_arrays; i++) {
    total_size += sizes[i];
  }

  int* merged_array = (int*) malloc(total_size * sizeof(int));
  int insert_position = 0;
  for (int i = 0; i < num_arrays; i++) {
   for (int j = 0; j < sizes[i]; j++) {
     merged_array[insert_position] = values[i][j];
     insert_position++;
   }
  }
  mergesort(total_size, merged_array);
  int unique_count = 1;

  for (int i = 1; i < total_size; i++) {
    unique_count += (merged_array[i] != merged_array[i - 1]);
  }

  int* output = (int*) malloc((unique_count + 1) * sizeof(int));
  //reuse the insert position from above.
  insert_position = 1;
  for (int i = 0; i < total_size; i++) {
   if (i == 0 || merged_array[i] != merged_array[i - 1]) {
     output[insert_position] = merged_array[i];
     ++insert_position;
   }
  }
  output[0] = unique_count;
  free(merged_array);
  return output;
}
