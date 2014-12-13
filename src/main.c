#include <stdio.h>
#include <gem.h>

#include "window.h"
#include "output_window.h"

void app_set_up(window_t *output_window, short *workstation) {
    short work_in[11];
    short work_out[57];
    short dummy;

    appl_init();
    *workstation = graf_handle(&dummy, &dummy, &dummy, &dummy);

    for (short loop = 0; loop < 10; loop++) {
        work_in[loop] = 1;
    }

    work_in[10] = 2;

    v_opnvwk(work_in, workstation, work_out);

    *output_window = setup_output_window();
}

void clean_up(window_t output_window, short workstation) {
    destroy_output_window(output_window);
    v_clsvwk(workstation);
    appl_exit();
}

short main(short int argc, char *argv[]) {
    short button;
    short nul;

    window_t output_window;
    short workstation;
    app_set_up(&output_window, &workstation);

	graf_mouse(ARROW, 0);

    redraw_output_window(output_window, workstation);
    while(button == 0) {
        //vq_mouse(workstation, &button, &nul, &nul);
    }
    clean_up(output_window, workstation);
	return 0;
}
