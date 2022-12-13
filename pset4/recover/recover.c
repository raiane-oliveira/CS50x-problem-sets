#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;
const int NAME_JPG = 8;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover [memory card]");
        return 1;
    }

    // Remember filenames
    char *card = argv[1];
    char *newJpg = malloc(NAME_JPG);

    // Open memory card
    FILE *inptr = fopen(card, "r");
    if (!inptr)
    {
        printf("Could not open %s\n", card);
        return 2;
    }

    // Variables to recover the JPEG
    int i = 0, j = 0;
    BYTE bytes[BLOCK_SIZE];
    FILE *outptr;

    // Reads memory card to the end
    while (fread(bytes, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // Creates the new JPEGS names
            while (i < 1 + j)
            {
                sprintf(newJpg, "%03i.jpg", i);
                i++;
            }
            j++;

            // First JPEG
            if (i == 1)
            {
                // Making new JPEG
                outptr = fopen(newJpg, "w");
                if (!outptr)
                {
                    printf("Could not create %s\n", newJpg);
                    fclose(inptr);
                    free(newJpg);
                    return 3;
                }
                fwrite(bytes, sizeof(BYTE), BLOCK_SIZE, outptr);
            }
            else
            {
                fclose(outptr);

                // Making the next JPEG
                outptr = fopen(newJpg, "w");
                if (!outptr)
                {
                    printf("Could not create %s\n", newJpg);
                    fclose(inptr);
                    free(newJpg);
                    return 4;
                }
                fwrite(bytes, sizeof(BYTE), BLOCK_SIZE, outptr);
            }
        }
        else
        {
            // Checks if already found a JPEG
            if (i >= 1)
            {
                fwrite(bytes, sizeof(BYTE), BLOCK_SIZE, outptr);
            }
        }
    }

    // Closes files and free memory
    fclose(inptr);
    fclose(outptr);
    free(newJpg);
    return 0;
}