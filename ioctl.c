#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <libzfs_core.h>
#include <libnvpair.h>

int main() {

    if (libzfs_core_init() != 0) {
        fprintf(stderr, "Can't init libzfs\n");
        return 101;
    }

    lzc_mlec_test();

    libzfs_core_fini();
    
    return 0;
}