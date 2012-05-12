#include "../include/Random.h"
#include <ctime>
#include <cstdlib>

Random::Random() : min(0), max(0) {
    srand(time(NULL));
}

int Random::next(int min, int max) {
    return ((float)rand() * (max-min) / RAND_MAX) + min ;
}

int Random::next(int max) {
    return this->next(0, max);
}

int Random::next() {
    return this->next(this->min, this->max);
}

void Random::setMin(int min) {
    this->min = min;
}

void Random::setMax(int max) {
    this->max = max;
}
