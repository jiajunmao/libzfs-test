#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <libzfs_core.h>

// struct statzfs {
// 	long dummy;
// };

int main()
{
    // struct statzfs stat;
    // stat.dummy = 250;

    char* temp = "My String";
    char* my_str = malloc(strlen(temp) + 1);
    strcpy(my_str, temp);

    printf("Str len %d, sizeof %d\n", strlen(my_str), sizeof(my_str));

    long int amma = syscall(548, my_str, strlen(my_str));
    printf("System call statzfs returned %ld\n", amma);

    if (libzfs_core_init() != 0) {
        fprintf(stderr, "Can't init libzfs\n");
        return 101;
    }


    printf("libzfs init\n");

    return 0;
}