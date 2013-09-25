#ifndef CavesApp_HPP
#define CavesApp_HPP

#include "OgreFramework.h"
#include "BasicApp.h"
#include "PerlinNoiseGenerator.h"

#include "CaveRegion.h"
#include "DensityCubeBrush.h"
#include "SquareDensityBrush.h"
#include "StandardCubeSmoother.h"
#include "CubeWalker.h"
 
class CavesApp : public BasicApp
{
	private:
		
        CaveRegion* mRegion;
        CaveRegion* mRegion2;
        SquareDensityCubeBrush *mBrush;
        CubeWalker *mWalker;
        StandardCubeSmoother *mSmoother;
        
        virtual void setupScene();
        virtual void cleanScene();
	
     public:
		virtual void updateLogic();
};

#endif 
 
