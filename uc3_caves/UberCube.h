#ifndef UberCube_HPP
#define UberCube_HPP

#define UBERCUBE_SIZE 100

class UberCube
{
	public:
        bool _densityCube[UBERCUBE_SIZE][UBERCUBE_SIZE][UBERCUBE_SIZE];
        UberCube();
        int NormalizeCoordinate(int coordinate);
        void GetNeighbourPoints(int x, int y, int z, bool* outNeighbours);
};

#endif 
 
