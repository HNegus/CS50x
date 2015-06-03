/**
 * greedy.c
 *
 * probleemkind81
 *
 * Calculates minimum number of coins needed to give back change
 *
 * Writen for Problem Set 1 of the CS50x course
 * See https://www.edx.org/course/introduction-computer-science-harvardx-cs50x 
 */
 
#include "cs50.h"
#include "cs50.c"
#include <math.h>
#include <stdio.h>

int main(void)
{

    // stores input
    float input;

    // ask user for non negative amount of money
    do
    {
        printf("How much is owed?\n");
        input = GetFloat();
    }
    while (input < 0); 
    
    // multiply by 100 to get cents
    // round to prevent errors
    // counter counts number of coins used 
    input = 100 * input;
    int owed = round(input);
    int counter = 0;
   
    
    // loop while amount owed > 0
    while(owed > 0)
    {   
        // check if you can give back a certain amount of cents 
        // increase counter if yes, rinse, repeat     
        if (owed >= 25)
        {            
            owed = owed - 25;
            counter++;        
        }else if (owed >= 10)
        {        
            owed = owed - 10;
            counter++;         
        }else if (owed >= 5)
        {       
            owed = owed - 5;
            counter++;            
        }else if (owed >= 1)
        {       
            owed = owed - 1;
            counter++;      
        }       
    }   
    
    // print out minimum number of coins needed 
    printf("%d\n", counter);
}
