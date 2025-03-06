#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main ()
{
    FILE *com_file = fopen ("program.com", "rb");
    if (com_file == NULL)
        return 1;

    fseek (com_file, 0, SEEK_END);
    int file_size = ftell (com_file);
    fseek (com_file, 0, SEEK_SET);

    char *buffer = (char *)calloc (file_size, sizeof(char));
    if (buffer == NULL)
        return 1;
        
    fread (buffer, sizeof(char), file_size, com_file);

    fclose (com_file);

    FILE *file = fopen ("hacked_program.com", "ab");
    int i = 0;

    while (i != file_size)
    {
        if (*(buffer + i) != 't')
        {
            fprintf (file, "%c", *(buffer + i));
            i++;
        } else {
            fprintf (file, "u");
            i++;
        }
    }

    fclose (file);

    return 0;
}
