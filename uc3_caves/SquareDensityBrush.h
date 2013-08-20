#ifndef SquareDensityCubeBrush_HPP
#define SquareDensityCubeBrush_HPP
 
#include "UberCube.h"
#include "DensityCubeBrush.h"

class SquareDensityCubeBrush : public DensityCubeBrush
{
    private:
        int _brushSize;


	public:

        SquareDensityCubeBrush(int brushSize);

	    void UpdateDensityCube(UberCube* cube, int x, int y, int z);
};

#endif 
 
