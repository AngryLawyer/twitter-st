#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include <gem.h>
#include <stdbool.h>
#include "window.h"


typedef struct _output_window {
    window_t handle;
    OBJECT *obj_tree;
    short obj_tree_length;
} OUTPUT_WINDOW;

short make_object_colors(short border_color, short text_color, short draw_mode, short fill_pattern, short fill_color);

OUTPUT_WINDOW* setup_output_window();
void redraw_output_window(OUTPUT_WINDOW *window, GRECT *box);
void destroy_output_window(OUTPUT_WINDOW *window);
#endif
