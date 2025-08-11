// Recovers files from corrupt file storage

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Improper usage.\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");

    if (raw == NULL)
    {
        printf("Error while opening file.\n");
        return 1;
    }

    typedef uint8_t byte;
    int file_num = -1;
    char filename[25];

    byte storage[512];
    FILE *img;

    while (fread(storage, sizeof(byte), 512, raw) == 512)  // fread() returns number of items of size size read (can detect EOF if less than 512)
    {
        // New image found
        if (storage[0] == 0xff && storage[1] == 0xd8 && storage[2] == 0xff && (storage[3] & 0xf0) == 0xe0)  // (buffer[3] & 0xf0) == 0xe0
        {
            // Check if it's the first image
            if (file_num != -1)
            {
                fclose(img);
            }
            file_num++;
            sprintf(filename, "%03d.jpg", file_num);

            img = fopen(filename, "w");
            fwrite(storage, sizeof(byte), 512, img);
        }
        // Continue writing to file
        else if (file_num != -1)
        {
            fwrite(storage, sizeof(byte), 512, img);
        }
    }
    fclose(img);
    fclose(raw);
}