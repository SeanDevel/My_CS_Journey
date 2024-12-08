#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestValidBracketSubstring(const char *s) {
  int maxLength = 0;
  int n = strlen(s);

  // Stack to store indices of unmatched brackets
  int *stack = (int *)malloc((n + 1) * sizeof(int));
  int top = -1;

  // Push a base index for valid substrings
  stack[++top] = -1;

  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      // Push the index of the '(' onto the stack
      stack[++top] = i;
    } else {  // s[i] == ')'
      // Pop the last unmatched '('
      if (top > 0) {
        top--;
        // Calculate the valid substring length
        int length = i - stack[top];
        if (length > maxLength) {
          maxLength = length;
        }
      } else {
        // Push the current index as a base for the next valid substring
        stack[top] = i;
      }
    }
  }

  free(stack);
  return maxLength;
}

int main() {
  const char *input = ")()(()))(";  // Example input
                  // 0 12 3456 7 8
  int result = longestValidBracketSubstring(input);
  printf("The length of the longest valid bracket substring is: %d\n", result);
  return 0;
}
