#ifndef _YEHKUB_SIGNALCTL_H_
#define _YEHKUB_SIGNALCTL_H_

#include <stdarg.h>
#include <signal.h>

/* Registers signals to be handled by custom signal handler [ (void) sighandler(int sig); ] */
int reghsignals(void (*sighandler)(int), int num_signals, ...);

#endif