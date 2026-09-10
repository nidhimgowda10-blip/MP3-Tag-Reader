/*
* Name        : Nidhi M
* Date        : 04-08-2026
* Description : Contains utility functions for MP3 Tag Reader. Handles operation checking, help display, and integer to big-endian byte conversion.
*/

#include "../include/mp3.h"

OperationType check_operation(char *argv[])
{
    if(strcmp(argv[1], "-h") == 0)
    {
        return HELP;
    }
    else if(strcmp(argv[1], "-v") == 0)
    {
        return VIEW;
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        return EDIT;
    }
    else
    {
        return UNSUPPORTED;
    }
}

void display_help(void)
{
    printf("=============================================\n");
    printf("          MP3 TAG READER - HELP MENU\n");
    printf("=============================================\n");
    printf("./a.out -h                         : Display Help Menu\n");
    printf("./a.out -v <file.mp3>              : View MP3 Tag Information\n");
    printf("./a.out -e <option> <value> <file.mp3> : Edit MP3 Tag\n");
}

void int_to_big_endian(int value, unsigned char size[])
{
    size[0] = (value >> 24) & 0xFF;
    size[1] = (value >> 16) & 0xFF;
    size[2] = (value >> 8) & 0xFF;
    size[3] = value & 0xFF;
}