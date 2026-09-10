/*
* Name        : Nidhi M
* Date        : 04-08-2026
* Description : Implements MP3 metadata viewing operations. Reads ID3v2.3 header and frames and displays title, artist, album, year and genre details.
*/

#include "../include/mp3.h"

/* Read ID3 Header */
Status read_header(TagReaderInfo *tag)
{
    char header[4];

    rewind(tag->fptr_src);

    fread(header, 1, 3, tag->fptr_src);
    header[3] = '\0';

    if(strcmp(header, "ID3") != 0)
    {
        printf("ERROR: ID3 Header not found\n");
        return FAILURE;
    }

    return SUCCESS;
}

/* Read Version */
Status read_version(TagReaderInfo *tag)
{
    unsigned char version[2];

    fread(version, 1, 2, tag->fptr_src);

    sprintf(tag->version, "2.%d.%d", version[0], version[1]);

    return SUCCESS;
}

/* Read Specific Frame */
Status read_frame(TagReaderInfo *tag, char *frame_id, char *data)
{
    FrameHeader frame;
    unsigned char size[4];
    char encoding;

    fseek(tag->fptr_src, 10, SEEK_SET);

    while(1)
    {
        if(fread(frame.frame_id, 1, 4, tag->fptr_src) != 4)
        {
            return FAILURE;
        }

        frame.frame_id[4] = '\0';

        fread(size, 1, 4, tag->fptr_src);

        frame.frame_size = (size[0] << 24) |
                           (size[1] << 16) |
                           (size[2] << 8) |
                            size[3];

        fread(frame.flags, 1, 2, tag->fptr_src);

        if(strcmp(frame.frame_id, frame_id) == 0)
        {
            fread(&encoding, 1, 1, tag->fptr_src);

            fread(data, 1, frame.frame_size - 1, tag->fptr_src);

            data[frame.frame_size - 1] = '\0';

            return SUCCESS;
        }

        fseek(tag->fptr_src, frame.frame_size, SEEK_CUR);
    }
}

/* Display MP3 Tags */
Status view_tags(TagReaderInfo *tag)
{
    if(read_header(tag) == FAILURE)
        return FAILURE;

    if(read_version(tag) == FAILURE)
        return FAILURE;

    if(read_frame(tag, "TIT2", tag->title) == FAILURE)
        return FAILURE;

    if(read_frame(tag, "TPE1", tag->artist) == FAILURE)
        return FAILURE;

    if(read_frame(tag, "TALB", tag->album) == FAILURE)
        return FAILURE;

    if(read_frame(tag, "TYER", tag->year) == FAILURE)
        return FAILURE;

    if(read_frame(tag, "TCON", tag->genre) == FAILURE)
        return FAILURE;

    printf("\n========================================\n");
    printf("         MP3 TAG INFORMATION\n");
    printf("========================================\n");
    printf("Version : %s\n", tag->version);
    printf("Title   : %s\n", tag->title);
    printf("Artist  : %s\n", tag->artist);
    printf("Album   : %s\n", tag->album);
    printf("Year    : %s\n", tag->year);
    printf("Genre   : %s\n", tag->genre);
    printf("========================================\n");

    return SUCCESS;
}