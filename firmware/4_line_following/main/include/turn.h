
#ifndef TURN_H
#define TURN_H

#include "mazeblaze.h"
#include "line_following.h"
#include "tuning_http_server.h"

#define RIGHT 1
#define LEFT 2
#define UTURN 3

void turn(int direction);
void stop();
void go_straight();

#endif
