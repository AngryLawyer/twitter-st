#include <gem.h>
#include <stdbool.h>
#include <string.h>
#include "window.h"

short make_object_colors(short border_color, short text_color, short draw_mode, short fill_pattern, short fill_color) {
    return (border_color << 12) | (text_color << 8) | (draw_mode << 7) | (fill_pattern << 4) | fill_color;
}

bool tokenize_multiline(char *buffer, char *input, short max_width, short text_size, short *last_index) {
    short input_length = strlen(input);
    short buffer_position = 0;

    //Bail out if we're at the end of input
    if (*last_index >= input_length) {
        return false;
    }

    while (*last_index < input_length) {
        if (input[*last_index] == '\n') {
            buffer[buffer_position] = 0;
            (*last_index)++;
            break;
        } else {
            buffer[buffer_position] = input[*last_index];
            buffer_position++;
            (*last_index)++;
        }
    }

    //If we need to wrap, we should do so now
    short width_char_difference = buffer_position - (max_width / text_size);
    short inspected_char = 0;
    short original_last_index = *last_index;
    if (width_char_difference > 0) {
        inspected_char = buffer_position - width_char_difference;
        (*last_index) -= width_char_difference;

        while (inspected_char > 0 && buffer[inspected_char] != ' ') {
            inspected_char--;
            (*last_index)--;
        }
        if (buffer[inspected_char] == ' ') {
            buffer[inspected_char] = 0;
        } else {
            *last_index = original_last_index;
        }
    }
    return true;
}
