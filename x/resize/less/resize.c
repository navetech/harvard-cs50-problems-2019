// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // get resize factor
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    if ((*endptr != '\0') || (n < 1) || (n > 100))
    {
        fprintf(stderr, "Invalid resize factor: %s.\n", argv[1]);
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding for scanlines in the input file
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update output bitmap width an height
    int width_in = bi.biWidth;
    int height_in = bi.biHeight;
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines in the outfile
    int padding_out = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update outfile's headers
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding_out) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    RGBTRIPLE *row_out = malloc(bi.biWidth * sizeof(RGBTRIPLE));
    for (int i = 0, biHeight = abs(height_in); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < width_in; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // put RGB triple in the output row
            for (int k = 0; k < n; k++)
            {
                row_out[n * j + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);

        // write row to outfile
        for (int k = 0; k < n; k++)
        {
            fwrite(row_out, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            for (int l = 0; l < padding_out; l++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // free output row
    free(row_out);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
