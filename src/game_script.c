#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"
#include "json_utils.h"
#include "game_script.h"

#define FILENAME "../data/game_script.json"

struct Game_Script_Manager create_game_script_manager()
{
    struct Game_Script_Manager game_script_manager;

    game_script_manager.current_script_id = 0;
    game_script_manager.script_read_flag = false;

    return game_script_manager;
}

void advance_game_script(struct Game_Script_Manager *game_script_manager)
{
    if(game_script_manager->script_read_flag)
    {
        game_script_manager->current_script_id++;
        game_script_manager->script_read_flag = false;
    }
}

void run_game_script_manager(struct Game_Script_Manager *game_script_manager)
{
    char *script_content = load_game_script(game_script_manager->current_script_id);
    if (script_content != NULL)
    {
        printf("%s\n", script_content);
        game_script_manager->script_read_flag = true;
        advance_game_script(game_script_manager);
        free_script_content(script_content);
    }
}

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

char* load_game_script(const int id)
{
    bool script_flag = false;

    char *content = NULL;

    cJSON *json_file = load_json_file(FILENAME);
    cJSON *json_script = cJSON_GetObjectItemCaseSensitive(json_file, "script");
    cJSON *json_script_item = NULL;

    cJSON_ArrayForEach(json_script_item, json_script)
    {
        cJSON *json_script_item_id = cJSON_GetObjectItemCaseSensitive(json_script_item, "id");
        if(cJSON_IsNumber(json_script_item_id) && !script_flag)
        {
            if(json_script_item_id->valueint == id)
            {
                script_flag = true;
                cJSON *json_script_item_content = cJSON_GetObjectItemCaseSensitive(json_script_item, "content");
                if (cJSON_IsString(json_script_item_content) && json_script_item_content->valuestring != NULL)
                {
                    int script_content_size = strlen(json_script_item_content->valuestring);
                    content = malloc(script_content_size + 1);
                    if (!content)
                    {
                        fprintf(stderr, "Memory allocation failed\n");
                        cJSON_Delete(json_file);
                        return NULL;
                    }
                    strcpy(content, json_script_item_content->valuestring);
                }
            }
        }
    }

    cJSON_Delete(json_file);

    return content;
}

void free_script_content(char *script_content)
{
    free(script_content);
}