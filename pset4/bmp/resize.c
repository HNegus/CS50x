#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[]) 
{
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile.bmp outfile.bmp\n");
        return 1;
    }
 
    int factor = atoi(argv[1]);    
    char* infile = argv[2];
    char* outfile = argv[3];

    if (factor < 1 ||factor > 100) 
    {
        printf("factor must be in range 1..100\n");
        return 5;
    }
 
    FILE* input = fopen(infile, "r");
    if (input == NULL) 
    {
        printf("Error! Could not open input file.\n");
        return 2;
    }
    
    // read header info
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(bf), 1, input);   
    
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(bi), 1, input);
    
    if (bf.bfType != 0x4d42 || bi.biBitCount != 24 )
    {
        fclose(input);
        printf("Input filetype not supported\n");
        return 4; 
    }
    
    FILE* output = fopen(outfile, "w");
    if (output == NULL) 
    {
        fclose(input);  
        printf("Error! Problem creating output file.\n");
        return 3;
    }
   
    // calculate padding in input file
    int oldpadding = (4 - ((bi.biWidth * 3) % 4)) % 4;
    
    // store old Height and Width
    long oldWidth = bi.biWidth; 
    long oldHeight = bi.biHeight;
    
    // calculate new Height and Width 
    bi.biWidth *= factor;
    bi.biHeight *= factor;
  
    // calculate new padding
    long padding = (4 - ((bi.biWidth * sizeof(RGBTRIPLE) % 4))) % 4;
  
    // calculate new header information
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    
    // store new header information in output file
    fwrite(&bf, sizeof(bf), 1, output);
    fwrite(&bi, sizeof(bi), 1, output);
    
    //TODO can be simplified, see 2nd todo
    // initialize array to store scanlines
    RGBTRIPLE scanline[oldWidth];
    
    // loop through each line of pixels
    for (int i = 0; i < abs(oldHeight); i++) 
    {    
        // loop through each pixel
        for (int j = 0; j < oldWidth; j++)
        {
            // read and store pixel
            RGBTRIPLE triple;
            fread(&triple, sizeof(triple), 1, input);
            scanline[j] = triple;     
            
            // resize in the x-direction                
            for (int k = 0; k < factor; k++)
            {              
                fwrite(&triple, sizeof(triple), 1, output);
            }                              
        } 
        
        // skip over padding if present
        for (int j = 0; j < oldpadding; j++) 
        {
            fgetc(input);
        }
        
        // add padding to output if needed
        for (int j = 0; j < padding; j++)
        {
            fputc(0x00, output);
        }
        
        // duplicate first scanline               
        for (int l = 1; l < factor; l++)
        {   
            // do for each pixel         
            for (int j = 0; j < oldWidth; j++)
            {    
                // TODO resized scanline is stored, this kan be simplified
                // resize in x-direction
                for (int k = 0; k < factor; k++)
                {              
                    fwrite(&scanline[j], sizeof(scanline[j]), 1, output);
                }              
            }
            // add padding if needed
            for (int j = 0; j < padding; j++)
            {
                fputc(0x00, output);
            }
        }                     
    }   

    // close files and exit program     
    fclose(input);
    fclose(output);
    return 0;
}
