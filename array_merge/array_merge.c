#include "array_merge.h"
#include "../mergesort/mergesort.h"
#include <stdlib.h>

int* array_merge_old(int num_arrays, int* sizes, int** values) {
  //Figure out the total number of elements for the new array
  //This starts at 1 to account for the first element, being the array size
  //Note
  int total_size = 1;
  for (int i = 0; i < num_arrays; ++i){
    total_size += sizes[i];
  }
  int *output = (int*) malloc(total_size + 1 * sizeof(int));
  output[0] = total_size - 1; //The total number of actual elements in the array, not counting size

  //Sort all of the subarrays
  for(int i = 0; i < num_arrays; ++i){
    mergesort(sizes[i], values[i]);
  }

  //Merge the now-sorted arrays, eliminating duplicates
  //Store the position of travel within the newly-sorted arrays and where we're writing to
  int* positions = (int*) calloc(num_arrays, sizeof(int));
  int write_position = 1;

  while(true){
    //the array with the current smallest value; set to -1
    //to detect if no changes are made.
    int smallest_position = -1;

    for(int i = 0; i < num_arrays; i++){
      if(positions[i] < sizes[i]){
        int current_value = values[i][positions[i]];
        if(smallest_position == -1 || output[write_position] > current_value){
          smallest_position = i;
          output[write_position] = current_value;
        } else if (output[write_position] == current_value){
          ++positions[i]; //this is a duplicate, we don't want to work with this
        }
      }
    }

    if(smallest_position == -1) {break;}
    ++positions[smallest_position];
    ++write_position;
  }

  output = (int*) realloc(output, (write_position - 1) * sizeof(int));
  free(positions);
  return output;
}

int* array_merge(int num_arrays, int* sizes, int** values) {
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
  mergesort(merged_array, total_size);
  int unique_count = !!total_size;

  for (int i = 1; i < total_size; i++) {
    unique_count += (merged_array[i] != merged_array[i - 1]);
  }

}
