/**
 * caesar.c
 *
 * probleemkind81
 *
 * Cyphers text using Caesar's cyper
 * Input key with cmdline argument
 * Works for ASCII text
 *
 * Writen for Problem Set 2 of the CS50x course
 * See https://www.edx.org/course/introduction-computer-science-harvardx-cs50x 
 */
 
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // return 1 if wrong cmdline argument is given
    if (argc != 2)
    {     
        printf("Wrong command. 1\n"); 
        return 1;
    }
    
    // return 0 if program runs correcy
    else
    {
        // cast input key to int
        int k = atoi(argv[1]);
        
        // make key number between 0 - 26
        k = k % 26;
        
        // get input from user
        string input = GetString();
        
        // loops through and cypher characters in input
        for (int j = 0, n = strlen(input); j < n; j++)
        {   
            // ignore spaces
            if (isblank(input[j]))
            {
            }
            // ignore non-leters
            else if (!isalpha(input[j]))
            {                
            }
            // loop around for capital letters
            else if ((input[j] + k > (int) 'Z') && isupper(input[j]))
            {
                input[j] = (int) 'A' - 1 + input[j] + k - 'Z';                
            }
            // loop around for non-capitalised letters
            else if (input[j] + k > (int) 'z' && islower(input[j]))
            {
                input[j] = (int) 'a' - 1 + input[j] + k - 'z';                
            }   
            // all other cases (no loop, all letters)       
            else
            {
                input[j] = input[j] + k;
            }
        } 
        
        // print end result and return 0
        printf("%s\n", input);          
        return 0;
    }     
}
