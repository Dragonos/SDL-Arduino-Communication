
/*

	The MIT License (MIT)

	Copyright (c) 2015 Amine Ben Hassouna (https://github.com/Dragonos)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

*/


#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "arduino.h"

#define SERIAL_PORT "/dev/ttyACM0"



#define SERIAL_PORT_BUFFER_LENGTH   20
#define PLANE_STEPS   5

int strStartsWith(const char *pre, const char *str);
void move(SDL_Surface *screen, SDL_Surface *plane, SDL_Rect *planePosition, SDLKey direction);

int main(int argc, char* argv[])
{
    // SDL variables
    SDL_Surface *screen, *dragonos, *background, *plane;
    SDL_Rect dragonosPosition, backgroundPosition, planePosition;

    char serialPortBuffer[SERIAL_PORT_BUFFER_LENGTH] = {0};
    int serialPortReadDataLength = 0;

    // Connect to the Arduino board via the serial port with Baudrate = 9600
    if(!Arduino_connect(SERIAL_PORT, 9600))
        exit(EXIT_FAILURE);

    // Initialize the SDL lib
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "SDL initialization error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    // Setup the the main window
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL)
    {
        fprintf(stderr, "SDL screen load error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Communication between SDL and Arduino", NULL);

    SDL_EnableKeyRepeat(10, 10);

    // Load images
    dragonos = IMG_Load("data/Dragonos.png");
    background = IMG_Load("data/Water.jpg");
    plane = IMG_Load("data/Plane.png");

    // Set the images initial positions
    dragonosPosition.x = 10;
    dragonosPosition.y = 10;

    backgroundPosition.x = 0;
    backgroundPosition.y = background->h - 600;
    backgroundPosition.h = 600;
    backgroundPosition.w = background->w;

    planePosition.x = screen->w/2 - plane->w/2;
    planePosition.y = screen->h - plane->h - 20;


    int quit = 0;
    SDL_Event event;

    while(!quit)
    {
        // Check for SDL events
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    // Move the plane
                    move(screen, plane, &planePosition, event.key.keysym.sym);
                    break;
                }
                break;
            }
        }

        // Read from Arduino via serial port
        serialPortReadDataLength = Arduino_read(serialPortBuffer, SERIAL_PORT_BUFFER_LENGTH);
        serialPortBuffer[serialPortReadDataLength] = 0;

        if(serialPortReadDataLength > 0)
        {
            if(strStartsWith("up", serialPortBuffer))
            {
                move(screen, plane, &planePosition, SDLK_UP);
            }
            else if(strStartsWith("down", serialPortBuffer))
            {
                move(screen, plane, &planePosition, SDLK_DOWN);
            }
            else if(strStartsWith("right", serialPortBuffer))
            {
                move(screen, plane, &planePosition, SDLK_RIGHT);
            }
            else if(strStartsWith("left", serialPortBuffer))
            {
                move(screen, plane, &planePosition, SDLK_LEFT);
            }
        }

        // Send Notifications to the Arduino via serial port
        if(planePosition.x == 0)
            Arduino_write("Border Left\n", 12);
        else if(planePosition.x == 800 - plane->w)
            Arduino_write("Border Right\n", 13);
        else if(planePosition.y == 0)
            Arduino_write("Border Top\n", 11);
        else if(planePosition.y == 600 - plane->h)
            Arduino_write("Border Bottom\n", 14);

        // Update the sea position

        backgroundPosition.y -= 3;
        if(backgroundPosition.y == 0)
            backgroundPosition.y = background->h - 600;

        // Update the screen
        SDL_BlitSurface(background, &backgroundPosition, screen, NULL);
        SDL_BlitSurface(plane, NULL, screen, &planePosition);
        SDL_BlitSurface(dragonos, NULL, screen, &dragonosPosition);
        SDL_Flip(screen);



        SDL_Delay(10);
    }

    SDL_FreeSurface(background);
    SDL_FreeSurface(dragonos);
    SDL_FreeSurface(plane);

    SDL_Quit();

    // Close Arduino connection
    Arduino_disconnect();

    return EXIT_SUCCESS;
}

void move(SDL_Surface *screen, SDL_Surface *plane, SDL_Rect *planePosition, SDLKey direction)
{
    switch(direction)
    {
    case SDLK_UP:
        planePosition->y -= PLANE_STEPS;
        if(planePosition->y <0)
            planePosition->y = 0;
        break;
    case SDLK_DOWN:
        planePosition->y += PLANE_STEPS;
        if(planePosition->y > screen->h - plane->h)
            planePosition->y = screen->h - plane->h;
        break;
    case SDLK_RIGHT:
        planePosition->x += PLANE_STEPS;
        if(planePosition->x > screen->w - plane->w)
            planePosition->x = screen->w - plane->w;
        break;
    case SDLK_LEFT:
        planePosition->x -= PLANE_STEPS;
        if(planePosition->x <0)
            planePosition->x = 0;
        break;
    }
}

int strStartsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

