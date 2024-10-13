# SDL based C Game Engine
[![C/C++ CI](https://github.com/amaury-bonneau/C-Game-Engine/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/amaury-bonneau/C-Game-Engine/actions/workflows/c-cpp.yml)
![Coverage](https://img.shields.io/codecov/c/github/username/repo.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-0.x.x-blue.svg)


## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Running the Game](#running-the-game)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction
This project is a simple game engine built using the Simple DirectMedia Layer (SDL) library. It serves as a foundation for developing 2D games in C, providing functionality for rendering graphics, handling user input, and managing game entities.

## Features
- **Entity Management:** Create and manage game entities with positions and collisions.
- **Resource Management:** Load and unload game assets like textures and backgrounds.
- **Player Movement:** Basic player controls with keyboard input.
- **Collision Detection:** Detect collisions between the player and entities.
- **Background Rendering:** Render a scrolling background to enhance visual appeal.
- **Fullscreen Support:** Toggle between fullscreen and windowed modes.

## Getting Started

### Prerequisites
- [SDL2](https://www.libsdl.org/download-2.0.php) (version 2.0 or higher)
- [SDL_image](https://github.com/libsdl-org/SDL_image) (optional, for image loading)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/sdl-game-engine.git
   cd sdl-game-engine
   ```
2. Make sure SDL2 and SDL_image are installed on your system. You can install them using a package manager or build from source.

3. Compile the project:
    ```bash
    gcc -o game main.c player.c texture.c config.c entity.c collider.c background.c resourceManager.c -lSDL2 -lSDL2_image
    ```
### Running the Game
To run the game, place yourself in the built game file and execute the following command:
    ```bash
    ./game
    ```

## Usage
The engine's main loop manages events, updates game logic, and calls functions from the modules. You can add your game-specific logic by modifying or extending the provided functions:

- handle_input(SDL_Event e, Player *player, int *quit, SDL_Window *win, SDL_Renderer *ren): Handles user input.
- update(Player *player, Entity *entities[], int entityCount, float deltaTime): Updates the player and entities and account for framerate variations.
- render_textures(SDL_Renderer* ren, Background *background, Player *player, Entity *entities[]): Renders game elements.

## File Structure

    ```bash
    /sdl-game-engine
    │
    ├── main.c                # Entry point of the game engine (contains main game loop)
    ├── player.c              # Player functionality
    ├── texture.c             # Texture handling
    ├── config.c              # Configuration settings
    ├── entity.c              # Entity management
    ├── collider.c            # Collision detection
    ├── background.c          # Background rendering
    ├── resourceManager.c     # Resource management (load and unload)
    ├── main.h                # Header file for main functions
    ├── player.h              # Header file for player functions
    ├── texture.h             # Header file for texture functions
    ├── config.h              # Header file for configuration settings
    ├── entity.h              # Header file for entity functions
    ├── collider.h            # Header file for collision functions
    ├── background.h          # Header file for background functions
    ├── resourceManager.h     # Header file for resource management
    └── README.md             # This README file
    ```

## Contributing
Contributions are welcome. Feel free to submit pull requests or open issues to discuss enhancements or bugs.

- Fork the project.
- Create your feature branch: git checkout -b feature/YourFeature.
- Commit your changes: git commit -m 'Add some feature'.
- Push to the branch: git push origin feature/YourFeature.
- Open a pull request.

## License
This project is licensed under the MIT License, allowing for both personal and commercial use. See the LICENSE file for details.

## Acknowledgments
- SDL for the HAL library used as a base for the game engine.
- SDL_image for image loading support.
