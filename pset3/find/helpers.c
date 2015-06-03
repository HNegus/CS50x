/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/*
int main (void)
{
    int array[] = generate(5, 8);
    for (int i = 0; i < 5; i++)
        printf("%d", array[i]);
    
    
}
*/
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // these will be the upper and lower limits for your search
    int upper = n;
    int lower = 0;
    int middle;
    
    // execute while middle != 0, n    
    for ( ; ; )
    {
        middle = (lower + upper) / 2;
           
        // return true if value is found
        if (value == values[middle])
        {
            return true;
        }
        // else if value is smaller, discard right side 
        else if (value < values[middle])
        {
            upper = middle - 1;
        }
        // else discard left side
        else if (value > values[middle])
        {
            lower = middle + 1;
        }
        else if (middle == 0 || middle == n)
        {
            return false;
        }        
    }
      
    // return false if value is not found
    return false;
}

/**
 * Sorts array of n values
 */
void sort(int values[], int n)
{

    bool swaps;
    //walk through array
    
    do
    {
        swaps = false;
        //check value with its partner
        for (int j = 0; j < n; j++)
        { 
            //swap if wrongly sorted
            if (values[j] > values[j + 1])
            {
                int temp = values[j + 1];
                values[j + 1] = values[j];
                values[j] = temp;
                swaps = true;
            }   
        }
    }
    while (swaps);   
    return;
} 
