/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** utils
*/

#include "my_zappy.h"

bool str_to_uint16(const char* str, uint16_t* res)
{
    char* end;
    errno = 0;
    intmax_t val = strtoimax(str, &end, 10);
    if (errno == ERANGE || val < 0 || val > UINT16_MAX || end == str ||
        *end != '\0')
        return false;
    *res = (uint16_t) val;
    return true;
}