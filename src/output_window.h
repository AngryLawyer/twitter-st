#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include <gem.h>
#include "window.h"

window_t setup_output_window();
void redraw_output_window(window_t window, GRECT *box, OBJECT *object);
void destroy_output_window(window_t window);
#endif
