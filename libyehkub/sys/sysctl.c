#include <yehkub/yehkub.h>          /* base */
#include <yehkub/sys/sysctl.h>

int read_sys_info(char *bufout, const char *dmipath, size_t idsz) {
    if (bufout == NULL) { return EXIT_FAILURE; }
    
    FILE *fp = fopen(dmipath, "r");
    if (!fp) { return EXIT_FAILURE; }

    fgets(bufout, idsz, fp);
    fclose(fp);

    return EXIT_SUCCESS;
}
