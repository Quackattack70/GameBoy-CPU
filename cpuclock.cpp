#include "cpuclock.h"

void sleep(timei t){
    clock_t end = t + clock();
    while (end > clock());
}