#include <stdio.h>

void printArray(int *nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int removeElement(int *nums, int numsSize, int val)
{
    // i will track the position to place the next valid element
    int i = 0; 
    for (int j = 0; j < numsSize; j++)
    {
        if (nums[j] != val)
        {
            nums[i] = nums[j];
            i++;
        }
    }
    // i is now the length of the array without the target values
    return i; 
}

int _from_book(int *nums, int numsSize, int target)
{
    int left = -1, right = 0;
    for (; right < numsSize; right++)
    {
        if (nums[right] != target)
            nums[++left] = nums[right];
    }
    return left+1;
}
int main(int argc, char const *argv[])
{
    int nums[] = {0, 1, 2, 2, 3, 0, 4, 2};
    int numsSize = sizeof(nums) / sizeof(int);
    int target = 2;
    printf("%d\n", _from_book(nums, numsSize, target));
    printArray(nums, numsSize);
    return 0;
}