#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

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

int main()
{
// TODO: go to antoher function
    // const char* filename = "txt_parser/test.txt";
    const char* filename = "txt_parser/war_and_peace_words.txt";
    size_t filesize = get_file_len(filename);
    FILE* SAFE_OPEN_FILE(words, filename, "r");

    char* text = (char*) calloc(filesize + 10, sizeof(char));// {"12345", "5678", "1234", "12345"};
    fread(text, filesize, sizeof(char), words);

    size_t lines_num = get_lines_num(text, filesize);
    char** text_lines = (char**) calloc(lines_num, sizeof(char*));
    size_t line_index = 0;
    char* prev_ptr = text;
    for (size_t i = 0; i < filesize; i++)
    {
        // printf("text[i]=%c\n", text[i]);
        if (text[i] == '\n')
        {
            text_lines[line_index++] = prev_ptr;
            text[i] = '\0';
            prev_ptr = &text[i] + 1;
        }
    }

    for (size_t i = 0; i < lines_num; i++)
    {
        // printf("i = %u, %s\n", i, text_lines[i]);
    }

    hash_table_t my_ht = {};

    ht_ctor(&my_ht, 600000 / 15);
    // ht_insert(&my_ht, "12345");
    // ht_insert(&my_ht, "5678");
    // ht_insert(&my_ht, "03345");
    // ht_insert(&my_ht, "03345");
    ht_fill(&my_ht, text_lines, lines_num);
    ht_dump(&my_ht);
    ht_dtor(&my_ht);
    free(text_lines);
    free(text);
    fclose(words);

    return EXIT_SUCCESS;
}
