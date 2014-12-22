#ifndef WINDOW_H
#define WINDOW_H

#include <gem.h>
#include <stdbool.h>

typedef short window_t;

bool tokenize_multiline(char *buffer, const char *input, short max_width, short text_size, short *last_index);
short make_object_colors(short border_color, short text_color, short draw_mode, short fill_pattern, short fill_color);
#endif
