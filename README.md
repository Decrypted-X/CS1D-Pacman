# CS1D Pacman

## Installing the Application

You can download the binaries for Windows, Linux, or macOS in the bin folder of the project and run the game directly
using the binaries. If your machine is unable to run the application, you can try compiling the code yourself to run the
application in the Godot Engine editor.

## Running the project in Godot

You can follow the more generalized, official tutorial
[here](https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html) if you need any
extra help.

To run the project directly in the Godot Engine, you must first download the engine from their
[website](https://godotengine.org/download) and then do the following:

* Follow the official Godot documentation to set up compiling for either
[Windows](https://docs.godotengine.org/en/stable/development/compiling/compiling_for_windows.html),
[Linux](https://docs.godotengine.org/en/stable/development/compiling/compiling_for_x11.html), or
[macOS](https://docs.godotengine.org/en/stable/development/compiling/compiling_for_osx.html).

* Clone this repository with the following command:

    ```
    git clone --recursive https://github.com/Decrypted-X/CS1D-Pacman.git
    ```

* Then compile the godot-cpp bindings with the following commands. Replace ```<platform>``` with windows, linux, or osx
depending on your OS.

    ```
    cd godot-cpp
    scons platform=<platform> generate_bindings=yes target=release
    cd ..
    ```

* Once the godot-cpp bindings are done compiling, you can compile the project with the following commands:

    ```
    cd cs1d_pacman
    scons platform=<platform> target=release
    cd ..
    ```

After the godot-cpp bindings and the project are compiled, you can then run the project in the Godot Engine. You just
run the Godot Engine and import the project by selecting the ```project.godot``` file in the ```cs1d_pacman/project/```
directory. Click the Run button at the top right of the Godot Engine editor to run the game.
