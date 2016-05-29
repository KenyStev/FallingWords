Rosalila Demo
=============
rosalilastudio.com

Build instructions using Code::Blocks:

1. Install the dependencies
---------------------------
* apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev freeglut3-dev
* TODO port to SDL2: yum install SDL-devel SDL_mixer-devel SDL_image-devel SDL_ttf-devel freeglut-devel 

2. Link the libraries
---------------------
In Code::Blocks: "Linker settings" -> "Other linker options"
Add the following:
*   lGL
*   lglut
*   lGLU
*   lSDL2
*   lSDL2_image
*   lSDL2_ttf
*   lSDL2_mixer
