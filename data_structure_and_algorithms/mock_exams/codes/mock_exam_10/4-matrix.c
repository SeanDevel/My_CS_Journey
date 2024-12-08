#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool areElementsUnique(int** matrix, int rows, int cols) {
  int range = 10000;  // Example for bounded integer elements (-range to +range)
  bool seen[2 * 10000 + 1] = {false};  // Array to track seen elements

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int value = matrix[i][j] + range;  // Shift to handle negatives
      if (seen[value]) {
        return false;  // Duplicate found
      }
      seen[value] = true;
    }
  }
  return true;  // All elements are unique
}



// Comparison function for sorting
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool areElementsUniqueInPlace(int* matrix, int size) {
    qsort(matrix, size, sizeof(int), compare);
    for (int i = 1; i < size; i++) {
        if (matrix[i] == matrix[i - 1]) {
            return false; // Duplicate found
        }
    }
    return true; // All elements are unique
}

int main() {
  int rows = 3, cols = 3;
  int mat[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
  // Convert 2D array to pointer array
  int* matrix[3] = {mat[0], mat[1], mat[2]};

  if (areElementsUnique(matrix, rows, cols)) {
    printf("All elements are unique.\n");
  } else {
    printf("There are duplicate elements.\n");
  }

  return 0;
}
