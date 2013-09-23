#include "StandardCubeSmoother.h"

void StandardCubeSmoother::Smooth(UberCube* cube)
{
    for(int i=0; i < mSmoothIterations; ++i)
    {
        mPolisher.PolishCube(cube);
    }
}