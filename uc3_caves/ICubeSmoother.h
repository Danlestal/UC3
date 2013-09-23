#ifndef ICUBESMOOTHER_H
#define ICUBESMOOTHER_H

#include "UberCube.h"

class ICubeSmoother
{
    public:
    virtual void Smooth(UberCube* cubeToSmooth) = 0;
};
#endif