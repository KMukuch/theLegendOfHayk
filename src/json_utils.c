#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "config.h"

cJSON* load_json_file(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    char *buffer = malloc(len + 1);
    if (!buffer)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    if (fread(buffer, 1, len, fp) != len)
    {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        fclose(fp);
        return NULL;
    }
    buffer[len] = '\0';
    fclose(fp);

    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (!json)
    {
        fprintf(stderr, "JSON parse error: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    return json;
}