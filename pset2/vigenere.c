/**
 * caesar.c
 *
 * probleemkind81
 *
 * Cyphers text using Vigenere cyper
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

// prototype
char cypher(char input, int k);

int main(int argc, string argv[])
{
    // return 1 if wrong cmdline argument is given
    if (argc != 2)
    {     
        printf("Wrong command\n"); 
        return 1;
    }
        
    // set keyphrase to be cmdline argument
    string keyphrase = argv[1];  
    int len_kp = strlen(keyphrase);
    
    // create array to store keys
    int keys[1000];        
    
    // loop through content of keyphrase
    for (int i = 0; i < len_kp; i++)
    {   
        // reject keyphrase if not exclusively letters
        if (!isalpha(keyphrase[i]))
        {
            printf("Wrong command. 2\n");
            return 1;
        }
        
        // capitalise letters of keyphrase
        keyphrase[i] = toupper(keyphrase[i]);
        
        // convert letters to keys and store (A = index 0; Z = index 25) 
        keys[i] = (int) keyphrase[i] - 65;               
    }        

    // prompt user for input    
    string input = GetString();
    string output = input;
    
    // apply cypher function to input
    for (int i = 0, j = 0; i < strlen(input); i++)
    {   
        output[i] = cypher(input[i], keys[(j % len_kp)]); 
        // only apply key if input is a letter
        if (isalpha(input[i]))
        {
            j++;
        }
    }
       
    // print cyphertext and return 0         
    printf("%s\n", output);
    return 0;                
}

// cypher function
char cypher(char input, int k)
{
    char output;
    // ignore spaces and non-letters
    if (isblank(input) || !isalpha(input))
    {
        output = input;
        return output;
    }
    // loop around for capital letters    
    else if (input + k > (int) 'Z' && isupper(input))
    {
        output = (int) 'A' - 1 + input + k - 'Z';
        return output;                
    }    
    // loop around for non-capitalised letters
    else if (input + k > (int) 'z' && islower(input))
    {      
        output = (int) 'a' - 1 + input + k - 'z';
        return output;                
    }               
    // all other cases (no loop, all letters)       
    else
    {
        output = input + k;
        return output;
    }    
}

