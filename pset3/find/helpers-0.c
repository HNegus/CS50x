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

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // reject array with < 1 values
    if (n < 1)
    {
        return false;
    }
    
    // loop through array of values
    for (int i = 0; i < n; i++)
    {   
        // return true if value is found
        if (values[i] == value)
        {
            return true;
        }
    }
     
    // return false if value is not found
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int counter;
    //walk through array
    do
    {
        counter = 0;
        //check value with its partner
        for (int j = 0; j < n; j++)
        { 
            //swap if wrongly sorted
            if (values[j] > values[j + 1])
            {
                int temp = values[j + 1];
                values[j + 1] = values[j];
                values[j] = temp;
                counter++;
            }   
        }
    }
    while (counter != 0);   
    return;
} 
