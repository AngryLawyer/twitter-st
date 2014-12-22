#include <gem.h>
#include <string.h>
#include <stdlib.h>
#include "window.h"
#include "output_window.h"

short draw_multiline(PARMBLK *parmblock) {
    GRECT clip_area;
    short sizing = 4;

    //Set up clipping
    OUTPUT_WINDOW *window = (OUTPUT_WINDOW*)parmblock->pb_parm;
    short handle = window->workstation;
    char buffer[255];
    short last_index = 0;

    short draw_region[4] = {
        parmblock->pb_x, parmblock->pb_y, parmblock->pb_x + parmblock->pb_w, parmblock->pb_y + parmblock->pb_h
    };
    short clip_region[4] = {
        parmblock->pb_xc, parmblock->pb_yc, parmblock->pb_xc + parmblock->pb_wc, parmblock->pb_yc + parmblock->pb_hc
    };

    vs_clip(handle, 1, clip_region);
    vsf_interior(handle, 1);
    //vsf_color(handle, 6);
    //vr_recfl(handle, draw_region);   // clear entire message area
    vsl_color(handle, 1);

    vst_height(handle, sizing, &sizing, &sizing, &sizing, &sizing);

    short position = 6;
    while (tokenize_multiline(buffer, window->text, parmblock->pb_w, sizing, &last_index)) {
        v_gtext(handle, parmblock->pb_x, parmblock->pb_y + position, buffer);
        position += sizing;
    }
    vs_clip(handle, 0, clip_region);

    return 0;
}

OUTPUT_WINDOW* setup_output_window(short workstation) {
    OUTPUT_WINDOW *window = calloc(1, sizeof(OUTPUT_WINDOW));
    window->obj_tree_length = 2;
    window->obj_tree = calloc(window->obj_tree_length, sizeof(OBJECT));
    window->workstation = workstation;
    window->text = "Llama llama llama\nllama duck\nllama llama llama llama llama llama\nHOLLLLLLAAAAAAAAAAAAAAAAAAAAAAAAAA";

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

    //Add our own multiline handling block
    OBJECT *text = &window->obj_tree[1];
    text->ob_next = -1;
    text->ob_head = -1;
    text->ob_tail = -1;

    USERBLK *user_block = malloc(sizeof(USERBLK));
    user_block->ub_code = &draw_multiline;
    user_block->ub_parm = (int)window;

    objc_add(window->obj_tree, 0, 1);
    text->ob_type = G_USERDEF;
    text->ob_width = box->ob_width - 1; //adjust for border
    text->ob_height = box->ob_height - 1;
    text->ob_spec.userblk = user_block;

    wind_set_str(window->handle, WF_NAME, "Twitter");
    return window;
}

void redraw_output_window(OUTPUT_WINDOW *window, GRECT *box) {
    objc_draw_grect(window->obj_tree, 0, 1, box);
}

void destroy_output_window(OUTPUT_WINDOW *window) {
    objc_delete(window->obj_tree, 1);
    free(window->obj_tree[1].ob_spec.userblk);
    free(window->obj_tree);
    window->obj_tree_length = 0;
    wind_close(window->handle);
    wind_delete(window->handle);
    free(window);
    window = NULL;
}
