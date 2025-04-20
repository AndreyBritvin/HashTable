#include "read_text.h"
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

__off_t get_file_len(const char *filename)
{
    assert(filename != NULL);

    struct stat st = {};
    stat(filename, &st);

    return st.st_size;
}

size_t get_lines_num(char *text_unaligned, size_t text_len)
{
    assert(text_unaligned != NULL);

    size_t lines_num = 0;

    for (size_t symbol = 0; symbol < text_len; symbol++)
    {
        if (text_unaligned[symbol] == '\n')
        {
            lines_num++;
        }
    }

    return lines_num;
}

int parse_lines(const char* filename, char** text, char*** text_lines)
{
    // const char* filename = "txt_parser/test.txt";
    // const char* filename = "txt_parser/war_and_peace_words.txt";
    size_t filesize = get_file_len(filename);

    FILE* SAFE_OPEN_FILE(words, filename, "r");

    char* text_unaligned = (char*) calloc(filesize + 10, sizeof(char));// {"12345", "5678", "1234", "12345"};
    fread(text_unaligned, filesize, sizeof(char), words);

    size_t lines_num = get_lines_num(text_unaligned, filesize);
    *text_lines = (char**) calloc(lines_num, sizeof(char*));
    size_t line_index = 0;
    char* prev_ptr = text_unaligned;

    for (size_t i = 0; i < filesize; i++)
    {
        // printf("text_unaligned[i]=%c\n", text_unaligned[i]);
        if ((text_unaligned)[i] == '\n')
        {
            (*text_lines)[line_index++] = prev_ptr;
            (text_unaligned)[i] = '\0';
            prev_ptr = &(text_unaligned)[i] + 1;
        }
    }

    *text = (char *) calloc(lines_num * 32, sizeof(char)); // TODO: replace 32 to cool type
    for (size_t i = 0; i < lines_num; i++)
    {
        strcpy(&(*text)[i * 32], (*text_lines)[i]);
        (*text_lines)[i] = &(*text)[i * 32];
    }

    free(text_unaligned);
    fclose(words);

    return lines_num;
}
