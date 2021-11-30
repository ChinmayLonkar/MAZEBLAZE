
#ifndef TURN_H
#define TURN_H

#include "mazeblaze.h"
#include "line_following.h"
#include "tuning_http_server.h"

#define RIGHT 100
#define LEFT 101
#define UTURN 102

void turn(int direction);
void stop();
void go_straight();

#endif
