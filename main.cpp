#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<fstream>
#include<string>
#include<SDL2/SDL_mixer.h>

#include "Jugador.h"
#include "Enemigo.h"
#include "Proyectil.h"
#include "Humunculus.h"
#include "Skeleton.h"
#include "Devil.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character, *menu, *menuNew, *menuExit;
SDL_Rect rect_background,rect_character;
Mix_Music *gMusic = NULL;
Mix_Chunk *gMedium = NULL, *menu_Click = NULL;
int Mx = 0;
int My = 0;
void loop_Menu();
void loop_Game();

using namespace std;

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init Music
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return 40;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    menu = IMG_LoadTexture(renderer, "menu.png");
    menuNew = IMG_LoadTexture(renderer, "menuNew.png");
    menuExit = IMG_LoadTexture(renderer, "menuExit.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    loop_Menu();

    return 0;

}

void loop_Menu()
{
    SDL_RenderCopy(renderer, menu, NULL, &rect_background);

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            menu_Click = Mix_LoadWAV("select_Click.wav");
            if(Event.type == SDL_QUIT)
                exit(0);
            if(Event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x ,&y);
                cout<<x<<","<<y<<endl;
                if(x>156 && x<353 && y>106 && y< 129)
                {
                    Mix_PlayChannel(-1, menu_Click, 0);
                    SDL_RenderCopy(renderer, menuNew, NULL, &rect_background);
                }

                else if(x>203 && x<277 && y>172 && y<199)
                {
                    Mix_PlayChannel(-1, menu_Click, 0);
                    SDL_RenderCopy(renderer, menuExit, NULL, &rect_background);
                }
                else
                    SDL_RenderCopy(renderer, menu, NULL, &rect_background);
            }

            if(Event.type == SDL_MOUSEBUTTONDOWN)
            {
                int click_x, click_y;
                SDL_GetMouseState(&click_x, &click_y);
                cout<<click_x<<","<<click_y<<endl;
                if(click_x>156 && click_x<353 && click_y>106 && click_y< 129)
                    loop_Game();
                else if(click_x>203 && click_x<277 && click_y>172 && click_y<199)
                    exit(0);
            }
        }

        SDL_RenderPresent(renderer);
    }
}


void loop_Game()
{

    double last_frame = 0;

    int g_Timer = SDL_GetTicks();

    list<Entidad*> entidades;
    Jugador *player = new Jugador(&entidades,renderer);
    entidades.push_back(player);
    entidades.push_back(new Humunculus(&entidades,renderer));
    entidades.push_back(new Skeleton(&entidades,renderer));
    entidades.push_back(new Devil(&entidades,renderer));

    //Main Loop
    int p = 0;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            gMusic = Mix_LoadMUS("Most Wanted (Original).wav");
            gMedium = Mix_LoadWAV("enemy_dead_21.wav");

            if(Event.type == SDL_QUIT)
            {
                player->clean_up(*player);
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                switch(Event.key.keysym.sym)
                {
                case SDLK_BACKSPACE:
                    player->clean_up(*player);
                    exit(0);
                    break;

                case SDLK_9:
                    if( Mix_PlayingMusic() == 0)
                    {
                        Mix_PlayMusic(gMusic, -1);
                    }
                    else
                    {
                        if(Mix_PausedMusic() == 1)
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                    break;
                case SDLK_f:
                    Mix_PlayChannel(-1, gMedium, 0);
                    break;

                    break;

                //Funcion de Pausa
                case SDLK_p:
                    if(p==0)
                    {
                        while(p==0)
                        {
                            while(SDL_PollEvent(&Event))
                            {
                                if(Event.type == SDL_QUIT)
                                {
                                    exit(0);
                                }
                                if(Event.type == SDL_KEYDOWN)
                                {
                                    if(Event.key.keysym.sym == SDLK_p)
                                    {
                                        p++;
                                    }
                                }

                            }
                        }
                        p=0;
                    }

                    break;

                case SDLK_0:
                    Mix_HaltMusic();
                    break;
                }
            }
        }

        //SDL_Delay(17-(SDL_GetTicks()-last_frame))
        double diferencia = SDL_GetTicks()-last_frame;
        double ajuste = 17 - diferencia;
        if(ajuste>0)
            SDL_Delay(ajuste);
        last_frame=SDL_GetTicks();

        for(list<Entidad*>::iterator e = entidades.begin();
                e!=entidades.end();
                e++)
            (*e)->logica();

        for(list<Entidad*>::iterator e = entidades.begin();
                e!=entidades.end();
                e++)
        {
            if((*e)->delete_flag)
            {
                entidades.remove(*e);
                break;
            }
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Entidad*>::iterator e = entidades.begin();
                e!=entidades.end();
                e++)
            (*e)->dibujar();

        SDL_RenderPresent(renderer);
    }
}

