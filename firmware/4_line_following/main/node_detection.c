#include "node_detection.h"

bool only_straight()
{
    if (position().pos == 3 || (read_lsa().data[1] == 1 && read_lsa().data[1] == 1 && read_lsa().data[0] == 0 && read_lsa().data[4] == 0) || (read_lsa().data[3] == 1 && read_lsa().data[3] == 1 && read_lsa().data[0] == 0 && read_lsa().data[4] == 0)) // OnlyStraight
    {
        return true;
    }
    return false;
}

bool only_left()
{
    if (position().pos == 5) // OnlyLeft
    {
        return true;
    }
    return false;
}

bool only_right()
{
    if (position().pos == 1) // OnlyRight
    {
        return true;
    }
    return false;
}

bool plus_node()
{
    if (position().pos == 9) // Plus
    {
        return true;
    }
    return false;
}

bool T_node()
{
    if (position().pos == 6) // T
    {
        return true;
    }
    return false;
}

bool straight_right()
{
    if (position().pos == 4) // StraightRight
    {
        return true;
    }
    return false;
}

bool straight_left()
{
    if (position().pos == 8) // StraightLeft
    {
        return true;
    }
    return false;
}

bool deadend()
{
    if (read_lsa().data[0] == 0 && read_lsa().data[2] == 0 && read_lsa().data[1] == 0 && read_lsa().data[4] == 0 && read_lsa().data[3] == 0) // DeadEnd
    {
        return true;
    }
    return false;
}

bool end()
{
    if (read_lsa().data[0] == 1 && read_lsa().data[2] == 1 && read_lsa().data[1] == 1 && read_lsa().data[4] == 1 && read_lsa().data[3] == 1)
    {
        return true;
    }
    return false;
}