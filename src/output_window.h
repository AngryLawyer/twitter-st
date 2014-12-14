#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include <gem.h>
#include "window.h"

typedef struct _output_window {
    window_t handle;
    OBJECT obj_tree[2];
    TEDINFO tedinfo;
} OUTPUT_WINDOW;

void setup_output_window(OUTPUT_WINDOW *window);
void redraw_output_window(OUTPUT_WINDOW *window, GRECT *box);
void destroy_output_window(OUTPUT_WINDOW *window);
#endif
