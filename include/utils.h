#pragma once
#include <stdbool.h>
#include <stdio.h>


void get_abs_path(char *out, const char *path, size_t size);

void get_backpack_dir(char *out, size_t size);

bool ensure_backpack_dir();

bool copy_file(const char *src, const char *dst);

bool delete_file_or_dir(const char *path);
