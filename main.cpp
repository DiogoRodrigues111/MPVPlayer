#include <iostream>

extern "C" {

    /* PART OF C LANGUAGE
       because libmpv is writing in C. */

    #include <mpv/client.h>
    #include <stdio.h>
    #include <stdlib.h>

    typedef int u32;

    static inline void check_error(
            u32 status)
    {
        if (status < 0) {
            printf("Failed to Create and Instance new values of ... \n");
            exit(1);    // FAILED
        }
    }

    mpv_handle* CreateNewInstance(
            mpv_handle* ctx, char** pargs)
    {
        const char* pass_args[] = {"loadfile", pargs[1], 0};
        ctx = mpv_create();
        if (!ctx) printf("Error to Create an instance of Handler MPV \n");
        check_error(mpv_initialize(ctx));
        check_error(mpv_set_option_string(ctx, "input-default-bindings", "yes"));
        check_error(mpv_set_option_string(ctx, "input-vo-keyboard", "yes"));
        u32 val = 1;
        check_error(mpv_set_option(ctx, "osc", MPV_FORMAT_FLAG, &val));
        check_error(mpv_command(ctx, pass_args));   // PASS FileLoad.
        while ( 1 ) {
            mpv_event *event = mpv_wait_event(ctx, 10000);
            if (event->event_id == MPV_EVENT_SHUTDOWN) {
                break;
            }

            if (event->event_id == MPV_EVENT_END_FILE) {
                check_error(mpv_command(ctx, pass_args));
            }

            if (ctx == 0) {
                // End file release CTX session.
                // And Close with code 0.
                mpv_terminate_destroy(ctx);
            }
        }
        return ctx;
    }
}

int main(int argc, char** argv)
{
    static mpv_handle* ctx;

    if (argc != 2)
        std::cout << "You have pass a arguments here \n";

    CreateNewInstance(ctx, argv);

    return 0;
}
