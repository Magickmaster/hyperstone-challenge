#include <stdio.h>

typedef enum
{
    verySpecial,           // 0 (int)
    verySignificant,       // 1
    moderatelySignificant, // 2
    slightlySignificant,   // 3
    slightlyUnspecial,     // 4
} SpecialValues;

// a)
static inline unsigned int fancyFunction(SpecialValues val)
{
    // 1) Shift a 1 to the bits of very/moderately/slightlySignificant
    // 2) Shift the bits to the right by the value of val
    // 3) If the lsb is set, val was any of the three values.
    // As the bitmap uses static values, the compiler can optimize this
    return (((1 << verySignificant) |
             (1 << moderatelySignificant) |
             (1 << slightlySignificant)) >>
            val) &
           1;
}

// b)
// As the enum values are purely integers, the 'or' doesn't properly distinguish between the values.
// Due to the specific nature of the values, for this instance of enum and selection it works.
// Also, the result is value>0 (true), but in fancyFunction it's 1 (true) which could lead to inconsistency.
static inline unsigned int anotherFancyFunction(SpecialValues val)
{
    return (val & (verySignificant | moderatelySignificant | slightlySignificant));
}

// c)
// Here the function still works due to structure, but with the >0 we have a more consistent result of 0 or 1.
// This isn't branchless anymore though.
static inline unsigned int anotherFixedFancyFunction(SpecialValues val)
{

    return (1 << val & (1 << verySignificant | 1 << moderatelySignificant | 1 << slightlySignificant)) > 0;
}

// d)
// This time we use independent enum elements.
static inline unsigned int myFancyFunction(SpecialValues val)
{
    return (((1 << verySpecial) |
             (1 << slightlyUnspecial) |
             (1 << slightlySignificant)) >>
            val) &
           1;
}

// e)
// With these values, we see that the behaviour deviates.
static inline unsigned int myBrokenFancyFunction(SpecialValues val)
{
    return (val & (verySpecial | slightlyUnspecial | slightlySignificant));
}

// f)
// Using shifts, we get a consistent result of 0 or (>1), which is enough for a conditional.
// We could also apply the fix from (c) for consistent 0 or 1.
static inline unsigned int myFixedFancyFunction(SpecialValues val)
{
    return (1 << val & (1 << verySpecial | 1 << slightlyUnspecial | 1 << slightlySignificant));
}

int main(int argc, char const *argv[])
{
    printf("x -> a b c \n");
    for (SpecialValues i = verySpecial; i <= slightlyUnspecial; i++)
    {
        printf("%d -> %d %d %d\n", i, fancyFunction(i), anotherFancyFunction(i), anotherFixedFancyFunction(i));
    }

    printf("\nx -> d e f\n");
    for (SpecialValues i = verySpecial; i <= slightlyUnspecial; i++)
    {
        printf("%d -> %d %d %d\n", i, myFancyFunction(i), myBrokenFancyFunction(i), myFixedFancyFunction(i));
    }
}
