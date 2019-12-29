#include <stdio.h>
#include <string.h>
#include <arch/i386/tty.h>
#include <stdbool.h>

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

void init_sh_cmd_ctx(sh_cmd_ctx_t *ctx) {
    ctx->complete = false;
    ctx->len = 0;
    memset(ctx->buf, '\0', MAX_CMD_BUF_LEN);

    ctx->argc = 0;
    for (unsigned int i = 0; i < MAX_ARGS; i++)
        memset(ctx->argv[i], '\0', MAX_CMD_BUF_LEN);
}

void reset_sh(sh_cmd_ctx_t *ctx) {
    init_sh_cmd_ctx(ctx);
    printf("\n> ");
}

void run_sh() {
    sh_cmd_ctx_t sh_cmd_ctx;
    printf("\nWelcome to XyOS!\n");

    reset_sh(&sh_cmd_ctx);

    for (;;) {
        char c;
        while ((c = stdin_getchar()) != EOF) {
            // TODO: remove char on backspace
            if (c == '\n') {
                sh_cmd_ctx.buf[sh_cmd_ctx.len++] = '\0';
                sh_cmd_ctx.complete = true;
                break;
            }
            if (sh_cmd_ctx.len >= MAX_CMD_BUF_LEN - 1) {
                reset_sh(&sh_cmd_ctx);
                break;
            }
            sh_cmd_ctx.buf[sh_cmd_ctx.len++] = c;
            putchar(c);
        }

        if (sh_cmd_ctx.complete) {
            printf("\n");

            // Process cmd
            sh_process_cmd(&sh_cmd_ctx);

            // Reset terminal
            reset_sh(&sh_cmd_ctx);
        }
    }
}

int sh_split_args(sh_cmd_ctx_t *ctx) {
    // char arg[MAX_ARG_LEN];
    char *arg;
    int arg_len = 0;

    arg = ctx->buf;

    // TODO: remove/ignore redundant spaces
    // if we processed a command, there will be at least 1 entry in argv
    ctx->argc = 0;
    for (size_t i = 0; i < ctx->len; i++) {
        // TODO: check for max arg len
        if (ctx->buf[i] == ' ' || ctx->buf[i] == '\0') {
            if (arg_len < 1)
                continue;
            memcpy(ctx->argv[ctx->argc], arg, arg_len);
            ctx->argv[ctx->argc][arg_len] = '\0';
            ctx->argc++;
            arg = ctx->buf + i + 1;
            arg_len = 0;
        } else {
            arg_len++;
        }
    }

    return 0;
}

int sh_process_cmd(sh_cmd_ctx_t *ctx) {
    if (!ctx->complete || ctx->len < 1)
        return -1;

    sh_split_args(ctx);

    if (ctx->argc < 1)
        return -1;

    if (strcmp(ctx->argv[0], "echo") == 0) {
        for (unsigned int i = 1; i < ctx->argc; i++)
            printf("%s ", ctx->argv[i]);
    }
    return 0;
}
