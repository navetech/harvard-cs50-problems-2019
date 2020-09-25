// Resize a BMP image

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // get resize factor
    char *endptr;
    float f = strtof(argv[1], &endptr);
    if ((*endptr != '\0') || !(f > 0) || (f > 100))
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
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding for scanlines in the input file
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update output bitmap width an height
    int width_in = bi.biWidth;
    int height_in = bi.biHeight;
    bi.biWidth *= f;
    bi.biHeight *= f;

    if ((bi.biWidth == 0) || (bi.biHeight == 0))
    {
        fclose(inptr);
        fprintf(stderr, "Width/height of resized image became 0.\n");
        return 6;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

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
    float r = 0;
    for (int i = 0, biHeight = abs(height_in); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        float c = 0;
        for (int j = 0; j < width_in; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // put RGB triple in the output row
            int ic = c;
            c += f;
            for (int k = 0, nc = c - ic; k < nc; k++)
            {
                row_out[ic + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);

        // write row to outfile
        int ir = r;
        r += f;
        for (int k = 0, nr = r - ir; k < nr; k++)
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
