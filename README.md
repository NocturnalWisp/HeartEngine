# Lua scripted game engine built on raylib C++

The engine is inspired by Love2D and Godot. Debated on calling it Love3D, but the engine is functionally quite different and needed it's own name.

Currently in infancy, but has a rebust module system for easily expanding functionality!

Heart Engine is a game engine built on raylib C++. My main goals with the engine are as follows:
1. Simple game objects with no inheritance trees. (All objects have components and are forced to be their own scenes like Godot. Interactions between nodes (aka scenes) are handled via event systems.)
2. Simple Lua scripting.
3. Module engine parts. (All non-core engine is built out in modules/ to keep everything clean and interchangable.)
4. Raylib is not a requirement. (Interchange raylib with any other C++ game library (Ex. Ogre3D, SDL, SFML) using modules.)
5. Obfuscated game assets. (Assets are stored in a binary file and not directly accessable when built for production.)
6. Simple (and easy to use) python scripts for build systems and tools.
7. Easy CMake build system. (Heart Engine aims to make it easy to call certain CMake scripts to do the heavy lifting. No need for complex or annoying manual Fetching.)

Current goals:
- Create a functioning game with working game loop.
