/*
* Name        : Nidhi M
* Date        : 04-08-2026
* Description : Implements MP3 metadata editing operations. Searches ID3v2.3 frames, updates selected metadata, and creates the modified MP3 file.
*/

#include "../include/mp3.h"

/* Validate edit arguments */
Status validate_edit_args(char *argv[], TagReaderInfo *tag)
{
    if(argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
    {
        printf("ERROR: Invalid edit arguments\n");
        return FAILURE;
    }

    tag->edit_option = argv[2];
    tag->edit_data = argv[3];
    tag->src_fname = argv[4];

    return open_files(tag);
}

/* Open temporary file */
Status open_dest_file(TagReaderInfo *tag)
{
    tag->dest_fname = "temp.mp3";

    tag->fptr_dest = fopen(tag->dest_fname, "wb");

    if(tag->fptr_dest == NULL)
    {
        printf("ERROR: Unable to create temp.mp3\n");
        return FAILURE;
    }

    printf("Temporary file created successfully\n");

    return SUCCESS;
}

/* Copy ID3 Header */
Status copy_header(TagReaderInfo *tag)
{
    char buffer[10];

    if(fread(buffer, 1, 10, tag->fptr_src) != 10)
        return FAILURE;

    if(fwrite(buffer, 1, 10, tag->fptr_dest) != 10)
        return FAILURE;

    return SUCCESS;
}

/* Search frame and edit */
Status edit_frame(TagReaderInfo *tag)
{
    FrameHeader frame;
    unsigned char size[4];
    char frame_to_edit[5];
    int found = 0;

    if(strcmp(tag->edit_option, "-t") == 0)
        strcpy(frame_to_edit, "TIT2");
    else if(strcmp(tag->edit_option, "-a") == 0)
        strcpy(frame_to_edit, "TPE1");
    else if(strcmp(tag->edit_option, "-A") == 0)
        strcpy(frame_to_edit, "TALB");
    else if(strcmp(tag->edit_option, "-y") == 0)
        strcpy(frame_to_edit, "TYER");
    else if(strcmp(tag->edit_option, "-g") == 0)
        strcpy(frame_to_edit, "TCON");
    else
    {
        printf("ERROR: Invalid edit option\n");
        return FAILURE;
    }

    fseek(tag->fptr_src, 10, SEEK_SET);

    while(fread(frame.frame_id, 1, 4, tag->fptr_src) == 4)
    {
        frame.frame_id[4] = '\0';

        if(fread(size, 1, 4, tag->fptr_src) != 4)
            return FAILURE;

        frame.frame_size = (size[0] << 24) |
                           (size[1] << 16) |
                           (size[2] << 8) |
                            size[3];

        if(fread(frame.flags, 1, 2, tag->fptr_src) != 2)
            return FAILURE;

        printf("Frame : %-4s Size : %d\n", frame.frame_id, frame.frame_size);

        if(strcmp(frame.frame_id, frame_to_edit) == 0)
        {
            found = 1;

            printf("Frame to edit found : %s\n", frame.frame_id);

            fwrite(frame.frame_id, 1, 4, tag->fptr_dest);

            int new_size = strlen(tag->edit_data) + 1;

            unsigned char new_size_buf[4];

            int_to_big_endian(new_size, new_size_buf);

            fwrite(new_size_buf, 1, 4, tag->fptr_dest);

            fwrite(frame.flags, 1, 2, tag->fptr_dest);

            fseek(tag->fptr_src, frame.frame_size, SEEK_CUR);

            char encoding = 0x00;

            fwrite(&encoding, 1, 1, tag->fptr_dest);

            fwrite(tag->edit_data, 1, strlen(tag->edit_data), tag->fptr_dest);
                
            char buffer[1024];
            size_t bytes_read;

            while((bytes_read = fread(buffer, 1, sizeof(buffer), tag->fptr_src)) > 0)
            {
                fwrite(buffer, 1, bytes_read, tag->fptr_dest);
            }
            break;
        }
        else
        {
            fwrite(frame.frame_id, 1, 4, tag->fptr_dest);
            fwrite(size, 1, 4, tag->fptr_dest);
            fwrite(frame.flags, 1, 2, tag->fptr_dest);

            char buffer[1024];
            int remaining = frame.frame_size;

            while(remaining > 0)
            {
                int bytes = remaining > 1024 ? 1024 : remaining;

                fread(buffer, 1, bytes, tag->fptr_src);
                fwrite(buffer, 1, bytes, tag->fptr_dest);

                remaining -= bytes;
            }
        }
    }
    if(found == 0)
    {
        printf("ERROR: Frame not found\n");
        return FAILURE;
    }

    return SUCCESS;
}

/* Edit operation */
Status edit_tags(TagReaderInfo *tag)
{
    if(open_dest_file(tag) == FAILURE)
        return FAILURE;

    if(copy_header(tag) == FAILURE)
        return FAILURE;

    if(edit_frame(tag) == FAILURE)
        return FAILURE;

    if(update_mp3_file(tag) == FAILURE)
        return FAILURE;

    return SUCCESS;
}

/* Replace original file */
Status update_mp3_file(TagReaderInfo *tag)
{
    if(fclose(tag->fptr_src) != 0)
        return FAILURE;

    if(fclose(tag->fptr_dest) != 0)
        return FAILURE;

    if(remove(tag->src_fname) != 0)
        return FAILURE;

    if(rename("temp.mp3", tag->src_fname) != 0)
        return FAILURE;

    printf("Edit successful\n");

    return SUCCESS;
}