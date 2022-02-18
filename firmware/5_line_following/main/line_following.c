#include "line_following.h"


position_t position()
{
    position_t sum;
    sum.pos = (1) * read_lsa().data[0]/* + (2) * read_lsa().data[1] */+ (3) * read_lsa().data[2]/* + (4) * read_lsa().data[3]*/ + (5) * read_lsa().data[4];
    return sum;
}

float bound(float val, float min, float max)
{
    if (val > max)
        val = max;
    else if (val < min)
        val = min;
    return val;
}