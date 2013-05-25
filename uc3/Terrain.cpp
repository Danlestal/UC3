#include "Terrain.h"

void Terrain::ConfigureGlobals()
{
	Terrain::m_terrainGlobals = new Ogre::TerrainGlobalOptions();
}

void Terrain::ConfigureGroup()
{
	m_terrainGroup = new Ogre::TerrainGroup(OgreFramework::getSingletonPtr()->m_pSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
    m_terrainGroup->setFilenameConvention(Ogre::String("Uc3Terrain"), Ogre::String("dat"));
    m_terrainGroup->setOrigin(Ogre::Vector3::ZERO);

	ConfigureTerrainDefaults(OgreFramework::getSingletonPtr()->m_light);

	for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            DefineTerrain(x, y);
 
    // sync load since we want everything in place when we start
    m_terrainGroup->loadAllTerrains(true);

	if (m_terrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = m_terrainGroup->getTerrainIterator();
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            InitBlendMaps(t);
        }
    }

	m_terrainGroup->freeTemporaryResources();

}

void Terrain::ConfigureTerrainDefaults(Ogre::Light *light)
{
	// Configure global
    m_terrainGlobals->setMaxPixelError(8);
    // testing composite map
    m_terrainGlobals->setCompositeMapDistance(3000);

	m_terrainGlobals->setLightMapDirection(light->getDerivedDirection());
    m_terrainGlobals->setCompositeMapAmbient(OgreFramework::getSingletonPtr()->m_pSceneMgr->getAmbientLight());
    m_terrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	Ogre::Terrain::ImportData& defaultimp = m_terrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600; // due terrain.png is 8 bpp
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;

	defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 100;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");

}

void Terrain::DefineTerrain(int x, int y)
{
	 Ogre::String filename = m_terrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(m_terrainGroup->getResourceGroup(), filename))
    {
        m_terrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        GetTerrainImage(x % 2 != 0, y % 2 != 0, img);
        m_terrainGroup->defineTerrain(x, y, &img);
        m_terrainsImported = true;
    }
}

void Terrain::GetTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX)
        img.flipAroundY();
    if (flipY)
        img.flipAroundX();
 
}

void Terrain::InitBlendMaps(Ogre::Terrain* terrain)
{
    Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
 
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;
 
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}