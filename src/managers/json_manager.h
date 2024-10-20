#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <json-c/json.h>

typedef struct {
    int32_t value;  // Actual integer value
    int error;      // 0 for success, -1 for error
} IntResult;

char* read_file(const char *filename);
char* get_string_value(struct json_object *jsonObject, const char *key);
IntResult get_int_value(struct json_object *jsonObject, const char *key);
json_bool get_boolean_value(struct json_object *jsonObject, const char *key);
char* get_nested_value(struct json_object *jsonObject, char *keyPath);
json_object* get_json_value_from_key(json_object *jsonObject, char *key);
const char** get_keys_from_json(json_object *jsonObject);

#endif