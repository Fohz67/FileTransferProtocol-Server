/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** signal.c
*/

#include "my_ftp.h"
#include "my_signal.h"
#include "my_utils.h"

static const char SIGACTION_ERROR[] = "Sigaction error.";

sig_atomic_t *get_signal_flag_ptr(void)
{
    static sig_atomic_t signal_flag = 0;

    return &signal_flag;
}

static void signal_received(int signal)
{
    if (signal == SIGINT) {
        *get_signal_flag_ptr() = 1;
    }
}

int exit_signal(void)
{
    struct sigaction action = {0};

    action.sa_handler = signal_received;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGINT, &action, NULL) < SUCCESS) {
        return output_error(SIGACTION_ERROR);
    }
    return SUCCESS;
}
