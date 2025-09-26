#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define UNIT_HOUR 1.0f
#define DISTANCE_TO_HOUR 1.0f
#define ACTION_TO_HOUR (1.0f/6.0f)

float convert_distance_to_hour(const float *distance);
float convert_action_to_hour(const float *action);
float convert_hour_to_distance(const float *hour);
float convert_hour_to_action(const float *hour);

#endif