#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in a block of data
const int BLOCK = 512;

int main(int argc, char *argv[])
{
    // Check for single command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open forensic image
    FILE *memory_card = fopen(argv[1], "r");

    // Check if file exists
    if (memory_card == NULL)
    {
        // Inform user that file doesn't exist
        printf("File not found.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK];

    // Initalize variables before entering loop
    FILE *img = NULL;
    char filename[8];
    int i = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK, memory_card) == BLOCK)
    {
        // Define JPEG
        bool is_jpeg = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
        
        // Check if first JPEG
        if ((is_jpeg) && img == NULL)
        {
            // Create new file name
            sprintf(filename, "%03i.jpg", i);

            // Open new file
            img = fopen(filename, "w");

            // Create JPEG from the data
            fwrite(buffer, 1, BLOCK, img);
        }
        // If not first JPEG, check if this block is JPEG
        else if ((is_jpeg) && img != NULL)
        {
            // Close file and open a new file
            fclose(img);
            i++;

            // Create new file name
            sprintf(filename, "%03i.jpg", i);

            // Open new file
            img = fopen(filename, "w");

            // Create JPEG from data
            fwrite(buffer, 1, BLOCK, img);
        }
        // If not first JPEG, check if this block is not JPEG
        // This means the block is part of the previously opened JPEG
        else if ((!is_jpeg) && img != NULL)
        {
            // Keep writing to same JPEG
            fwrite(buffer, 1, BLOCK, img);
        }
    }
    // Close last opened image
    if (fread(buffer, 1, BLOCK, memory_card) != BLOCK)
    {
        fclose(img);
    }
    // Close forensic image
    fclose(memory_card);
}
