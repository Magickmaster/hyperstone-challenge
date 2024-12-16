#include <stdio.h>

static unsigned int getMostSignificantBit(unsigned int mask)
{
    return ((sizeof(unsigned int) * 8) - 1) - __builtin_clz(mask);
}

static void printBitMask(unsigned int mask)
{
    // Mask all set bits in order of getMostSignificantBit
    while (mask)
    {
        int i = getMostSignificantBit(mask);
        printf("Index %d set\n", i);
        mask &= ~(1 << i);
    }
}

static void printBitMaskSlower(unsigned int mask)
{
    // Just iterate over all bits and check if they are set.
    for (int i = 0; mask; i++, mask >>= 1)
    {
        if (mask & 1)
            printf("Index %d set\n", i);
    }
}

// > You had a typo here: int was capitalized
int main(int argc, char **argv)
{
    unsigned int bitMaske = (1 << 23) | (1 << 10) | (1 << 13);
    // insert code here.
    printf("Print bit mask little endian style\n");
    printBitMask(bitMaske);

    printf("\nPrint bit mask big endian style (and slower, trivial solution)\n");
    printBitMaskSlower(bitMaske);
}