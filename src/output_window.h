#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include "window.h"

window_t setup_output_window();
void redraw_output_window(window_t window, short handle);
void destroy_output_window(window_t window);
#endif
