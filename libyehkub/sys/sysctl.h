#ifndef _YEHKUB_SYSCTL_H_
#define _YEHKUB_SYSCTL_H_

#include <stdio.h>

/* Read one line of length (size_t) idsz from DMI descriptors - (const char) *dmipath */
int read_sys_info(char *bufout, const char *dmipath, size_t idsz);

#endif
