#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "json_utils.h"
#include "game_script.h"

#define FILENAME "../data/game_script.json"

char* load_game_title()
{
    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_title = cJSON_GetObjectItemCaseSensitive(json_file, "title");
    if (cJSON_IsString(json_title) && json_title->valuestring != NULL) 
    {
        return json_title->valuestring;
    }

    cJSON_Delete(json_file);

    return NULL;
}

char* load_game_openning_script()
{
    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_story = cJSON_GetObjectItemCaseSensitive(json_file, "story");
    cJSON *json_story_item = cJSON_GetArrayItem(json_story, 0);
    cJSON *json_story_item_content = cJSON_GetObjectItemCaseSensitive(json_story_item, "content");
    if (cJSON_IsString(json_story_item_content) && json_story_item_content->valuestring != NULL)
    {
        return json_story_item_content->valuestring;
    }

    cJSON_Delete(json_file);

    return NULL;
}