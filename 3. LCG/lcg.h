#include <stdio.h>
 
int m = 8191;
int a =  7;
int c =  7;
int rseed = 7;
 
static inline int myrand() {
    return rseed = (a * rseed + c) % m;
}

static inline void set_seed(int seed) {
    rseed = seed;
}
