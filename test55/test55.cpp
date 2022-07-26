// test5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_thread.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>

#include "Program.h"

void initGL()
{
    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLenum err = glewInit();

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void sdl_init(char const* title, int width, int height, SDL_Window** pwindow, SDL_Renderer** prenderer, SDL_GLContext* gcontext)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL wont start SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("No Renderer: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    *gcontext = SDL_GL_CreateContext(window);
    *pwindow = window;

    //Initialize OpenGL
    initGL();
  
    //*prenderer = renderer;
}


Uint32 drawTimer(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;  
}

Uint32 logicTimer(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT + 1;
    SDL_PushEvent(&ev);
    return ms;  
}

Uint32 lightTimer(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT + 2;
    SDL_PushEvent(&ev);
    return ms;
}

int main(int argc, char* argv[])
{
    srand(time(0));

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext gcontext;
    int ww = 1024;
    int wh = 768;
    sdl_init("test5", ww, wh, &window, &renderer,&gcontext);

   
    SDL_TimerID id1 = SDL_AddTimer(16, drawTimer, NULL);
    SDL_TimerID id2 = SDL_AddTimer(8, logicTimer, NULL);
    SDL_TimerID id3 = SDL_AddTimer(36, lightTimer, NULL);

    bool quit = false;
    bool console = false;
    InputHandler ih = InputHandler();
    Program program = Program(&gcontext,&ih);
    

    while (!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
           
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                ih.buttonPressed(0, false);
                break;

            case SDLK_RIGHT:
                ih.buttonPressed(1, false);
                break;

            case SDLK_UP:
                ih.buttonPressed(2, false);
                break;

            case SDLK_DOWN:
                ih.buttonPressed(3, false);
                break;

            case SDLK_RETURN:
                ih.buttonPressed(4, false);
            break;

            case SDLK_ESCAPE:
                ih.buttonPressed(5, false);
            break;

            case SDLK_a:
                ih.buttonPressed(6, false);
                break;

            case SDLK_d:
                ih.buttonPressed(7, false);
                break;

            case SDLK_w:
                ih.buttonPressed(8, false);
                break;

            case SDLK_s:
                ih.buttonPressed(9, false);
                break;

            case SDLK_r:
                ih.buttonPressed(10, false);
                break;

            case SDLK_f:
                ih.buttonPressed(11, false);
                break;
            }
        break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                ih.buttonPressed(0, true);
                break;

            case SDLK_RIGHT:
               ih.buttonPressed(1, true);
                break;

            case SDLK_UP:
               ih.buttonPressed(2, true);
                break;

            case SDLK_DOWN:
               ih.buttonPressed(3, true);
                break;

            case SDLK_RETURN:
                ih.buttonPressed(4, true);
                break;

            case SDLK_ESCAPE:
                ih.buttonPressed(5, true);
                break;

            case SDLK_a:
                ih.buttonPressed(6, true);
                break;

            case SDLK_d:
                ih.buttonPressed(7, true);
                break;

            case SDLK_w:
                ih.buttonPressed(8, true);
                break;

            case SDLK_s:
                ih.buttonPressed(9, true);
                break;

            case SDLK_r:
                ih.buttonPressed(10, true);
                break;

            case SDLK_f:
                ih.buttonPressed(11, true);
                break;
            }

        break;

        
        case SDL_USEREVENT:
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            program.drawCycle();
            SDL_GL_SwapWindow(window);
        break;

        case SDL_USEREVENT + 1:
            program.actionLoop();
        break;

        case SDL_USEREVENT + 2:
            program.lightUpdate();
        break;

        }
       
       // SDL_RenderPresent(renderer);
    }
    SDL_RemoveTimer(id1);
    SDL_RemoveTimer(id2);

    SDL_Quit();

    return 0;
}

