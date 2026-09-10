/*
* Name        : Nidhi M
* Date        : 04-08-2026
* Description : Header file for MP3 Tag Reader project. Contains structures, enums and function declarations used for viewing and editing ID3v2.3 metadata.
*/

#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return Status */
typedef enum
{
    SUCCESS,
    FAILURE
} Status;

/* Operation Type */
typedef enum
{
    HELP,
    VIEW,
    EDIT,
    UNSUPPORTED
} OperationType;

/* Frame Header */
typedef struct
{
    char frame_id[5];
    int frame_size;
    char flags[2];

} FrameHeader;

/* MP3 Information */
typedef struct
{
    char *src_fname;
    FILE *fptr_src;

    char version[10];

    char title[100];
    char artist[100];
    char album[100];
    char year[10];
    char genre[50];

    char *edit_option;
    char *edit_data;

    FILE *fptr_dest;
    char *dest_fname;

} TagReaderInfo;


/* utils.c */
OperationType check_operation(char *argv[]);
void display_help(void);
void int_to_big_endian(int value, unsigned char size[]);


/* validate.c */
Status validate_view_args(char *argv[], TagReaderInfo *tag);
Status open_files(TagReaderInfo *tag);


/* view.c */
Status read_header(TagReaderInfo *tag);
Status read_version(TagReaderInfo *tag);
Status read_frame(TagReaderInfo *tag, char *frame_id, char *data);
Status view_tags(TagReaderInfo *tag);


/* edit.c */
Status validate_edit_args(char *argv[], TagReaderInfo *tag);
Status edit_tags(TagReaderInfo *tag);
Status open_dest_file(TagReaderInfo *tag);
Status copy_header(TagReaderInfo *tag);
Status edit_frame(TagReaderInfo *tag);
Status update_mp3_file(TagReaderInfo *tag);

#endif