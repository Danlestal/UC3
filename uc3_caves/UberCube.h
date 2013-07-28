#ifndef UberCube_HPP
#define UberCube_HPP
 
class UberCube
{
	public:
		bool _densityCube[1000][1000][1000];
		bool* GetNeighbourPoints(int x, int y, int z);
};

#endif 
 
