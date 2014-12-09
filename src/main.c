#include <stdio.h>
#include <gem.h>

short wind_handle;
short work_stn_hndle, handle;
static char *title = "Twitter Client";

void window_set_up() {
    short loop;
    short work_in[11];
    short work_out[57];
    short dummy;
    short x_loc = 50;
    short y_loc = 50;
    short height = 50;
    short width = 50;
    appl_init();
    handle = graf_handle(&dummy, &dummy, &dummy, &dummy);
    work_stn_hndle = handle;
    for (loop = 0; loop < 10; loop++) {
        work_in[loop] = 1;
    }
    work_in[10] = 2;
    wind_get(0, WF_CURRXYWH, &x_loc, &y_loc, &width, &height);
    v_opnvwk(work_in, &work_stn_hndle, work_out);
    wind_handle = wind_create(NAME | MOVER, x_loc, y_loc, width, height);
    wind_open(wind_handle, x_loc, y_loc, width, height);
    
    wind_set_str(wind_handle, WF_NAME, title);

}

void clean_up() {
    wind_close(wind_handle);
    wind_delete(wind_handle);
    v_clsvwk(work_stn_hndle);
    appl_exit();
}

short main(short int argc, char *argv[]) {
    short button;
    short nul;
    window_set_up();
    while(button == 0) {
        //vq_mouse(handle, &button, &nul, &nul);
    }
    clean_up();
	return 0;
}
