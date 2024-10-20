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
- [Perspectives](#perspectives)

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

   Here is an example GCC compilation command for Windows with SDL installed via Cygwin:

   ```bash
   gcc -I "C:\Path\To\SDL2\include" \
       src\*.c \
       src\components\*.c \
       src\managers\*.c \
       -o build\main.exe \
       -lSDL2 \
       -lSDL2_image \
       -Wall \
       -g
    ```
    Feel free to modify this command according to your project’s needs. If you have different configurations or setups, you may need to adjust the command accordingly. The use of * wildcard instead of complete source files names is for convenience only and not fit for production.

### Running the Program
To run the Program, place yourself in the built Program file and execute the following command:
    ```
    ./main
    ```

## Usage
The engine's main loop manages events, updates game logic, and calls functions from the modules. You can add your game-specific logic by modifying or extending the provided functions:

- handle_input(SDL_Event e, Player *player, int *quit, SDL_Window *win, SDL_Renderer *ren): Handles user input.
- update(Player *player, Entity *entities[], int entity_count, float delta_time): Updates the player and entities and account for framerate variations.
- render_textures(SDL_Renderer* ren, Background *background, Player *player, Entity *entities[]): Renders game elements.

## File Structure

```bash
/C-Game-Engine
│
├── /src/                  # Source files
│   ├── /components/       # Components c files
│   ├── /managers/         # System c files
│   ├── config.json        # Main engine configuration file
│   └── main.c             # Entry point for the engine
│
├── /build/                # Built files
│   ├── main               # Built executable
│   └── /tests/            # Automatic built tests
│
├── /assets/               # Game assets like images, audio...
│
├── /docs/                 # Documentation files
│   └── /html/             # Back-end API documentation
│
├── /tests/                # Unit tests
│
├── TODO.md                # TODO list
├── README.md              # Readme file
└── LICENSE                # License file
```

## Naming Conventions

In order to maintain consistency and readability in the codebase, the following naming conventions are followed:

- **File Names**: We use **snake_case** for file names to enhance clarity.  
  *Example*: `resource_manager.c`, `scene_manager.h`

- **Types (Structs and Classes)**: We use **PascalCase** for naming types such as structs and classes.  
  *Example*: `ColliderComponent`, `TransformComponent`

- **Constants**: We use **UPPER_SNAKE_CASE** for constants to distinguish them easily.  
  *Example*: `SCREEN_WIDTH`, `CONFIG_PATH`

- **Functions and Variables**: We use **snake_case** for naming functions and variables, ensuring that they are descriptive and clear.  
  *Example*: `load_resources()`, `delta_time`

Following these conventions will help us write clean, maintainable code that is easy to navigate and understand.


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

## Perspectives
- **Migrating to C++**: Perspectives of evolutions include transitionning to C++ (for now, I am merely using C for learning purposes). For this reason, the current C codebase is structured with the potential for future migration to C++ in mind, making the transition smoother if and when it happens.
- **Supporting higher levels of abstraction**: Once the C backend reaches a sufficient level of maturity, the project aims to implement bindings for higher-level languages such as Python, allowing scripting capabilities. Additionally, there are plans to explore the possibility of introducing a visual development interface, making the engine accessible to users who prefer event-driven or GUI-based design.