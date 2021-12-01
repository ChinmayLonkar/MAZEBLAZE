#include "node_detection.h"

bool only_straight()
{
    if (position().pos < 500 && position().pos > -300) // OnlyStraight
    {
        return true;
    }
    return false;
}

bool only_left()
{
    if (position().pos == 500) // OnlyLeft
    {
        return true;
    }
    return false;
}

bool only_right()
{
    if (position().pos == -300) // OnlyRight
    {
        return true;
    }
    return false;
}

bool plus_node()
{
    if (position().pos == 300) // Plus
    {
        return true;
    }
    return false;
}

bool T_node()
{
    if (position().pos == 200) // T
    {
        return true;
    }
    return false;
}

bool straight_right()
{
    if (position().pos == -200) // StraightRight
    {
        return true;
    }
    return false;
}

bool straight_left()
{
    if (position().pos == 600) // StraightLeft
    {
        return true;
    }
    return false;
}

bool deadend()
{
    if (position().pos == 0) // DeadEnd
    {
        return true;
    }
    return false;
}

bool end()
{
    if (read_lsa().lsa_read[0] == 100 && read_lsa().lsa_read[2] == 100 && read_lsa().lsa_read[1] == 100 && read_lsa().lsa_read[4] == 100 && read_lsa().lsa_read[3] == 100)
    {
        return true;
    }
    return false;
}