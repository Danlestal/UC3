#include "CavePoligonizer.h"


 Ogre::ManualObject* CavePoligonizer::Poligonize(CaveRegion region)
{
	char regionName[50];
	region.GetID(regionName);
    Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(regionName);
	mMarchingCubesAlgorithm.Poligonize(region.GetDensityCube(), manual);

	return manual;
}

void GetVectorInformation(Ogre::ManualObject* manualObject, std::vector<Ogre::Vector3> vertices)
{
    Ogre::ManualObject::ManualObjectSection* section = static_cast<Ogre::ManualObject*>(manualObject)->getSection(0) ;
    Ogre::RenderOperation* renderOperation = section->getRenderOperation();
    Ogre::VertexData* vertexData = renderOperation->vertexData;

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
        vertices.push_back(Ogre::Vector3(pt.x, pt.y,pt.z));
    }
}

void GetBoundaryVertex(std::vector<Ogre::Vector3> allVertex, CubeFace boundaryFace, std::vector<Ogre::Vector3> boundaryVertex)
{
    switch(boundaryFace)
    {
        case CubeFace::LEFT:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex.begin(); allVertexIterator != allVertex.end(); ++allVertexIterator)
            {
                if((*allVertexIterator).x == 0)
                {
                    boundaryVertex.push_back(*allVertexIterator);
                }
            }
        break;
        case CubeFace::TOP:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex.begin(); allVertexIterator != allVertex.end(); ++allVertexIterator)
            {
                if((*allVertexIterator).y == UBERCUBE_SIZE -1)
                {
                    boundaryVertex.push_back(*allVertexIterator);
                }
            }
        break;
        case CubeFace::RIGHT:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex.begin(); allVertexIterator != allVertex.end(); ++allVertexIterator)
            {
                if((*allVertexIterator).x == UBERCUBE_SIZE -1)
                {
                    boundaryVertex.push_back(*allVertexIterator);
                }
            }
        break;
        case CubeFace::BOTTON:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex.begin(); allVertexIterator != allVertex.end(); ++allVertexIterator)
            {
                if((*allVertexIterator).y == 0)
                {
                    boundaryVertex.push_back(*allVertexIterator);
                }
            }
        break;
        case CubeFace::FRONT:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex.begin(); allVertexIterator != allVertex.end(); ++allVertexIterator)
            {
                if((*allVertexIterator).z == 0)
                {
                    boundaryVertex.push_back(*allVertexIterator);
                }
            }
        break;
        case CubeFace::BACK:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex.begin(); allVertexIterator != allVertex.end(); ++allVertexIterator)
            {
                if((*allVertexIterator).z == UBERCUBE_SIZE -1)
                {
                    boundaryVertex.push_back(*allVertexIterator);
                }
            }
        break;
    }

   
}

std::map<CubeFace, Ogre::ManualObject*> CavePoligonizer::PoligonizeNeighbours(CaveRegion region,  Ogre::ManualObject* mainRegionManualObject)
{
	std::map<CubeFace, Ogre::ManualObject*> result;
	
    // BEGIN: LOL
    std::vector<Ogre::Vector3> mainRegionVectorInfo;
    GetVectorInformation(mainRegionManualObject, mainRegionVectorInfo);
    
    // END: LOL


	std::map<CubeFace, CaveRegion*>::iterator neighboursMapIterator;
	for (neighboursMapIterator = region.GetNeighbours().begin(); neighboursMapIterator != region.GetNeighbours().end(); ++neighboursMapIterator)
	{
        CaveRegion* neighBourRegion = neighboursMapIterator->second;
        
        char neighBourRegionName[50];
	    neighBourRegion->GetID(neighBourRegionName);

        Ogre::ManualObject *neighbourManual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(neighBourRegionName);
        mMarchingCubesAlgorithm.Poligonize(neighBourRegion->GetDensityCube(), neighbourManual);

        std::vector<Ogre::Vector3> boundaryVectorInfo;
        GetBoundaryVertex(mainRegionVectorInfo, neighboursMapIterator->first, boundaryVectorInfo);


        // Add the new stick section with the region. To do so, we need to have the final vertex of the region.
    }
    return result;
}

Ogre::ManualObject* CavePoligonizer::PoligonizeNeighbour(CaveRegion region, CubeFace faceWithNeighbour)
{

	return nullptr;
}