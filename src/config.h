#ifndef CONFIG_H
#define CONFIG_H

// Screen dimensions
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// Character dimensions
extern const int CHARACTER_WIDTH;
extern const int CHARACTER_HEIGHT;

// Character starting position
extern const int CHARACTER_STARTING_X;
extern const int CHARACTER_STARTING_Y;

// Maximum entity number allowed
extern const int MAX_ENTITIES;

// Configuration JSON file path
extern const char* CONFIG_PATH;

// Timeout for CI/CD game termination
extern const int GAME_TIMEOUT_SECONDS;

#endif