#include <stdio.h>

#include <cs50.h>

int main(void)
{
    string name = get_string("Enter Name > ");
    //printf("hello, world\n");
    printf("hello, %s\n", name);
}
