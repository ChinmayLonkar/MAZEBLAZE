#ifndef LINE_FOLLOWING_H
#define LINE_FOLLOWING_H

#include "mazeblaze.h"

typedef struct position_t
{
    int pos;
} position_t;

position_t position();

float bound(float val, float min, float max);

#endif