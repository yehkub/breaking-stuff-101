#define _XOPEN_SOURCE 700
#include <stdio.h>

#include <yehkub/yehkub.h>
#include <yehkub/sys/signal.h>

// Registers signals to be handled by custom signal handler
int reghsignals(void (*sighandler)(int), int num_signals, ...) {
    va_list args;
    va_start(args, num_signals);

    struct sigaction sa;
    sa.sa_handler = sighandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    for (int i = 0; i < num_signals; i++) {
        if (sigaction(va_arg(args, int), &sa, NULL) != EXIT_SUCCESS) { return EXIT_FAILURE; }
    }

    va_end(args);
    return EXIT_SUCCESS;
}