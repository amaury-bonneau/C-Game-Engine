#include "config.h"

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Character dimensions
const int CHARACTER_WIDTH = 50;
const int CHARACTER_HEIGHT = 50;

// Character starting position
const int CHARACTER_STARTING_X = SCREEN_WIDTH/2;
const int CHARACTER_STARTING_Y = SCREEN_HEIGHT/2;

// Maximum entity number allowed
const int MAX_ENTITIES = 100;

// Configuration JSON file path
const char* CONFIG_PATH = "./config.json";

// Timeout for CI/CD game termination
const int GAME_TIMEOUT_SECONDS = 60;