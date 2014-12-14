#include <gem.h>
#include "window.h"
#include "output_window.h"

window_t setup_output_window() {
    short x_loc;
    short y_loc;
    short height;
    short width;

    short wind_handle;

    wind_get(0, WF_CURRXYWH, &x_loc, &y_loc, &width, &height);
    wind_handle = wind_create(NAME, x_loc, y_loc, width, height);
    wind_open(wind_handle, x_loc, y_loc, width, height);

    wind_set_str(wind_handle, WF_NAME, "Twitter");
    return wind_handle;
}

void redraw_output_window(window_t window, GRECT *box, OBJECT *object) {
    object->ob_width = box->g_w;
    object->ob_height = box->g_h;
    object->ob_x = box->g_x;
    object->ob_y = box->g_y;
    objc_draw_grect(object, 0, 0, box);
	/*graf_mouse(M_OFF, 0);
    short pixels[4] = {0, 0, 0, 0};
    wind_get(window, WF_WORKXYWH, &pixels[0], &pixels[1], &pixels[2], &pixels[3]);
    //Wipe the background...
    vsf_color(handle, 0);
    vr_recfl(handle, pixels);

    //Draw some text!
    v_gtext(handle, pixels[0], pixels[1] + 12, "Now this is a story all about how my life got flipped turned upside down");
	graf_mouse(M_ON, 0);*/
}

void destroy_output_window(window_t window) {
    wind_close(window);
    wind_delete(window);
}
