#ifndef READ_TEXT_H__
#define READ_TEXT_H__

#include <stdio.h>
#include "utils.h"

__off_t get_file_len(const char *filename);
size_t get_lines_num(char *text, size_t text_len);
int parse_lines(const char* filename, char** text, char*** text_lines);

#endif // READ_TEXT_H__
