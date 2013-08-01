#ifndef UberCube_HPP
#define UberCube_HPP
 

#define UBERCUBE_SIZE 20

class UberCube
{
	public:
        bool _densityCube[UBERCUBE_SIZE][UBERCUBE_SIZE][UBERCUBE_SIZE];
		void GetNeighbourPoints(int x, int y, int z, bool* outNeighbours);
        UberCube();
};

#endif 
 
