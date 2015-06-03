/**
 * initials.c
 *
 * probleemkind81
 *
 * Takes user input (your name) and prints capitalised initials
 *
 * Writen for Problem Set 2 of the CS50x course
 * See https://www.edx.org/course/introduction-computer-science-harvardx-cs50x 
 */
 
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
 
int main(void)
{
    // prompts user for name
    string name = GetString();
    
    // loops through input string
    for (int i = 0; i < strlen(name); i++)
    {   
        // checks if character is a space and next is a letter
        if (name[i] == ' ' && name[i + 1] != ' ')
        {
            // capitalise letter and print
            name[i + 1] = toupper(name[i + 1]); 
            printf("%c", name[i + 1]);
        }
        // checks if letter is first
        else if (i == 0)
        {
            // capitalise letter and print
            name[i] = toupper(name[i]);
            printf("%c", name[i]);
        }              
    }
    
    // moves to new line
    printf("\n");
}
