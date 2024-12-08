#include <stdio.h>

int removeDuplicates(int* nums, int numsSize) {
  if (numsSize == 0) return 0;  // Handle empty array

  int i = 0;  // Index for the unique elements
  for (int j = 1; j < numsSize; j++) {
    if (nums[j] != nums[i]) {  // If a new unique element is found
      i++;                     // Move to the next position for unique elements
      nums[i] = nums[j];       // Update the array in place
    }
  }
  return i + 1;  // Length of the array with unique elements
}

int main() {
  int nums[] = {1, 1, 2, 3, 3, 4};  // Example sorted array
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  int length = removeDuplicates(nums, numsSize);

  printf("New length of the array: %d\n", length);
  printf("Modified array elements: ");
  for (int i = 0; i < length; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  return 0;
}
