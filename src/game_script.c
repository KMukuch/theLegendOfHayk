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
    int total_len;

    cJSON *json_file = load_json_file(FILENAME);
    if (!json_file) return NULL;

    cJSON *json_name = cJSON_GetObjectItemCaseSensitive(json_file, "name");
    cJSON *json_author = cJSON_GetObjectItemCaseSensitive(json_file, "author");
    cJSON *json_version = cJSON_GetObjectItemCaseSensitive(json_file, "version");
    cJSON *json_date = cJSON_GetObjectItemCaseSensitive(json_file, "date");

    if (!cJSON_IsString(json_name) || !cJSON_IsString(json_author) || !cJSON_IsString(json_version) || !cJSON_IsString(json_date))
    {
        cJSON_Delete(json_file);
        return NULL;
    }
    const char *format = "%s by %s, version %s, %s";
    total_len = snprintf(NULL, 0, format, json_name->valuestring, json_author->valuestring, json_version->valuestring, json_date->valuestring) + 1;
    char *title = malloc(total_len);
    if (!title) {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json_file);
        return NULL;
    }

    snprintf(title, total_len, format, json_name->valuestring, json_author->valuestring, json_version->valuestring, json_date->valuestring);

    cJSON_Delete(json_file);

    return title;
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