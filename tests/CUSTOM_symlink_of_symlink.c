#include "../fs/operations.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t const file_contents[] = "Hello!";
char const target_path1[] = "/f1";
char const link_path1[] = "/l1";
char const link_path2[] = "/l2";

// here we test if it opens the correct file when we symlink a symlink of a file
int main() {
    assert(tfs_init(NULL) != -1);

    int f = tfs_open(target_path1, TFS_O_CREAT);
    assert(f != -1);

    // write to file
    assert(tfs_write(f, file_contents, sizeof(file_contents)) == sizeof(file_contents));

    assert(tfs_close(f) != -1);

    // create soft link on a file
    assert(tfs_sym_link(target_path1, link_path1) != -1);
    // create a soft link on the first soft link
    assert(tfs_sym_link(link_path1, link_path2) != -1);

    int fh = tfs_open(link_path2, 0);
    assert(fh != -1);

    // compare de contents
    uint8_t buffer[sizeof(file_contents)];
    assert(tfs_read(fh, buffer, sizeof(buffer)) == sizeof(buffer));
    assert(memcmp(buffer, file_contents, sizeof(buffer)) == 0);

    assert(tfs_close(fh) != -1);

    printf("Successful test.\n");

    return 0;
}