#include <gem.h>
#include <string.h>
#include "window.h"
#include "output_window.h"

void setup_output_window(OUTPUT_WINDOW *window) {
    memset(window, 0, sizeof(OUTPUT_WINDOW));
    window->obj_tree[0].ob_type = G_BOX;
    window->obj_tree[1].ob_type = G_TEXT;
    objc_add(window->obj_tree, 0, 1);
    window->obj_tree[1].ob_spec.tedinfo = &window->tedinfo;

    window->tedinfo.te_ptext = "Hello again hello";
    window->tedinfo.te_font = 3;
    window->tedinfo.te_color = 2; //FIXME
    window->tedinfo.te_txtlen = strlen(window->tedinfo.te_ptext);

    short x_loc;
    short y_loc;
    short height;
    short width;

    wind_get(0, WF_CURRXYWH, &x_loc, &y_loc, &width, &height);
    window->handle = wind_create(NAME, x_loc, y_loc, width, height);
    wind_open(window->handle, x_loc, y_loc, width, height);

    wind_set_str(window->handle, WF_NAME, "Twitter");
}

void redraw_output_window(OUTPUT_WINDOW *window, GRECT *box) {
    window->obj_tree[0].ob_width = box->g_w;
    window->obj_tree[0].ob_height = box->g_h;
    window->obj_tree[0].ob_x = box->g_x;
    window->obj_tree[0].ob_y = box->g_y;
    window->obj_tree[1].ob_width = box->g_w;
    window->obj_tree[1].ob_height = box->g_h;
    objc_draw_grect(window->obj_tree, 0, 1, box);
}

void destroy_output_window(OUTPUT_WINDOW *window) {
    wind_close(window->handle);
    wind_delete(window->handle);
}
