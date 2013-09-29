#ifndef MarchingCubes_HPP
#define MarchingCubes_HPP

#include "OgreFramework.h"
#include "UberCube.h"
#include "MarchingCubesTable.h"
#include "BooleanVoxel.h"

struct Voxel
{
	bool _vertex0;
	bool _vertex1;
	bool _vertex2;
	bool _vertex3;
	bool _vertex4;
	bool _vertex5;
	bool _vertex6;
	bool _vertex7;
	
	Voxel(bool vertex0, bool vertex1, bool vertex2,	bool vertex3, bool vertex4, bool vertex5, bool vertex6, bool vertex7)
	{
		 _vertex0 = vertex0;
		 _vertex1 = vertex1;
		 _vertex2 = vertex2;
		 _vertex3 = vertex3;
		 _vertex4 = vertex4;
		 _vertex5 = vertex5;
		 _vertex6 = vertex6;
		 _vertex7 = vertex7;
	}
};

class MarchingCubes
{
	public:
	void Poligonize(UberCube* cube, Ogre::MeshPtr mesh);
	int CreateRawTrianglesVector(UberCube* cube, std::vector<RawTriangle> *trianglesVector, Ogre::Vector3 cubeOffset = Ogre::Vector3::ZERO);

};


#endif