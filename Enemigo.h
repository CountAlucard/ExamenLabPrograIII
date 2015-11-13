#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Personaje.h"
#include "Jugador.h"
#include <stdlib.h>
#include <list>

class Jugador;

class Enemigo : public Personaje
{
    public:
        Jugador* jugador;
        Enemigo();
        virtual ~Enemigo();
        virtual void logica()=0;
    protected:
    private:
};

#endif // ENEMIGO_H
