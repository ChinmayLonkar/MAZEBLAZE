#include "line_following.h"
#include "lsa.h"

position_t position()
{
    position_t sum;
    sum.pos = (5) * read_lsa().lsa_read[0] + (3) * read_lsa().lsa_read[2] + (1) * read_lsa().lsa_read[1] + (-1) * read_lsa().lsa_read[4] + (-3) * read_lsa().lsa_read[3];
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