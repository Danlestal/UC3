#include "CavePoligonizer.h"


Ogre::ManualObject* CavePoligonizer::PoligonizeJoint(CaveRegion mainRegion, CubeFace unionFace, CaveRegion neighbourRegion)
{
    char mainRegionName[50];
	mainRegion.GetID(mainRegionName);

    char neighbourRegionName[50];
	mainRegion.GetID(mainRegionName);

    char glueRegionName[100];
    sprintf(glueRegionName, "%s|%s", mainRegionName, neighbourRegionName);

    Ogre::ManualObject *mainManual =  OgreFramework::getSingletonPtr()->m_pSceneMgr->getManualObject(mainRegionName);
    Ogre::ManualObject *neighbourManual =  OgreFramework::getSingletonPtr()->m_pSceneMgr->getManualObject(neighbourRegionName);

    std::vector<Ogre::Vector3> mainRegionVectorInfo;
    std::vector<Ogre::Vector3> *ptrMainRegionVectorInfo = &mainRegionVectorInfo;
    std::vector<Ogre::Vector3> mainRegionBoundaryVertex;
    std::vector<Ogre::Vector3> *ptrMainRegionBoundaryVertex = &mainRegionBoundaryVertex;

    GetVectorInformation(mainManual, ptrMainRegionVectorInfo);
    GetBoundaryVertex(ptrMainRegionVectorInfo, unionFace, ptrMainRegionBoundaryVertex);

    std::vector<Ogre::Vector3> neighbourRegionVectorInfo;
    std::vector<Ogre::Vector3> *ptrNeighbourRegionVectorInfo = &neighbourRegionVectorInfo;
    std::vector<Ogre::Vector3> neighbourRegionBoundaryVertex;
    std::vector<Ogre::Vector3> *ptrNeighbourRegionBoundaryVertex = &neighbourRegionBoundaryVertex;
    
    GetVectorInformation(neighbourManual, ptrNeighbourRegionVectorInfo);
    GetBoundaryVertex(ptrNeighbourRegionVectorInfo, GetOpossiteFace(unionFace), ptrNeighbourRegionBoundaryVertex);

    std::vector<Ogre::Vector3> allVertextInfo;
    


    Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(glueRegionName);


}


 Ogre::ManualObject* CavePoligonizer::Poligonize(CaveRegion region)
{
	char regionName[50];
	region.GetID(regionName);
    Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(regionName);
	mMarchingCubesAlgorithm.Poligonize(region.GetDensityCube(), manual);

	return manual;
}

void GetVectorInformation(Ogre::ManualObject* manualObject, std::vector<Ogre::Vector3> *vertices)
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
        vertices->push_back(Ogre::Vector3(pt.x, pt.y,pt.z));
    }
    vbuf->unlock();
}

void GetBoundaryVertex(std::vector<Ogre::Vector3> *allVertex, CubeFace boundaryFace, std::vector<Ogre::Vector3> *boundaryVertex)
{
    switch(boundaryFace)
    {
        case CubeFace::LEFT:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex->begin(); allVertexIterator != allVertex->end(); ++allVertexIterator)
            {
                if((*allVertexIterator).x == 0)
                {
                    if(std::find(boundaryVertex->begin(), boundaryVertex->end(), (*allVertexIterator)) == boundaryVertex->end()) 
                    {
                        boundaryVertex->push_back(*allVertexIterator); 
                    }
                }
            }
        break;
        case CubeFace::TOP:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex->begin(); allVertexIterator != allVertex->end(); ++allVertexIterator)
            {
                if((*allVertexIterator).y == UBERCUBE_SIZE -1)
                {
                   if(std::find(boundaryVertex->begin(), boundaryVertex->end(), (*allVertexIterator)) == boundaryVertex->end()) 
                    {
                        boundaryVertex->push_back(*allVertexIterator); 
                    }
                }
            }
        break;
        case CubeFace::RIGHT:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex->begin(); allVertexIterator != allVertex->end(); ++allVertexIterator)
            {
                if((*allVertexIterator).x == UBERCUBE_SIZE -1)
                {
                    if(std::find(boundaryVertex->begin(), boundaryVertex->end(), (*allVertexIterator)) == boundaryVertex->end()) 
                    {
                        boundaryVertex->push_back(*allVertexIterator); 
                    }
                }
            }
        break;
        case CubeFace::BOTTON:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex->begin(); allVertexIterator != allVertex->end(); ++allVertexIterator)
            {
                if((*allVertexIterator).y == 1)
                {
                    if(std::find(boundaryVertex->begin(), boundaryVertex->end(), (*allVertexIterator)) == boundaryVertex->end()) 
                    {
                        boundaryVertex->push_back(*allVertexIterator); 
                    }
                }
            }
        break;
        case CubeFace::FRONT:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex->begin(); allVertexIterator != allVertex->end(); ++allVertexIterator)
            {
                if((*allVertexIterator).z == 0)
                {
                    if(std::find(boundaryVertex->begin(), boundaryVertex->end(), (*allVertexIterator)) == boundaryVertex->end()) 
                    {
                        boundaryVertex->push_back(*allVertexIterator); 
                    }
                }
            }
        break;
        case CubeFace::BACK:
            for(std::vector<Ogre::Vector3>::iterator allVertexIterator = allVertex->begin(); allVertexIterator != allVertex->end(); ++allVertexIterator)
            {
                if((*allVertexIterator).z == UBERCUBE_SIZE -1)
                {
                    if(std::find(boundaryVertex->begin(), boundaryVertex->end(), (*allVertexIterator)) == boundaryVertex->end()) 
                    {
                        boundaryVertex->push_back(*allVertexIterator); 
                    }
                }
            }
        break;
    }

   
}


