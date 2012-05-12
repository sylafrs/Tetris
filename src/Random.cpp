#include "../include/Random.h"
#include <ctime>
#include <cstdlib>

Random::Random() {
    srand(time(NULL));
}

int Random::next(int min, int max) {
    return ((float)rand() * (max-min) / RAND_MAX) + min ;
}
