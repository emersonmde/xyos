#ifndef _SH_H
#define _SH_H 1

#include <stdbool.h>
#include <stddef.h>

#define MAX_CMD_BUF_LEN 100
#define MAX_ARG_LEN 100
#define MAX_ARGS 25

// TODO: move to process specific heap allociation
typedef struct {
    char buf[MAX_CMD_BUF_LEN];
    size_t len;
    bool complete;

    // TODO: malloc variable length argument lists
    unsigned int argc;
    char argv[MAX_ARGS][MAX_ARG_LEN];
} sh_cmd_ctx_t;

void reset_sh();
void run_sh();

int sh_process_cmd(sh_cmd_ctx_t *ctx);

#endif
