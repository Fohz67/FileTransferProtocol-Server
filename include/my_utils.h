/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_utils.h
*/

#ifndef MY_UTILS_H
    #define MY_UTILS_H

    #include <stdbool.h>

// Print
int output_error(const char *);
void *output_null_error(const char *);
int output_helper(void);

// Lib
size_t count_char(const char *, char);
bool is_dir(const char *);
size_t str_length(const char *);
size_t array_length(void *);
char *concat_strings(const char *, const char *);

// Get args
in_port_t get_port(const char **);
char *get_path(const char **);

#endif
