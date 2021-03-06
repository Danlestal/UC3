#include "OgreFramework.h"
 
using namespace Ogre; 
 
template<> OgreFramework* Ogre::Singleton<OgreFramework>::msSingleton = 0;
 
/// <summary>
/// Initializes a new instance of the <see cref="OgreFramework"/> class. Just init some required variables.
/// </summary>
OgreFramework::OgreFramework()
{
	m_MoveSpeed = 0.4f;
	m_RotateSpeed = 0.3f;
	m_bShutDownOgre = false;
	m_iNumScreenShots = 0;
	m_pRoot = 0;
	m_pSceneMgr = 0;
	m_pRenderWnd = 0;
	m_pCamera = 0;
	m_pViewport = 0;
	m_pLog = 0;
	m_pTimer = 0;
	m_pInputMgr = 0;
	m_pKeyboard = 0;
	m_pMouse = 0;
    m_pTrayMgr = 0;
    m_FrameEvent = Ogre::FrameEvent();
}

/// <summary>
/// Inits the ogre framework.
/// 1.Instantiates the log manager class
/// 2. Creates a new Ogre root
/// 3. Creates the scene manager and set some ambient light
/// 4. Creates the camera and sets its position and clip planes
/// 5. Creates the viewport and sets the background color
/// 6. Creates the input devices
/// 7. Loads the resources
/// 8. Creates the timer
/// 9. Creates the debug overlay
/// 10. Sets the render window active
/// </summary>
/// <param name="wndTitle">The WND title.</param>
/// <param name="pKeyListener">The p key listener.</param>
/// <param name="pMouseListener">The p mouse listener.</param>
/// <returns></returns>
bool OgreFramework::initOgre(Ogre::String wndTitle, Ogre::SceneType sceneType, OIS::KeyListener *pKeyListener,  OIS::MouseListener *pMouseListener )
{
	Ogre::LogManager* logMgr = new Ogre::LogManager();
 
	m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);
 
	m_pRoot = new Ogre::Root("plugins.cfg");
 
	if(!m_pRoot->showConfigDialog())
		return false;
	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
 
	m_pSceneMgr = m_pRoot->createSceneManager(sceneType, "SceneManager");
	
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();


	m_light = m_pSceneMgr->createLight("tstLight");
    m_light->setType(Ogre::Light::LT_DIRECTIONAL);
    m_light->setDirection(lightdir);
    m_light->setDiffuseColour(Ogre::ColourValue::White);
    m_light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
	
	
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_cameraNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("CameraNode");
	m_cameraNode->setPosition(Vector3(0, 60, 60));

	m_pCamera = m_pSceneMgr->createCamera("Camera");
	m_pCamera->setNearClipDistance(1);
 
	m_pViewport = m_pRenderWnd->addViewport(m_pCamera);
    m_pViewport->setBackgroundColour(Ogre::ColourValue::Blue);
 
	m_pCamera->setAspectRatio(Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight()));
 
	m_pViewport->setCamera(m_pCamera);
 
	m_cameraNode->attachObject(m_pCamera);

	size_t hWnd = 0;
	m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
	m_pInputMgr = OIS::InputManager::createInputSystem(hWnd);

 
    m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
	m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));
 
	m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
	m_pMouse->getMouseState().width	 = m_pRenderWnd->getWidth();
 
	if(pKeyListener == 0)
		m_pKeyboard->setEventCallback(this);
	else
		m_pKeyboard->setEventCallback(pKeyListener);
 
	if(pMouseListener == 0)
		m_pMouse->setEventCallback(this);
	else
		m_pMouse->setEventCallback(pMouseListener);
 
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
    cf.load("resources.cfg");
 
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
 
	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();
 
	OgreBites::InputContext inputContext = OgreBites::InputContext::InputContext();
	inputContext.mMouse = m_pMouse;


     /*

	m_pTrayMgr = new OgreBites::SdkTrayManager("TrayMgr", m_pRenderWnd, inputContext, this);
        m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
        m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        m_pTrayMgr->hideCursor();
		*/
	m_pRenderWnd->setActive(true);
 
	return true;
}

/// <summary>
/// Finalizes an instance of the <see cref="OgreFramework"/> class.
/// </summary>
OgreFramework::~OgreFramework()
{
    if(m_pInputMgr) OIS::InputManager::destroyInputSystem(m_pInputMgr);
    if(m_pTrayMgr)  delete m_pTrayMgr;
    if(m_pRoot)     delete m_pRoot;
    if(m_pTimer)     delete m_pTimer;
}

/// <summary>
/// Interacts agains the keyPressedEvent.
/// </summary>
/// <param name="keyEventRef">The key event ref.</param>
/// <returns></returns>
bool OgreFramework::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
			m_bShutDownOgre = true;
			return true;
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ))
	{
		m_pRenderWnd->writeContentsToTimestampedFile("BOF_Screenshot_", ".png");
		return true;
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_M))
	{
		static int mode = 0;
 
		if(mode == 2)
		{
			m_pCamera->setPolygonMode(PM_SOLID);
			mode = 0;
		}
		else if(mode == 0)
		{
			 m_pCamera->setPolygonMode(PM_WIREFRAME);
			 mode = 1;
		}
		else if(mode == 1)
		{
			m_pCamera->setPolygonMode(PM_POINTS);
			mode = 2;
		}
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_O))
	{
		if(m_pTrayMgr->isLogoVisible())
                {
                        m_pTrayMgr->hideLogo();
                        m_pTrayMgr->hideFrameStats();
                }
                else
                {
                        m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
                        m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
                }
	}
 
	return true;
}

/// <summary>
/// Keys the released.
/// </summary>
/// <param name="keyEventRef">The key event ref.</param>
/// <returns></returns>
bool OgreFramework::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

/// <summary>
/// Mouses the moved.
/// </summary>
/// <param name="evt">The evt.</param>
/// <returns></returns>
bool OgreFramework::mouseMoved(const OIS::MouseEvent &evt)
{
	m_cameraNode->yaw(Degree(evt.state.X.rel * -0.1f));
	m_cameraNode->pitch(Degree(evt.state.Y.rel * -0.1f));
 
	return true;
}

/// <summary>
/// Mouses the pressed.
/// </summary>
/// <param name="evt">The evt.</param>
/// <param name="id">The id.</param>
/// <returns></returns>
bool OgreFramework::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}
 
/// <summary>
/// Mouses the released.
/// </summary>
/// <param name="evt">The evt.</param>
/// <param name="id">The id.</param>
/// <returns></returns>
bool OgreFramework::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

/// <summary>
/// Updates the ogre.
/// </summary>
/// <param name="timeSinceLastFrame">The time since last frame.</param>
void OgreFramework::updateOgre(double timeSinceLastFrame)
{
	m_MoveScale = m_MoveSpeed   * (float)timeSinceLastFrame;
	m_RotScale  = m_RotateSpeed * (float)timeSinceLastFrame;
 
	m_TranslateVector = Vector3::ZERO;
 
	getInput();
	moveCamera();
 
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    //  TODO: check the overlay system.
	//    m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
}

/// <summary>
/// Moves the camera.
/// </summary>
void OgreFramework::moveCamera()
{
	if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT)) 
	{
		m_cameraNode->translate(m_cameraNode->getOrientation() * m_TranslateVector);
	}
	else
	{
		m_cameraNode->translate(m_cameraNode->getOrientation() * (m_TranslateVector / 10));
	}
}

/// <summary>
/// Gets the input.
/// </summary>
void OgreFramework::getInput()
{
	if(m_pKeyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;
}