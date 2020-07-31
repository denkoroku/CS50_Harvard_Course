#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./recover fileName\n");
        return 1;
    }

    char *card = argv[1];

    //open memory card
    FILE *data = fopen(card, "r");

    //if card cant be read
    if (data == NULL)
    {
        printf("Card cannot be read");
        return 1;
    }

    unsigned char buffer[512];
    char img[8];
    int fileCounter = 0;
    FILE *jpeg;

    fread(buffer, 512, 1, data);

    // while not at the end of the card

    while (fread(buffer, 512, 1, data) == 1)
    {

        //if it is a jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        // if first jpeg just write it to new file
        {
            if (fileCounter == 0)
            {
                //open a new file
                sprintf(img, "%03i.jpg", fileCounter);

                //increase the file counter
                fileCounter++;

                //write the buffer to the file
                jpeg = fopen(img, "w");
                fwrite(buffer, 512, 1, jpeg);
                fclose(jpeg);
            }

            //if not first one then close file and write it to new one
            else if (fileCounter > 0)
            {
                //Then start a new file
                sprintf(img, "%03i.jpg", fileCounter);

                //increase file counter
                fileCounter++;

                //write to the new file
                jpeg = fopen(img, "w");
                fwrite(buffer, 512, 1, jpeg);
                fclose(jpeg);
            }
        }
        //else if not jpeg header just keep wrtiting to the file
        else
        {
            if (jpeg != NULL)
            {
                jpeg = fopen(img, "a");
                fwrite(buffer, 512, 1, jpeg);
                fclose(jpeg);
            }
        }
    }

    //close any remaining files
    fclose(data);

    return 0;
}
