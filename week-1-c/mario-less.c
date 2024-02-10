#include <cs50.h>
#include <stdio.h>

// prototypes
int get_height(void);
void print_row(int spaces, int bricks);

int main(void)
{
    int height = get_height();          // call function that prompts user to enter pyramid height
    for (int i = 0; i < height; i++)    // print pyramid of height that user entered
    {
        int b = i + 1;                  // define integer "b"
        print_row(height - b, b);       // call function that prints bricks in pyramid
    }
}

// prompt user to enter a pyramid height
int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);
    return height;
}

// print row of bricks in pyramid
void print_row(int spaces, int bricks)
{
    for (int j = 0; j < spaces; j++)
    {
        printf(" ");
    }
    for (int k = 0; k < bricks; k++)
    {
        printf("#");
    }
    printf("\n");
}
