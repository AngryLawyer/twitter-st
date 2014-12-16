#include <gem.h>
#include <string.h>
#include <stdlib.h>
#include "window.h"
#include "output_window.h"

OUTPUT_WINDOW* setup_output_window() {
    OUTPUT_WINDOW *window = calloc(1, sizeof(OUTPUT_WINDOW));
    window->obj_tree_length = 1;
    window->obj_tree = calloc(window->obj_tree_length, sizeof(OBJECT));

    short x_loc;
    short y_loc;
    short height;
    short width;

    wind_get(0, WF_CURRXYWH, &x_loc, &y_loc, &width, &height);
    window->handle = wind_create(NAME, x_loc, y_loc, width, height);
    wind_open(window->handle, x_loc, y_loc, width, height);

    OBJECT *box = &window->obj_tree[0];
    box->ob_next = -1;
    box->ob_head = -1;
    box->ob_tail = -1;
    box->ob_type = G_BOX;
    wind_get(window->handle, WF_WORKXYWH, &box->ob_x, &box->ob_y, &box->ob_width, &box->ob_height);

    //OBJECT *text = &window->obj_tree[1];
    //objc_add(window->obj_tree, 0, 1);
    

    //window->obj_tree[1].ob_type = G_TEXT;
    //objc_add(window->obj_tree, 0, 1);
    //window->obj_tree[1].ob_spec.tedinfo = &window->tedinfo;

    /*window->tedinfo.te_ptext = "Hello again hello";
    window->tedinfo.te_font = 3;
    window->tedinfo.te_color = 2; //FIXME
    window->tedinfo.te_txtlen = strlen(window->tedinfo.te_ptext);*/

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
    free(window->obj_tree);
    window->obj_tree_length = 0;
    wind_close(window->handle);
    wind_delete(window->handle);
    free(window);
    window = NULL;
}
