#include <stdio.h>
#include <stdlib.h>
#include "bmp.h" 


int main(int argc, char* argv[]) 
{
    if(argc != 3) {
        printf("Usage: ./wodunit clue.bmp output.bmp\n"); 
        return 1;
    }
    
    char* infile = argv[1];
    char* outfile = argv[2];
    
    FILE* input = fopen(infile, "r");
    if (input == NULL)
    {
         printf("Could not open %s!\n", infile);
         return 2;
    }   
    FILE* output = fopen(outfile, "w");
    if (output == NULL)
    {
         fclose(input);
         printf("Could not create %s!\n", outfile);
         return 3;
    }
    
    BITMAPFILEHEADER bf; 
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input);
  
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(bi), 1, input);
      
    if (bf.bfType != 0x4d42 || bi.biBitCount != 24 )
    {
        fclose(input);
        fclose(output);
        printf("Input filetype not supported\n");
        return 4; 
    }

    fwrite(&bf, sizeof(bf), 1, output);
    fwrite(&bi, sizeof(bi), 1, output);
    
    // TODO calculate padding needed by doing 4 - (width*3 % 4)
    int padding = (4 - ((bi.biWidth * 3) % 4)) % 4;
    
    // TODO loop through scanlines biHeight number of times
    for (int i = 0; i < abs(bi.biHeight); i++) 
    {    
        // TODO loop through bytes on scanline biWidth number of times
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(triple), 1, input);
            
            if (triple.rgbtRed > 0xec) 
            {
                triple.rgbtRed = 0xff;
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;

            } 
            else if (triple.rgbtRed < 0xec) 
            {
                triple.rgbtBlue = 0xc0;
                triple.rgbtGreen = 0xc0;
                triple.rgbtRed = 0xc0;
            }
            
            fwrite(&triple, sizeof(triple), 1, output);
            
            
            // TODO add padding
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, output);
            }
        }
    }
    fclose(input);
    fclose(output);
    printf("EOP reached\n");
    return 0;
}
