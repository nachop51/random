#include <stdio.h>
void xor_swap(int *a, int *b) {
  *a = *a ^ *b;
  *b = *b ^ *a;
  *a = *a ^ *b;
}

int main(void) {
  int a = 941;
  int b = 205;

  printf("[%p]: a (%i)\n[%p]: b (%i)\n", &a, a, &b, b);
  xor_swap(&a, &b);
  printf("---------------------------\n");
  printf("[%p]: a (%i)\n[%p]: b (%i)\n", &a, a, &b, b);
}
