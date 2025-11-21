#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fts.h>
#include <copyfile.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/syslimits.h>

static const char *get_home_dir() {
    const char *home = getenv("HOME");
    if (home && home[0] != '\0')
        return home;

    struct passwd *pw = getpwuid(getuid());
    return pw ? pw->pw_dir : NULL;
}

void get_backpack_dir(char *out, size_t size) {
    const char *home = get_home_dir();
    snprintf(out, size, "%s/.backpack/items", home);
}

void get_abs_path(char *out, const char *path, size_t size) {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    snprintf(out, size, "%s/%s", cwd, path);
}

bool ensure_backpack_dir() {
    char backpack_dir[PATH_MAX];
    get_backpack_dir(backpack_dir, sizeof(backpack_dir));

    struct stat st = {0};
    if (stat(backpack_dir, &st) == -1) {
        if (mkdir(backpack_dir, 0700) == -1) {
            perror("mkdir");
            return false;
        }
    }
    return true;
}

bool copy_file_or_dir(const char *src, const char *dst) {
    if (copyfile(src, dst, NULL, COPYFILE_ALL | COPYFILE_RECURSIVE) == -1) {
        perror("copyfile");
        return false;
    }
    return true;
}

bool delete_file_or_dir(const char *path) {
    char *paths[] = {(char *) path, NULL};

    FTS *ftsp = fts_open(paths, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
    if (!ftsp) {
        perror("fts_open");
        return false;
    }

    FTSENT *ent;
    while ((ent = fts_read(ftsp)) != NULL) {
        switch (ent->fts_info) {
            case FTS_F:
            case FTS_SL:
            case FTS_SLNONE:
                if (unlink(ent->fts_path) == -1) {
                    perror("unlink");
                    fts_close(ftsp);
                    return false;
                }
                break;

            case FTS_DP:
                if (rmdir(ent->fts_path) == -1) {
                    perror("rmdir");
                    fts_close(ftsp);
                    return false;
                }
                break;
        }
    }

    fts_close(ftsp);
    return true;
}
