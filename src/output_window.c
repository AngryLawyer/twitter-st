#include <gem.h>
#include <string.h>
#include <stdlib.h>
#include "window.h"
#include "output_window.h"

short make_object_colors(short border_color, short text_color, short draw_mode, short fill_pattern, short fill_color) {
    return (border_color << 12) | (text_color << 8) | (draw_mode << 7) | (fill_pattern << 4) | fill_color;
}

OUTPUT_WINDOW* setup_output_window() {
    OUTPUT_WINDOW *window = calloc(1, sizeof(OUTPUT_WINDOW));
    window->obj_tree_length = 2;
    window->obj_tree = calloc(window->obj_tree_length, sizeof(OBJECT));

    short x_loc;
    short y_loc;
    short height;
    short width;

    wind_get(0, WF_CURRXYWH, &x_loc, &y_loc, &width, &height);
    window->handle = wind_create(NAME, x_loc, y_loc, width, height);
    wind_open(window->handle, x_loc + 10, y_loc + 10, width / 2, height / 2);

    OBJECT *box = &window->obj_tree[0];
    box->ob_next = -1;
    box->ob_head = -1;
    box->ob_tail = -1;
    box->ob_type = G_BOX;
    wind_get(window->handle, WF_WORKXYWH, &box->ob_x, &box->ob_y, &box->ob_width, &box->ob_height);

    OBJECT *text = &window->obj_tree[1];
    text->ob_next = -1;
    text->ob_head = -1;
    text->ob_tail = -1;
    
    objc_add(window->obj_tree, 0, 1);
    text->ob_type = G_TEXT;
    text->ob_width = box->ob_width;
    text->ob_height = 16;

    TEDINFO *info = calloc(1, sizeof(TEDINFO));
    info->te_font = 5;
    info->te_color = make_object_colors(0, 1, 1, 7, 0);
    info->te_ptext = "Hello again hello";
    info->te_txtlen = strlen(info->te_ptext);
    text->ob_spec.tedinfo = info;

    wind_set_str(window->handle, WF_NAME, "Twitter");
    return window;
}

void redraw_output_window(OUTPUT_WINDOW *window, GRECT *box) {
    /*window->obj_tree[0].ob_width = box->g_w;
    window->obj_tree[0].ob_height = box->g_h;
    window->obj_tree[0].ob_x = box->g_x;
    window->obj_tree[0].ob_y = box->g_y;
    window->obj_tree[1].ob_width = box->g_w;
    window->obj_tree[1].ob_height = box->g_h;*/
    objc_draw_grect(window->obj_tree, 0, 1, box);
}

void destroy_output_window(OUTPUT_WINDOW *window) {
    objc_delete(window->obj_tree, 1);
    free(window->obj_tree[1].ob_spec.tedinfo);
    free(window->obj_tree);
    window->obj_tree_length = 0;
    wind_close(window->handle);
    wind_delete(window->handle);
    free(window);
    window = NULL;
}
