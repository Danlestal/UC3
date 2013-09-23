#ifndef STANDARDCUBESMOOTHER_H
#define STANDARDCUBESMOOTHER_H

#include "ICubeSmoother.h"
#include "CubePolisher.h"
class StandardCubeSmoother : public ICubeSmoother
{
    private:
    CubePolisher mPolisher;
    int mSmoothIterations;

    public:
    StandardCubeSmoother(int smoothIterations) : mPolisher(CubePolisher()), mSmoothIterations(smoothIterations)
    {}

    void Smooth(UberCube* cubeToSmooth);
};
#endif
