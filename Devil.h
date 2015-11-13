#ifndef DEVIL_H
#define DEVIL_H
#include "Enemigo.h"

class Devil : public Enemigo
{
    public:
        Devil(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Devil();
        void logica();
    protected:
    private:
};

#endif // DEVIL_H
