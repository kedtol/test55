// test5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <iostream>
#include <time.h>
#include <SDL.h>
#include "Program.h"


void sdl_init(char const* felirat, int szeles, int magas, SDL_Window** pwindow, SDL_Renderer** prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window* window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}


Uint32 rajzIdozit(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Uint32 logikaIdozit(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT + 1;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

int main(int argc, char* argv[])
{
    srand(time(0));

    SDL_Window* window;
    SDL_Renderer* renderer;
    int ww = 1024;
    int wh = 768;
    sdl_init("test5", ww, wh, &window, &renderer);

   
    SDL_TimerID id1 = SDL_AddTimer(30, rajzIdozit, NULL);
    SDL_TimerID id2 = SDL_AddTimer(10, logikaIdozit, NULL);

    bool quit = false;
    bool console = false;
    InputHandler ih = InputHandler();
    Program program = Program(renderer,&ih);
    

    while (!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
       
        int a;
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
            SDL_RenderClear(renderer);
            program.drawCycle();
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderPresent(renderer);
        break;

        case SDL_USEREVENT + 1:

            program.actionLoop();

        break;


        }
       

        
       // SDL_RenderPresent(renderer);
    }
    SDL_RemoveTimer(id1);
    SDL_RemoveTimer(id2);

    SDL_Quit();

    return 0;
}

