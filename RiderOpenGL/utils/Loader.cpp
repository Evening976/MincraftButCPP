#include "loader.h"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>

char* read_file(const char* filename)
{
    FILE* in = fopen(filename, "rb");
    if (in == NULL) throw std::runtime_error("file does not exists");

    int res_size = BUFSIZ;
    auto res = (char*)malloc(res_size);
    int nb_read_total = 0;

    while (!feof(in) && !ferror(in))
    {
        if (nb_read_total + BUFSIZ > res_size)
        {
            if (res_size > 10 * 1024 * 1024) break;
            res_size = res_size * 2;
            res = (char*)realloc(res, res_size);
        }
        char* p_res = res + nb_read_total;
        nb_read_total += fread(p_res, 1, BUFSIZ, in);
    }

    fclose(in);
    res = (char*)realloc(res, static_cast<size_t>(nb_read_total) + 1);
    res[nb_read_total] = '\0';
    return res;
}
