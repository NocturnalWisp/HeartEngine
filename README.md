# Heart Engine
Heart Engine is a Lua scripted engine built on C++. Heart Engine is inspired by Love2D and Godot. There are a few key standards that the engine intends to adhere to.

## Standards
1. Inheritance can be messy for games. The engine is built on certain inheritance abstractions, but lua scripts are intent on composition.
2. Heart engine is completely modular. It will not really on any implementation besides sol3 (Lua bindings). Raylib is offered as the base, but can be interchanged.
3. Object communication is mainly done through events. One node should not see the components of another node.
4. Game assets are easily obfuscated into binary files. Lua scripts and other resources should not be accessable by the player.
5. Simplified build system offered through python scripts. Easy to create, easy to use.

## Binary
The binary build of the engine is offered in a seperate repository which also provides a C++ template in case you want to develop modules or have more control over your project.

[https://github.com/NocturnalWisp/HeartEngineBinary](https://github.com/NocturnalWisp/HeartEngineBinary)

## Building From Source
Heart Engine uses CMake's robust FetchContent system. It allows for quickly downloading and building external libraries.

You will need CMake (3.5+), Python (3). You will not need lua as it is one of the external libraries built during the CMake configure process.

### CMake Variables
