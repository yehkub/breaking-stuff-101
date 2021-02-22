#ifndef _YEHKUB_FINGERPRINT_H_
#define _YEHKUB_FINGERPRINT_H_

#include <yehkub/sys/sysctl.h>

#define UUID_LEN        36        /* Formatted UUID string length (dashes included) */
#define UUID_LEN_RAW    32        /* Raw/Unformatted UUID length (no dashes) */

/* Get a new UUID directly from kernel UUID interface ('/proc/sys/kernel/random/uuid'). Returns pointer to new UUID string or NULL on error */
#define gen_random_uuid(void)   read_sys_info("/proc/sys/kernel/random/uuid", UUID_LEN)
/* Read boot UUID created by kernel, which is not boot-persistent ('/proc/sys/kernel/random/boot_id'). Returns pointer to BOOT_UUID string or NULL on error */
#define read_boot_id(void)      read_sys_info("/proc/sys/kernel/random/boot_id", UUID_LEN)
/* Reads Machine ID from '/var/lib/dbus/machine-id' Returns pointer to MachineID string or NULL on error */
#define read_machine_id(void)   read_sys_info("/var/lib/dbus/machine-id", UUID_LEN_RAW)
/* Reads Product UUID from '/sys/class/dmi/id/product_uuid' Returns pointer to UUID string or NULL on error */
#define read_product_uuid(void) read_sys_info("/sys/class/dmi/id/product_uuid", UUID_LEN)

#endif