#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <libzfs_core.h>
#include <libzfs/sys/nvpair.h>   

typedef unsigned char uchar_t;

int main() {

    if (libzfs_core_init() != 0) {
        fprintf(stderr, "Can't init libzfs\n");
        return 101;
    }

    // Define list
    nvlist_t *nvl;
    const char *key = "data";
    const char *data = "wutever";
    size_t data_size = strlen(data) + 1;

    // Allocate the list
    if (nvlist_alloc(&nvl, NV_UNIQUE_NAME, 0) != 0) {
        fprintf(stderr, "Failed to allocate nvlist\n");
        return EXIT_FAILURE;
    }

    // Add binary data to the list
    if (nvlist_add_byte_array(nvl, key, (uchar_t*) data, data_size) != 0) {
        fprintf(stderr, "Failed to add binary data to nvlist\n");
        nvlist_free(nvl);
        return EXIT_FAILURE;
    }

    if (nvlist_add_uint64(nvl, "objset_id", 2)) {
        nvlist_free(nvl);
        return EXIT_FAILURE;
    }

    if (nvlist_add_uint64(nvl, "dn_object_id", 2)) {
        nvlist_free(nvl);
        return EXIT_FAILURE;
    }

    if (nvlist_add_uint64(nvl, "blk_id", 2)) {
        nvlist_free(nvl);
        return EXIT_FAILURE;
    }

    int ret = lzc_mlec_test("pool", nvl);
    printf("lzc_mlec_test returned %d\n", ret);

    nvlist_free(nvl);

    libzfs_core_fini();
    
    return 0;
}