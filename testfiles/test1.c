#include <stdio.h>
#include <stdlib.h>

struct cards{
  int suit;
};

struct dice{
  int roll;
  struct cards* deck;
};

int main() {
  struct dice* cur = (struct dice*)malloc(sizeof(struct dice));
  cur->deck = (struct cards*)malloc(sizeof(struct cards) * 5);
  int ponitsize = sizeof(cur->deck);
  int arrsize = sizeof(*cur->deck);
  int size = sizeof(*cur->deck) / sizeof(struct cards);
  printf("%d, %d, %d", ponitsize, arrsize, size);
}