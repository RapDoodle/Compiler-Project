#include "utils.h"

int fpeek(FILE* const fp)
{
    const int c = getc(fp);
    return c == EOF ? EOF : ungetc(c, fp);
}