#include "CubePolisher.h"


void CubePolisher::PolishCube(UberCube* cube)
{
    for(int i = 1; i < UBERCUBE_SIZE -1; ++i)
    {
        for(int j = 1; j < UBERCUBE_SIZE -1; ++j)
        {
            for(int k = 1; k < UBERCUBE_SIZE -1; ++k)
            {
                bool neighbours[8];
                cube->GetNeighbourPoints(i,j,k, neighbours);

                if(cube->mDensityCube[i][j][k] == false)
                {
 
                    int numberOfTrueNeighbours = 0;
                    for(int z =0; z<8; ++z)
                    {
                        if(neighbours[z])
                            numberOfTrueNeighbours++;
                    }

                    if(numberOfTrueNeighbours > 3)
                    {
                        cube->mDensityCube[i][j][k] = true;
                    }
                 }
            }
        }
    }

}
