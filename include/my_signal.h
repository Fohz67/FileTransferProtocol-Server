/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_signal.h
*/

#ifndef MY_SIGNAL_H
    #define MY_SIGNAL_H

    #include <signal.h>

// Handle signal to stop the server properly
sig_atomic_t *get_signal_flag_ptr(void);
int exit_signal(void);

#endif
