#include "../include/commands.h"
#include <stdio.h>
#include <sys/syslimits.h>
#include <dirent.h>

#include "../include/utils.h"


void cmd_list() {
    ensure_backpack_dir();

    char backpack_dir[PATH_MAX] = {0};
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    DIR *dr = opendir(backpack_dir);
    if (dr == NULL) {
        printf("Error opening backpack directory\n");
        return;
    }

    struct dirent *de;
    int count = 0;
    while ((de = readdir(dr)) != NULL) {
        if (de->d_name[0] == '.')
            continue;
        printf(" - %s\n", de->d_name);
        count++;
    }

    if (count == 0) printf("Backpack is empty\n");

    closedir(dr);
}

void cmd_add(const char *path) {
    ensure_backpack_dir();

    char src[PATH_MAX] = {0};
    get_abs_path(src, path, sizeof(src));


    char backpack_dir[PATH_MAX];
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    char dst[PATH_MAX] = {0};
    snprintf(dst, sizeof(dst), "%s/%s", backpack_dir, path);

    if (copy_file(src, dst)) {
        printf("Added %s to backpack\n", path);
    } else {
        printf("Failed to add %s to backpack\n", path);
    }
}

void cmd_cut(const char *path) {
    ensure_backpack_dir();

    char src[PATH_MAX] = {0};
    get_abs_path(src, path, sizeof(src));


    char backpack_dir[PATH_MAX];
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    char dst[PATH_MAX] = {0};
    snprintf(dst, sizeof(dst), "%s/%s", backpack_dir, path);

    if (copy_file(src, dst) && delete_file_or_dir(src)) {
        printf("Moved %s to backpack\n", path);
    } else {
        printf("Failed to move %s to backpack\n", path);
    }
}

void cmd_paste(const char *item) {
    ensure_backpack_dir();

    char backpack_dir[PATH_MAX];
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    char src[PATH_MAX] = {0};
    snprintf(src, sizeof(src), "%s/%s", backpack_dir, item);


    char dst[PATH_MAX] = {0};
    get_abs_path(dst, item, sizeof(dst));

    if (copy_file(src, dst)) {
        printf("Pasted %s from backpack\n", item);
    } else {
        printf("Failed to paste %s from backpack\n", item);
    }
}

void cmd_pop(const char *item) {
    ensure_backpack_dir();

    char backpack_dir[PATH_MAX];
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    char src[PATH_MAX] = {0};
    snprintf(src, sizeof(src), "%s/%s", backpack_dir, item);


    char dst[PATH_MAX] = {0};
    get_abs_path(dst, item, sizeof(dst));

    if (copy_file(src, dst) && delete_file_or_dir(src)) {
        printf("Moved %s from backpack\n", item);
    } else {
        printf("Failed to move %s from backpack\n", item);
    }
}

void cmd_remove(const char *item) {
    ensure_backpack_dir();

    char backpack_dir[PATH_MAX];
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    char target[PATH_MAX] = {0};
    snprintf(target, sizeof(target), "%s/%s", backpack_dir, item);

    if (delete_file_or_dir(target)) {
        printf("Removed %s from backpack\n", item);
    } else {
        printf("Failed to remove %s from backpack\n", item);
    }
}
