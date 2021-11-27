#include "line_following.h"
#include "lsa.h"

position_t position()
{
    position_t sum;
    sum.pos = (5) * get_reading_lsa().lsa_reading[0] + (3) * get_reading_lsa().lsa_reading[2] + (1) * get_reading_lsa().lsa_reading[1] + (-1) * get_reading_lsa().lsa_reading[4] + (-3) * get_reading_lsa().lsa_reading[3];
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