# Casu Engine

A simple game engine i made as solo developer inspired by Godot Engine in 3 months.

This game engine was developed as a learning project. While it may be functional, it may contain issues or limitations. Use it at your own discretion and risk.

## Feature

- **Visual scene creation and editing** using an intuitive **node-based system**.
- **User-friendly Editor interface**.
- **2D graphics rendering**: supports drawing shapes, textures, text and fragment shader-based **post processing**.
- **Audio playback**: supports background music and sound effects in **WAV, OGG, MP3**, and other formats.
- **Keyboard and mouse input handling**.
- **Basic collision detection**: support layer-mask mechanism.
- **Resource management** for images, sounds, shader, and XML-based configurations.
- **Minimalist game loop**, designed to be **easy to extend and customize**.

# How to Use

- Install Visual Studio 2022 with `Desktop development with C++` workload
- Simply open the `MyGameEngine.sln` file to get started.

## Solution Structure

- **Casu Engine**: Contains all the core code of the game engine. It is built as a library. Users don't need to modify this part unless they want to make deep changes to the engine.
- **Editor**: Contains the code for the visual editor interface. It is also built as a library and usually does not require modifications.
- **Game**: This is where users write their own game logic. Currently, it contains a sample game for demonstration.

## How to Build a Game

To build your own game, create new classes by inheriting from the `Node` class. The main callback functions you can override include:

- `_SerializeToXML()`: Describes how to save the node's data to a file.
- `_DeserializeFromXML()`: Describes how to load data from a file.
- `_ShowInspector()`: Describes how the data is displayed in the editor.
- `_Ready()`: Called when all child nodes are ready.
- `_Update()`: Called every frame to update game logic.
- `_Render()`: Called to render the node.
- `_Destroy()`: Called before the node is destroyed.

> Note: You must use the macro `REGISTER_NODE_CLASS(node_name)` to make the node available in the game engine.

## Running

- To run the editor:
    
    ```cpp
    Editor::GetInstance()->Run();
    ```
    
- To run the game directly:
    
    ```cpp
    MainLoop::GetInstance()->Run();
    ```
    

# Third-Party

This project makes use of the following libraries and tools:

- [**raylib**](https://www.raylib.com/) – A simple and easy-to-use C library for game programming. Used as the main backend.
- [**raylib-cpp**](https://github.com/RobLoach/raylib-cpp) – A C++ wrapper for raylib, used to provide a more object-oriented interface.
- [**Dear ImGui**](https://github.com/ocornut/imgui) – A fast and minimal GUI library used for building the editor interface.
- [**TinyXML-2**](https://github.com/leethomason/tinyxml2) – A lightweight XML parser used for serializing and deserializing node data.
