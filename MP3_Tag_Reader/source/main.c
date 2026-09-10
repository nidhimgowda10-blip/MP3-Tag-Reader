/*
* Name        : Nidhi M
* Date        : 04-08-2026
* Description : Main function for MP3 Tag Reader application. Handles command-line arguments and performs view and edit operations based on user input.
*/

#include "../include/mp3.h"

int main(int argc, char *argv[])
{
    TagReaderInfo tag;
    OperationType op;

    tag.fptr_src = NULL;
    tag.fptr_dest = NULL;

    if(argc < 2)
    {
        printf("ERROR: Invalid number of arguments\n");
        display_help();
        return FAILURE;
    }

    op = check_operation(argv);

    switch(op)
    {
        case HELP:
            display_help();
            break;

        case VIEW:
            if(validate_view_args(argv, &tag) == SUCCESS)
            {
                if(view_tags(&tag) == SUCCESS)
                {
                    printf("\nView operation completed successfully\n");
                }

                if(tag.fptr_src != NULL)
                    fclose(tag.fptr_src);
            }
            break;

        case EDIT:
            if(validate_edit_args(argv, &tag) == SUCCESS)
            {
                if(edit_tags(&tag) == SUCCESS)
                {
                    printf("\nEdit operation completed successfully\n");
                }
                else
                {
                    printf("\nEdit operation failed\n");
                }
            }
            break;

        default:
            printf("ERROR: Unsupported option\n");
            display_help();
            break;
    }

    return SUCCESS;
}