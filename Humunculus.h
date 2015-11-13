#ifndef HUMUNCULUS_H
#define HUMUNCULUS_H
#include "Enemigo.h"

class Humunculus : public Enemigo
{
    public:
        Humunculus(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Humunculus();
        void logica();
    protected:
    private:
};

#endif // HUMUNCULUS_H
