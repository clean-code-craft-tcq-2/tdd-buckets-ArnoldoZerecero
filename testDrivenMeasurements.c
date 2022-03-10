#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUMBER_OF_RANGES_AND_READINGS 100

int quickSortComparator(const void* p1, const void* p2)
{
	 return (*(int*)p1 - *(int*)p2);
}

void printRangesAndReadings(int *buffer, int totalRanges)
{
    int idx = 0;
    while (totalRanges--)
    {
        printf("%i-%i, %i\n", buffer[idx], buffer[idx + 1], buffer[idx + 2]);
        idx = idx + 3;
    }
}

int getRangesAndReadings(int *samples, int sampleSize, int *rangesAndReadingsFound)
{
    int currentRangeMinValue = 0;
    int currentRangeMaxValue = 0;
    int idx = 0;
    int numReadingsFoundInRange = 0;
    int rangeFound = 0;
    int totalRanges = 0;

    qsort(samples, sampleSize, sizeof(int), quickSortComparator);
    for (idx = 0; idx < sampleSize; idx++)
    {
        if (samples[idx] == (samples[idx + 1] - 1))
        {
            if (rangeFound == 0)
            {
                currentRangeMinValue = samples[idx];
                rangeFound = 1;
                numReadingsFoundInRange++;
            }
            currentRangeMaxValue = samples[idx + 1];
            numReadingsFoundInRange++;
        }
        else if (samples[idx] == samples[idx + 1])
        {
            numReadingsFoundInRange++;
        }
        else
        {
            if (rangeFound == 1)
            {
                *rangesAndReadingsFound++ = currentRangeMinValue;
                *rangesAndReadingsFound++ = currentRangeMaxValue;
                *rangesAndReadingsFound++ = numReadingsFoundInRange;
                totalRanges++;
            }
            rangeFound = 0;
            numReadingsFoundInRange = 0;
        }
    }
    return totalRanges;
}

int main() 
{
    // Test 1: Smallest possible test 
    int chargingSamples[] = {4,5};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;
	//printf("%i",sizeof(chargingSamples)/sizeof(int));
    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    assert(rangesFound == 1);
    assert(rangesAndReadings[0] == 4);
    assert(rangesAndReadings[1] == 5);
    assert(rangesAndReadings[2] == 2);

    printRangesAndReadings(rangesAndReadings, rangesFound);

    // Test 2: Multiple continuous numbers 
    int chargingSamples2[] = {1,2,3,4,5,6,7,8,9,10};
    int rangesAndReadings2[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples2, sizeof(chargingSamples2)/sizeof(int), rangesAndReadings2);
    assert(rangesFound == 1);
    assert(rangesAndReadings2[0] == 1);
    assert(rangesAndReadings2[1] == 10);
    assert(rangesAndReadings2[2] == 10);

    printRangesAndReadings(rangesAndReadings2, rangesFound);

    // Test 3: Multiple uncontinuous numbers 
    int chargingSamples3[] = {3,7,1,10,2,4,9,6,5,8};
    int rangesAndReadings3[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples3, sizeof(chargingSamples3)/sizeof(int), rangesAndReadings3);
    assert(rangesFound == 1);
    assert(rangesAndReadings3[0] == 1);
    assert(rangesAndReadings3[1] == 10);
    assert(rangesAndReadings3[2] == 10);

    printRangesAndReadings(rangesAndReadings3, rangesFound);

    // Test 4: Multiple ranges
    int chargingSamples4[] = {1,22,3,4,11,23,14,2,13,12,21,24};
    int rangesAndReadings4[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples4, sizeof(chargingSamples4)/sizeof(int), rangesAndReadings4);
    assert(rangesFound == 3);
    assert(rangesAndReadings4[0] == 1);
    assert(rangesAndReadings4[1] == 4);
    assert(rangesAndReadings4[2] == 4);
    assert(rangesAndReadings4[3] == 11);
    assert(rangesAndReadings4[4] == 14);
    assert(rangesAndReadings4[5] == 4);
    assert(rangesAndReadings4[6] == 21);
    assert(rangesAndReadings4[7] == 24);
    assert(rangesAndReadings4[8] == 4);

    printRangesAndReadings(rangesAndReadings4, rangesFound);

    // Test 5: Repeated numbers
    int chargingSamples5[] = {1,2,3,3,3,4,5,20,20,20,20,8,9,9};
    int rangesAndReadings5[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples5, sizeof(chargingSamples5)/sizeof(int), rangesAndReadings5);
    assert(rangesFound == 2);
    assert(rangesAndReadings5[0] == 1);
    assert(rangesAndReadings5[1] == 5);
    assert(rangesAndReadings5[2] == 7);
    assert(rangesAndReadings5[3] == 8);
    assert(rangesAndReadings5[4] == 9);
    assert(rangesAndReadings5[5] == 3);

    printRangesAndReadings(rangesAndReadings5, rangesFound);

    // Test 6: No ranges
    int chargingSamples6[] = {3,3,3,3,3,3,3,3,3,3,5,5,5,5,5};
    int rangesAndReadings6[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples6, sizeof(chargingSamples6)/sizeof(int), rangesAndReadings6);
    assert(rangesFound == 0);

    printRangesAndReadings(rangesAndReadings6, rangesFound);
    return 0;
}