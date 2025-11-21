#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/commands.h"

struct Command {
    const char *name;

    void (*func)(const char *arg);

    bool needs_arg;
};

static struct Command commands[] = {
    {"list", (void(*)(const char *)) cmd_list, false},
    {"ls", (void(*)(const char *)) cmd_list, false},

    {"add", cmd_add, true},
    {"copy", cmd_add, true},
    {"cp", cmd_add, true},

    {"cut", cmd_cut, true},
    {"ct", cmd_cut, true},

    {"paste", cmd_paste, true},
    {"get", cmd_paste, true},

    {"pop", cmd_pop, true},

    {"remove", cmd_remove, true},
    {"rm", cmd_remove, true},
};

static const int command_count = sizeof(commands) / sizeof(commands[0]);

void print_usage() {
    printf("Usage: bp <command> [args]\n");
    printf("Commands:\n");
    for (int i = 0; i < command_count; i++) {
        if (i == 0 || strcmp(commands[i].name, commands[i - 1].name) != 0) {
            printf("  %s%s\n", commands[i].name, commands[i].needs_arg ? " <arg>" : "");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    const char *cmd = argv[1];

    for (int i = 0; i < command_count; i++) {
        if (strcmp(cmd, commands[i].name) == 0) {
            if (commands[i].needs_arg && argc < 3) {
                printf("Error: '%s' requires an argument.\n", cmd);
                return 1;
            }

            commands[i].func(commands[i].needs_arg ? argv[2] : NULL);
            return 0;
        }
    }

    printf("Unknown command: %s\n", cmd);
    print_usage();
    return 1;
}
