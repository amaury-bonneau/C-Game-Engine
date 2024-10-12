#include "jsonManager.h"
#include "stdlib.h"
#include "resourceManager.h"
#include <SDL.h>
#include <json-c/json.h>

#define JSON_ERROR -1

char* read_file(const char *filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("JSON Manager unable to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END); // seeking to the end of the file to get its length
    long length = ftell(file);
    fseek(file, 0, SEEK_SET); // put the reading head back at the begining of the file

    // allocate memory needed for the content of the json file
    char* content = (char*)malloc(length + 1);
    if (content == NULL) {
        perror("JSON Manager unable to allocate memory");
        fclose(file);
        return NULL;
    }
    
    // actually fill the allocated memory with file content
    fread(content, 1, length, file);
    fclose(file);

    content[length] = '\0'; //null terminate our content string

    return content;
}

char* get_string_value(struct json_object *jsonObject, const char *key) {
    struct json_object *valueObject;
    if (json_object_object_get_ex(jsonObject, key, &valueObject)) { //check if key exists and assign value if it does
        return (char*)json_object_get_string(valueObject);
    } else {
        return NULL;
    }
}

IntResult get_int_value(struct json_object *jsonObject, const char *key) {
    struct json_object *valueObject;
    IntResult result = {0,0};

    if (json_object_object_get_ex(jsonObject, key, &valueObject)) { //check if key exists and assign value if it does
        result.value = json_object_get_int(valueObject);
    } else {
        result.error = JSON_ERROR;
    }
    return result;
}

json_bool get_boolean_value(struct json_object *jsonObject, const char *key) {
    struct json_object *valueObject;
    if (json_object_object_get_ex(jsonObject, key, &valueObject)) { //check if key exists and assign value if it does
        return json_object_get_boolean(valueObject);
    } else {
        return JSON_ERROR;
    }
}

char* get_nested_value(struct json_object *jsonObject, char *keyPath) {
    char *token = strtok(keyPath, "/"); // split keyPath into several tokens if needed
    struct json_object *currentObject = jsonObject;

    while (token) {
        struct json_object *nextObject;
        if (json_object_object_get_ex(currentObject, token, &nextObject)) {
            currentObject = nextObject;
        } else {
            return NULL; // Key not found
        }
        token = strtok(NULL, "/");
    }
    return (char*)json_object_get_string(currentObject);
}

json_object* get_json_value_from_key(json_object *jsonObject, char *key) { 
    struct json_object *valueJsonObject; 
    json_object_object_get_ex(jsonObject, key, &valueJsonObject);  // Fetch the value for the given key
    return valueJsonObject;
}

const char** get_keys_from_json(json_object *jsonObject) {
    int numKeys = json_object_object_length(jsonObject);
    if (numKeys == 0) {
        return NULL; // there is no key to return in the json object
    }
    const char** keys = malloc(sizeof(char*) * numKeys);
    if (keys == NULL) {
        perror("JSON Manager unable to allocate memory");
        return NULL;
    }
    
    int i = 0;
    json_object_object_foreach (jsonObject, key, val) {
        keys[i] = (const char*)key;
        i++;
    }
    return keys;
}