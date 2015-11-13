#include "Skeleton.h"

Skeleton::Skeleton(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Enemigo";
    this->renderer = renderer;
    this->jugador = jugador;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Enemigo/skdown1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Enemigo/skdown2.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Enemigo/skup1.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Enemigo/skup2.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Enemigo/skleft1.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Enemigo/skleft2.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Enemigo/skright1.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Enemigo/skright2.png"));

    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    x = rand()%100;
    y = rand()%100;
    rect.x=x;
    rect.y=x;

    velocity=0.5;
    animation_velocity=20;

    current_texture=0;

    state="down";

    this->entidades = entidades;

    for(list<Entidad*>::iterator e=entidades->begin();
        e!=entidades->end();
        e++)
    {
        if((*e)->tipo=="Jugador")
        {
            jugador = (Jugador*)*e;
        }
    }
}

Skeleton::~Skeleton()
{
    //dtor
}

void Skeleton::logica()
{

    if(jugador->y+10<y)
    {
        state="up";
    }
    if(jugador->y-10>y)
    {
        state="down";
    }
    if(jugador->x+10<x)
    {
        x-=velocity;
    }
    if(jugador->x-10>x)
        x+=velocity;

    if(state=="up")
    {
        y-=velocity;
    }
    if(state=="down")
    {
        y+=velocity;
    }

    if(frames%animation_velocity==0)
    {
        current_texture++;
        if(current_texture>=textures[state].size())
            current_texture=0;
    }

    frames++;

}
