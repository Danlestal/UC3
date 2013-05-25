#ifndef RANDOMTERRAIN__H
#define RANDOMTERRAIN__H

#include "Terrain.h"

class RandomTerrain : public Terrain
{
	virtual void DefineTerrain(int x, int y);
};

#endif