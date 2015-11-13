#ifndef SKELETON_H
#define SKELETON_H
#include "Enemigo.h"

class Skeleton : public Enemigo
{
    public:
        Skeleton(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Skeleton();
        void logica();
    protected:
    private:
};

#endif // SKELETON_H
