#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int sum = 0;
  for (int i = 1; i < argc; i++) {
    char *q = argv[i];
    if (atoi(q)) {
      sum += (atoi(argv[i]));
    } else {
      printf("%s", q);
      printf("\n");
    }
  }
  printf("%d", sum);
}
