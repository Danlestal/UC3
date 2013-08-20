#ifndef DensityCubeBrush_HPP
#define DensityCubeBrush_HPP
 
#include "UberCube.h"

class DensityCubeBrush
{
	public:
	    virtual void UpdateDensityCube(UberCube* cube, int x, int y, int z) = 0;
};

#endif 
 
