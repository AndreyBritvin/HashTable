#include "read_text.h"
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>

__off_t get_file_len(const char *filename)
{
    assert(filename != NULL);

    struct stat st = {};
    stat(filename, &st);

    return st.st_size;
}

size_t get_lines_num(char *text, size_t text_len)
{
    assert(text != NULL);

    size_t lines_num = 0;

    for (size_t symbol = 0; symbol < text_len; symbol++)
    {
        if (text[symbol] == '\n')
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

    *text = (char*) calloc(filesize + 10, sizeof(char));// {"12345", "5678", "1234", "12345"};
    fread(*text, filesize, sizeof(char), words);

    size_t lines_num = get_lines_num(*text, filesize);
    *text_lines = (char**) calloc(lines_num, sizeof(char*));
    size_t line_index = 0;
    char* prev_ptr = *text;

    for (size_t i = 0; i < filesize; i++)
    {
        // printf("text[i]=%c\n", text[i]);
        if ((*text)[i] == '\n')
        {
            (*text_lines)[line_index++] = prev_ptr;
            (*text)[i] = '\0';
            prev_ptr = &(*text)[i] + 1;
        }
    }

    fclose(words);

    return lines_num;
}
