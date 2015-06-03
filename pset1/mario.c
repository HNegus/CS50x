/**
 * mario.c
 *
 * probleemkind
 *
 * Fetches height from user and draws pyramid with that height
 * 
 * Writen for Problem Set 1 of the CS50x course
 * See https://www.edx.org/course/introduction-computer-science-harvardx-cs50x
 */
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int height = 0;
    
    // fetch height from 0 to 24 from user
    do
    {
        
        printf("Height: ");
        height = GetInt();
  
    }
    while (height < 0 || height > 23);
    
    // counter = 1 to avoid prting one hashtag at the top
    int spaces = height;
    int counter = 1;
    
    // execute loop 'height' times
    do
    {            
        // prints spaces, starts with height-1, ends with 0
        for(int i = spaces; i > 0; i--)
        {
            printf(" ");
        }     
        
        // prints hashtags, starts with 2, ends with height+1
        for (int i = 0; i < counter; i++)
        {
            printf("#");          
        }
 
        // jump to a new line after hastags        
        if (counter <= height)
        {
            printf("\n");
        }
        
        // -1 space and +1 hashtag for next line
        spaces--;
        counter++;    
    }
    while (counter <= height);
      
}