void StickRegions(Ogre::ManualObject* mainRegionManualObject, CubeFace boundaryFace, Ogre::ManualObject* neighbourRegion)
{

    std::vector<Ogre::Vector3> mainRegionVectorInfo;
    std::vector<Ogre::Vector3> *ptrMainRegionVectorInfo = &mainRegionVectorInfo;
    std::vector<Ogre::Vector3> mainRegionBoundaryVertex;
    std::vector<Ogre::Vector3> *ptrMainRegionBoundaryVertex = &mainRegionBoundaryVertex;

    GetVectorInformation(mainRegionManualObject, ptrMainRegionVectorInfo);
    GetBoundaryVertex(ptrMainRegionVectorInfo, boundaryFace, ptrMainRegionBoundaryVertex);

    std::vector<Ogre::Vector3> neighbourRegionVectorInfo;
    std::vector<Ogre::Vector3> *ptrNeighbourRegionVectorInfo = &neighbourRegionVectorInfo;
    std::vector<Ogre::Vector3> neighbourRegionBoundaryVertex;
    std::vector<Ogre::Vector3> *ptrNeighbourRegionBoundaryVertex = &neighbourRegionBoundaryVertex;
    
    GetVectorInformation(neighbourRegion, ptrNeighbourRegionVectorInfo);
    GetBoundaryVertex(ptrNeighbourRegionVectorInfo, GetOpossiteFace(boundaryFace), ptrNeighbourRegionBoundaryVertex);
    //1. Add the mainRegionVertex into the neighbourRegion manualObject.
    neighbourRegion->beginUpdate(0);
    for (std::vector<Ogre::Vector3>::iterator it = mainRegionBoundaryVertex.begin()  ; it != mainRegionBoundaryVertex.end(); ++it)
    {
        neighbourRegion->position(it->x, it->y, it->z);
    }
    
    //2. Add the correspondent indexes.
   


    //2. Get the biggest list of the two an iterate throug it.
        //2.1 Get the two




}


std::map<CubeFace, Ogre::ManualObject*> CavePoligonizer::PoligonizeNeighbours(CaveRegion region,  Ogre::ManualObject* mainRegionManualObject)
{
	std::map<CubeFace, Ogre::ManualObject*> result;
    std::map<CubeFace, CaveRegion*> neigbours = region.GetNeighbours();

    std::vector<Ogre::Vector3> mainRegionVectorInfo;
    std::vector<Ogre::Vector3> *ptrMainRegionVectorInfo = &mainRegionVectorInfo;
    std::vector<Ogre::Vector3> mainRegionBoundaryVertex;
    std::vector<Ogre::Vector3> *ptrMainRegionBoundaryVertex = &mainRegionBoundaryVertex;

    GetVectorInformation(mainRegionManualObject, ptrMainRegionVectorInfo);


	for (std::map<CubeFace, CaveRegion*>::iterator neighboursMapIterator = neigbours.begin(); neighboursMapIterator != neigbours.end(); ++neighboursMapIterator)
	{
        CaveRegion* neighBourRegion = neighboursMapIterator->second;
        
        char lol[50];
	    neighBourRegion->GetID(lol);
        Ogre::ManualObject *neighbourManual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(lol);

        GetBoundaryVertex(ptrMainRegionVectorInfo, neighboursMapIterator->first, ptrMainRegionBoundaryVertex);
        mMarchingCubesAlgorithm.Poligonize(neighBourRegion->GetDensityCube(), neighbourManual);

        
    }
    return result;
}

Ogre::ManualObject* CavePoligonizer::PoligonizeNeighbour(CaveRegion region, CubeFace faceWithNeighbour)
{

	return nullptr;
}