#include "../fs/operations.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

char const target_path1[] = "/f1";
char const link_path1[] = "/l1";

// here we test if the program symlinks itself (shouldn't happen)
int main() {
    assert(tfs_init(NULL) != -1);

    int f = tfs_open(target_path1, TFS_O_CREAT);
    assert(tfs_close(f) != -1);

    // create soft link on a file
    assert(tfs_sym_link(target_path1, link_path1) != -1);
    // create soft link on itself (should fail)
    assert(tfs_sym_link(link_path1, link_path1) == -1);

    printf("Successful test.\n");

    return 0;
}