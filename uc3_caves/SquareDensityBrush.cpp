#include "SquareDensityBrush.h"

SquareDensityCubeBrush::SquareDensityCubeBrush(int brushSize)
{
    _brushSize = brushSize;
}

void SquareDensityCubeBrush::UpdateDensityCube(UberCube* cube,  int x, int y, int z)
{
    cube->_densityCube[x][y][z] = true;

    for(int i=0; i < _brushSize / 2; ++i)
    {
        cube->_densityCube[cube->NormalizeCoordinate(x + i)][y][z] = true;
        cube->_densityCube[cube->NormalizeCoordinate(x - i)][y][z] = true;
        
        cube->_densityCube[x][cube->NormalizeCoordinate(y + i)][z] = true;
        cube->_densityCube[x][cube->NormalizeCoordinate(y - i)][z] = true;

        cube->_densityCube[x][y][cube->NormalizeCoordinate(z + i)] = true;
        cube->_densityCube[x][y][cube->NormalizeCoordinate(z - i)] = true;
    }
}