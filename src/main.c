#include <stdio.h>
#include <string.h>
#include <gem.h>

#include "window.h"
#include "output_window.h"

short message_handler(short messages[], window_t output_window) {
	short int x, y, w, h;
	short int out = 0;

	switch(messages[0]) {
		case WM_REDRAW:
			redraw_output_window(output_window, (GRECT *)&messages[4]);
			break;
		default:
			break;
	}

	/* Close down the window? */
	//if (out && win_open) close_window(win_handle);

	return out;
}

void handle_events(window_t output_window) {
    short int mx, my, button, keystate, dummy;
    unsigned short int key;
    short int breturn;
    short int top_wind;           /* Top window handle */
    short int type = 0, out = 0;
    short int time_remaining = 1000;
    short int base_clip[4];                    
    short messages[16];

    while (out != 1) {
        type = 0;
        while (!(type & MU_KEYBD) && !(type & MU_MESAG) && 
               !(type & MU_BUTTON) && !(type & MU_TIMER)) {

            type = evnt_multi(
                (MU_KEYBD | MU_MESAG | MU_BUTTON | MU_TIMER), 0x182, 3, 3,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 
                messages, time_remaining, &mx, &my,
                &button, &keystate, &key, &breturn);
        }

        /*wind_get(win_handle, WF_TOP, &top_wind, &dummy, &dummy, &dummy);
        if (top_wind != win_handle) {
            if (game_state == ACTIVE) game_state == FROZEN;
        }

        // Base clip region is the screen
        base_clip[0] = base_clip[1] = 0;
        base_clip[2] = SCw - 1;
        base_clip[3] = SCh - 1;
        vs_clip(handle, 1, base_clip);*/

        wind_update(BEG_UPDATE);

        if (type & MU_KEYBD) {
            switch(key) {
                case 0x011B:    /* Esc Pause Game */
                    out = 1;
                    break;
                default:
                    break;
            }
            type &= ~MU_KEYBD;
        }

        if (type & MU_MESAG) {
            out = message_handler(messages, output_window);
            type &= ~MU_MESAG;
        }

        wind_update(END_UPDATE);
    }
    return;
}

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

    OBJECT zebox;
    memset(&zebox, 0, sizeof(OBJECT));

    app_set_up(&output_window, &workstation);

    graf_mouse(ARROW, 0);
    handle_events(output_window);

    clean_up(output_window, workstation);
    return 0;
}
