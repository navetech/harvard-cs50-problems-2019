# Questions

## What's `stdint.h`?

It is a header file in the C standard library introduced in the C99 standard library to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These are exact-width integer types. 

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2 bytes, respectively

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

hexadecimal: 42 4D       ASCII: BM

## What's the difference between `bfSize` and `biSize`?

bfSize: the size, in bytes, of the bitmap file.
biSize: the number of bytes required by the structure BITMAPINFOHEADER.

## What does it mean if `biHeight` is negative?

biHeight: the height of the bitmap, in pixels.

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
If biHeight is negative, indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS. Top-down DIBs cannot be compressed.

If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount
The number of bits-per-pixel. The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in `copy.c`?

If the input file does not exist.
If the output file can not be written or created, in case the program does not have write permission for the file or for the directory.

## Why is the third argument to `fread` always `1` in our code?

Because is to be read one data element (one pixel) each time.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

The  fseek()  function  sets  the  file position indicator for a file.
The new position, measured in bytes, is obtained by adding offset bytes (the second argument) to the position specified by the third argument.

## What is `SEEK_CUR`?

SEEK_CUR indicates that the offset bytes (the second argument) is relative to the current position indicator.
