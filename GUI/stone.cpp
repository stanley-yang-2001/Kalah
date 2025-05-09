#include "stone.h"


// stone used in a pit
Stone::Stone(int x, int y): posX(x), posY(y)
{
    setRect(x,y,20,20);
}
