#ifndef BooleanVoxel_HPP
#define BooleanVoxel_HPP

#include "OgreFramework.h"

class BooleanVoxel
{
private:
	Ogre::Vector3 _voxelPosition;
    bool _vertex0;
	bool _vertex1;
	bool _vertex2;
	bool _vertex3;
	bool _vertex4;
	bool _vertex5;
	bool _vertex6;
	bool _vertex7;

    int GetEdgeTableIndex();

    /*
       Linearly interpolate the position where an isosurface cuts
       an edge between two vertices, each with their own scalar value
    */
    Ogre::Vector3 VertexInterp(Ogre::Vector3 p1, Ogre::Vector3 p2, bool booleanValue1 ,bool booleanValue2)
    {
        double mu;
        Ogre::Vector3 result;

        if (!booleanValue1)
            return(p1);

        if (!booleanValue2)
            return(p2);
    
        if (booleanValue1 && booleanValue2)
        {
            return(p1);
        }

        return(p2);
    }

public:	
	BooleanVoxel(Ogre::Vector3 voxelPosition, bool vertex0, bool vertex1, bool vertex2,	bool vertex3, bool vertex4, bool vertex5, bool vertex6, bool vertex7);
	BooleanVoxel(Ogre::Vector3 voxelPosition, bool* vertexList);
    void GetTriangle();
	


};

#endif