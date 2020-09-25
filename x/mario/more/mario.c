#include <cs50.h>
#include <stdio.h>

void print_layer(int layer, int height);
void print_chars(char character, int num_of_chars);

// print adjacent pyramids
int main(void)
{
    // Prompt user for an integer height
    // If height less than 1 or greater 8, prompt again
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);
    
    // Iterate from 1 to height
        // On iteration i; print layer i
    for (int i = 1; i <= height; i++)
    {
        print_layer(i, height);
    }
    

}

// print a layer of the adjacent pyramids
void print_layer(int layer, int height)
{
    // Print left spaces
    int num_of_spaces = height - layer;
    print_chars(' ', num_of_spaces);
     
    // Print left hashes
    print_chars('#', layer);
        
    // Print gap
    printf("  ");
        
    // Print right hashes
    print_chars('#', layer);
        
    // Print end of layer
    printf("\n");
}

// print repeatly a character
void print_chars(char character, int num_of_chars)
{
    for (int i = 0; i < num_of_chars; i++)
    {
        printf("%c", character);
    }
}
