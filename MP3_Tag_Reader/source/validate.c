/*
* Name        : Nidhi M
* Date        : 04-08-2026
* Description : Validates command line arguments and opens the MP3 file for reading operations.
*/

#include "../include/mp3.h"

Status validate_view_args(char *argv[], TagReaderInfo *tag)
{
    tag->src_fname = argv[2];

    if(tag->src_fname == NULL)
    {
        printf("ERROR: Please provide MP3 file\n");
        return FAILURE;
    }

    if(strstr(tag->src_fname, ".mp3") == NULL)
    {
        printf("ERROR: Invalid MP3 file\n");
        return FAILURE;
    }

    return open_files(tag);
}

/* Open MP3 file */
Status open_files(TagReaderInfo *tag)
{
    tag->fptr_src = fopen(tag->src_fname, "rb");

    if(tag->fptr_src == NULL)
    {
        printf("ERROR: Unable to open %s\n", tag->src_fname);
        return FAILURE;
    }

    printf("File opened successfully\n");

    return SUCCESS;
}