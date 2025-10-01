#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

cJSON* load_json_file(const char *filename);

#endif