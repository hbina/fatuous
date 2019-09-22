# Fatuous

Demo : https://www.youtube.com/watch?v=BbLW4ZJnaLM

This project was supposed to be a simple calculator.
Somehow, it became a freak-of-nature ala Frankenstein of an attempt at making a 3d engine.
My current goal is to be able to implement all types of rendering techniques (mostly lighting, shadows, etc etc).

After that, I might implement other stuff like physics, animation, sounds, scripts etc. etc. to make it a proper game engine.

Regardless, I like `LateX`, so here is a more robust text about the project : [Fatuous Book](documentation/akarin_engine.tex)

# Installation

## Obtain the Source Code

First, clone the project

`git clone git@github.com:hbina/akarin_engine.git`

Then - after entering the directory - you want to initialize the submodules:

`git submodule init` then `git submodule update`.

## Prerequisite

### Linux

Before installing, you will need the following packages.

`sudo apt-get install cmake build-essential make xorg-dev libglu1-mesa-dev libc6-dbg gdb valgrind`

### Windows

AFAIK, all you need to install is probably the latest driver for your GPU.

## Compile

First, let `cmake` generate the build files.

`cd build` then `cmake ..`

Then, you compile.

`cmake --build . --config Debug --target akarin_engine -j 4`
