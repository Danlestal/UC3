#include "SquareDensityBrush.h"

SquareDensityCubeBrush::SquareDensityCubeBrush(int brushSize)
{
    _brushSize = brushSize;
}

void SquareDensityCubeBrush::UpdateDensityCube(UberCube* cube,  int x, int y, int z)
{
    cube->mDensityCube[x][y][z] = true;

    for(int i=0; i < _brushSize / 2; ++i)
    {
        cube->mDensityCube[cube->NormalizeCoordinate(x + i)][y][z] = true;
        cube->mDensityCube[cube->NormalizeCoordinate(x - i)][y][z] = true;
        
        cube->mDensityCube[x][cube->NormalizeCoordinate(y + i)][z] = true;
        cube->mDensityCube[x][cube->NormalizeCoordinate(y - i)][z] = true;

        cube->mDensityCube[x][y][cube->NormalizeCoordinate(z + i)] = true;
        cube->mDensityCube[x][y][cube->NormalizeCoordinate(z - i)] = true;
    }
}