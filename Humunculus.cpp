#include "Humunculus.h"

Humunculus::Humunculus(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Enemigo";
    this->renderer = renderer;
    this->jugador = jugador;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Enemigo/gdown1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Enemigo/gdown2.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Enemigo/gup1.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Enemigo/gup2.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Enemigo/gleft1.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Enemigo/gleft2.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Enemigo/gright1.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Enemigo/gright2.png"));

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

Humunculus::~Humunculus()
{
    //dtor
}

void Humunculus::logica()
{
    if(jugador->y+10<y)
    {
        state="up";
    }
    if(jugador->y-10>y)
    {
        state="down";
    }

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

