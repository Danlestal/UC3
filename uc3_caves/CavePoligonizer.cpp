#include "CavePoligonizer.h"


 Ogre::ManualObject* CavePoligonizer::Poligonize(CaveRegion region)
{
	char regionName[50];
	region.GetID(regionName);
    Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(regionName);
	mMarchingCubesAlgorithm.Poligonize(region.GetDensityCube(), manual);

	return manual;
}

void GetVectorInformation(Ogre::ManualObject* manualObject, Ogre::Vector3* &vertices)
{
    Ogre::ManualObject::ManualObjectSection* section = static_cast<Ogre::ManualObject*>(manualObject)->getSection(0) ;
    Ogre::RenderOperation* renderOperation = section->getRenderOperation();
    Ogre::VertexData* vertexData = renderOperation->vertexData;
    vertices = new Ogre::Vector3[vertexData->vertexCount];

    const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
    Ogre::HardwareVertexBufferSharedPtr vbuf = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
    unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
    Ogre::Real* pReal;


    for(size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vbuf->getVertexSize())
    {
        posElem->baseVertexPointerToElement(vertex, &pReal);

        Ogre::Vector3 pt;
        pt.x = (*pReal++);
        pt.y = (*pReal++);
        pt.z = (*pReal++);
        vertices[j].x = pt.x;
        vertices[j].y = pt.y;
        vertices[j].z = pt.z;
    }
}

void GetBoundaryVectors(Ogre::Vector3 *allVertex, CubeFace boundaryFace, Ogre::Vector3* &boundaryVertex)
{
}

std::map<CubeFace, Ogre::ManualObject*> CavePoligonizer::PoligonizeNeighbours(CaveRegion region,  Ogre::ManualObject* mainRegionManualObject)
{
	std::map<CubeFace, Ogre::ManualObject*> result;
	
    // BEGIN: LOL
    Ogre::Vector3 *mainRegionVectorInfo;
    GetVectorInformation(mainRegionManualObject, mainRegionVectorInfo);
    // END: LOL


	std::map<CubeFace, CaveRegion*>::iterator neighboursMapIterator;
	for (neighboursMapIterator = region.GetNeighbours().begin(); neighboursMapIterator != region.GetNeighbours().end(); ++neighboursMapIterator)
	{
        CaveRegion* neighBourRegion = neighboursMapIterator->second;
        
        char neighBourRegionName[50];
	    neighBourRegion->GetID(neighBourRegionName);

        Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(neighBourRegionName);
        mMarchingCubesAlgorithm.Poligonize(neighBourRegion->GetDensityCube(), manual);

        // Add the new stick section with the region. To do so, we need to have the final vertex of the region.
    }
    return result;
}

Ogre::ManualObject* CavePoligonizer::PoligonizeNeighbour(CaveRegion region, CubeFace faceWithNeighbour)
{

	return nullptr;
}