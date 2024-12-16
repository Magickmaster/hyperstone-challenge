#include <stdio.h>
#include <stdlib.h> // rand
#include <time.h>   // timeseed

unsigned int getRandomBoundedInteger(unsigned int maximum)
{
    return rand() % maximum; // dummy implementation
}

// I don't see much optimisation potential here.
unsigned int getVal()
{
    int random = rand() % 100; // Precise percentages
    if (random < 32)
        return 42;
    if (random < 54) // sum up
        return 13;
    if (random < 65) // further sum
        return 37;
    return getRandomBoundedInteger(10);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL)); // Initialize random seed
    printf("Random: %d\n", getVal());
    return 0;
}
