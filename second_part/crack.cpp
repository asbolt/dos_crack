#include "TXLib.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void makeCrackFile ();

int main()
{
    txCreateWindow (800, 500);
    txSetFillColor (TX_BLACK);
    txDrawText (0, 0, txGetExtentX(), txGetExtentY(), "Press anywhere to crack!");
    txSleep();

    while (! txMouseButtons()) {};
    txClear ();
    txDrawText (0, 0, txGetExtentX(), txGetExtentY(), "Hi-hi ha-ha");
    txSleep();

    makeCrackFile();

    txPlayVideo ("chipi-chipi-chapa-chapa.mp4", 1.5);
    return 0;
}

void makeCrackFile ()
{
    FILE *com_file = fopen ("program.com", "rb");
    if (com_file == NULL)
        return;

    fseek (com_file, 0, SEEK_END);
    int file_size = ftell (com_file);
    fseek (com_file, 0, SEEK_SET);

    char *buffer = (char *)calloc (file_size, sizeof(char));
    if (buffer == NULL)
        return;
        
    fread (buffer, sizeof(char), file_size, com_file);

    fclose (com_file);

    FILE *crack_file = fopen ("hacked_program.com", "ab");
    fseek (crack_file, 0, SEEK_SET);
    int i = 0;

    while (i != file_size)
    {
        if (*(buffer + i) != 't')
        {
            fprintf (crack_file, "%c", *(buffer + i));
            i++;
        } else {
            fprintf (crack_file, "u");
            i++;
        }
    }

    fclose (crack_file);
    free (buffer);

    return;
}



