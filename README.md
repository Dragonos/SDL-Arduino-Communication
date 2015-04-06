
# Communication between SDL and Arduino


This repository contains a demonstration of how we can establish communication between the SDL library and the Arduino boad. The PlaneGame folder contains two versions of the game and the sketsh that should be uploaded to the Arduino board.


## How to build

### Linux

First of all, the SDL 1.2 library and the SDL_image 1.2 library should be installed :

    $ sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev

Then, clone the libserialport repository and build it :

    $ sudo apt-get install git-core gcc make autoconf automake libtool
    $ git clone https://github.com/martinling/libserialport.git
    $ cd libserialport
    $ ./autogen.sh
    $ ./configure
    $ make
    $ sudo make install

Finaly, clone this repository and build it :

    $ git clone https://github.com/Dragonos/SDL-Arduino-Communication.git
    $ cd PlaneGame/PlaneGame-without-Arduino-Direction-Control
    $ make
    $ ./PlaneGame

**Do not forget to change the SERIAL_PORT constant in the "PlaneGame/PlaneGame-with-Arduino-Direction-Control/main.c" file with the Arduino serial port address.**

If you get an error like this : *Cannot open shared object file: No such file or directory* :

    $ sudo ldconfig /usr/local/lib


### Windows

A simple way to make the demo work is to create a new SDL project in Code::Blocks, add the main.c and the libserialport.h files to that project, add the SDL_image.lib and the libserialport.a files to the linker and copy the libserialport.dll file and all SDL necessary DLLs to the source folder.
Do not forget to change the SERIAL_PORT constant in the "main.c" file with the Arduino serial port address (COMx).


## Licence

This demonstration (PlaneGame) is licensed under the MIT License except the following files :

* PlaneGame/data/Water.jpg : rules of use at [simplybackgrounds.deviantart.com](http://simplybackgrounds.deviantart.com/art/Water-Texture-49283686)

* PlaneGame/data/Plane.png license : Personal and Non commercial use only, redistribute is forbidden. [all-free-download.com](http://all-free-download.com/free-vector/vector-misc/plane_311452.html)


