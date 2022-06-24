#include <stdlib.h>
#include <utilities.h>

// inclusive
int rand_range(int s, int e) { return s + rand() % (e - s + 1); }
