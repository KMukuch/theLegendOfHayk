#ifndef JSON_UTILS.H
#define JSON_UTILS.H

#include <stdio.h>
#include <cjson/cJSON.h>
#include "config.h"

cJSON* load_json_file(const char *filename);

#endif