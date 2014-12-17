#include <gem.h>
#include <string.h>
#include <stdlib.h>
#include "window.h"
#include "output_window.h"

short make_object_colors(short border_color, short text_color, short draw_mode, short fill_pattern, short fill_color) {
    return (border_color << 12) | (text_color << 8) | (draw_mode << 7) | (fill_pattern << 4) | fill_color;
}

short draw_multiline(PARMBLK *parmblock) {
    GRECT clip_area;
    short sizing = 4;

    //Set up clipping
    short handle = parmblock->pb_parm;
    vs_clip(handle, 1, &parmblock->pb_xc);
    vsf_interior(handle, 1);
    vsf_color(handle, 6);
    vr_recfl(handle, &parmblock->pb_x);   // clear entire message area
    vsl_color(handle, 1);

    vst_height(handle, sizing, &sizing, &sizing, &sizing, &sizing);
    v_gtext(handle, parmblock->pb_x, parmblock->pb_y + 4, "HELLO HELLO");
    vs_clip(handle, 0, &parmblock->pb_x);

    /*WORD   pxy[4];
    WORD   ycurr;

    set_clip(TRUE, clip_area);
    vsf_color(vdi_handle, WHITE);
    rc_grect_to_array(&work_area, pxy);
    graf_mouse(M_OFF,(MFORM *)0l);
    vr_recfl(vdi_handle, pxy);   // clear entire message area

    vsl_color(vdi_handle,BLACK);
    vswr_mode(vdi_handle,MD_REPLACE);
    vsl_type (vdi_handle,FIS_SOLID);
    vswr_mode(vdi_handle, 1);
    ycurr = work_area.g_y - 1;
    while (*strptr)         // loop through text strings
    {
       ycurr += gl_hbox;
       v_gtext(vdi_handle, work_area.g_x, ycurr, *strptr++);
    }
    graf_mouse(M_ON,(MFORM *)0l);
    set_clip(FALSE, clip_area);*/
    return 0;
}

OUTPUT_WINDOW* setup_output_window(short workstation) {
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

    //Add our own multiline handling block
    OBJECT *text = &window->obj_tree[1];
    text->ob_next = -1;
    text->ob_head = -1;
    text->ob_tail = -1;

    USERBLK *user_block = malloc(sizeof(USERBLK));
    user_block->ub_code = &draw_multiline;
    user_block->ub_parm = workstation;

    objc_add(window->obj_tree, 0, 1);
    text->ob_type = G_USERDEF;
    text->ob_width = box->ob_width;
    text->ob_height = box->ob_height;
    text->ob_spec.userblk = user_block;

    /*TEDINFO *info = calloc(1, sizeof(TEDINFO));
    info->te_font = 5;
    info->te_color = make_object_colors(0, 1, 1, 7, 0);
    info->te_ptext = "Hello again hello";
    info->te_txtlen = strlen(info->te_ptext);
    text->ob_spec.tedinfo = info;*/

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
