/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // TODO check if there are no cmdline args
    if (argc != 1) 
    {
        printf("Usage: ./recover\n");
        return 1;
    }
    
    // TODO open target file
    FILE* file = fopen("card.raw", "r");
    if (file == NULL) 
    {
        printf("Cannot open target file.\n");
        return 2;
    }
    
    BYTE buffer[512];
    
    int imgcounter = 0;
    bool jpgstart = false;
    bool jpgend = false;
    char title[8];
    FILE* output;
    
    while(true)   
    {    
        fread(&buffer, 512, 1, file);

        
        if (feof(file))
        {          
            fwrite(&buffer, 512, 1, output);
            fclose(output);
            break;
        }
        
        // check if jpg       
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && 
        buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
        {
            if (jpgend && imgcounter != 0)
            {
                fclose(output);
            }
            
            // set name of new jpeg
            imgcounter++;
            sprintf(title, "%03d.jpg", imgcounter);
            
            
            // open file 
            output = fopen(title, "w");                      
            jpgstart = true;
            jpgend = false;           
        }
        
        // check if jpeg file is opened
        if (jpgstart || imgcounter > 0)
        {
            fwrite(&buffer, 512, 1, output);
        }
        
        // check if at end of jpeg
        if ((int)buffer[511] == 0x00 && jpgstart)
        {
            jpgend = true;
            jpgstart = false;           
        }          
    }
 
    fclose(file);
    return 0;     
}
