#ifndef JUGADOR_H
#define JUGADOR_H

#include <list>
#include <fstream>
#include "Personaje.h"
#include "Proyectil.h"

class Jugador : public Personaje
{
    public:
        Jugador(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Jugador();
        void logica();
        void set_x(double x);
        void set_y(double y);
        void clean_up(Jugador &thisJugador);
        double get_x();
        double get_y();
        string get_state();
    protected:
    private:
};

#endif // JUGADOR_H
