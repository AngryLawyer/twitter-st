#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include <gem.h>
#include <stdbool.h>
#include "window.h"


typedef struct _output_window {
    window_t handle;
    OBJECT *obj_tree;
    short obj_tree_length;
    char *text;
    short workstation;
} OUTPUT_WINDOW;

short draw_multiline(PARMBLK *parmblock);
OUTPUT_WINDOW* setup_output_window(short workstation);
void redraw_output_window(OUTPUT_WINDOW *window, GRECT *box);
void destroy_output_window(OUTPUT_WINDOW *window);
#endif
