#include "../h_files/crack.h"

void makeCrackFile ()
{
    FILE *com_file = fopen (PROGRAM_TO_CRACK, "rb");
    if (com_file == NULL)
        return;

    fseek (com_file, 0, SEEK_END);
    int file_size = ftell (com_file);
    fseek (com_file, 0, SEEK_SET);

    char *buffer = (char *)calloc (file_size, sizeof(char));
    if (buffer == NULL)
    {
        fclose (com_file);
        return;
    }
        
    fread (buffer, sizeof(char), file_size, com_file);
    fclose (com_file);

    FILE *crack_file = fopen (CRACKED_PROGRAM, "ab");
    fseek (crack_file, 0, SEEK_SET);
    int i = 0;

    while (i != file_size)
    {
        if (*(buffer + i) != 't')                       // 't' == JE
        {
            fprintf (crack_file, "%c", *(buffer + i));
            i++;
        } else {
            fprintf (crack_file, "u");                  // 'u' == JNE
            i++;
        }
    }

    fclose (crack_file);
    free (buffer);

    return;
}



