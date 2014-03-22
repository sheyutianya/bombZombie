#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameSceneLayer.h"
#include "SceneManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{

	ActionManager::shareManager()->purgeActionManager();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	UIHelper::instance()->purgeUIHelper();
	SimpleAudioEngine::sharedEngine()->end();
	CCArmatureDataManager::sharedArmatureDataManager()->purge();
	delete Setting::GetSettingInstance();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();

    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(Setting::g_ResolusionWidth,Setting::g_ResolusionHeight,kResolutionExactFit);


	CCEGLView *pView = CCEGLView::sharedOpenGLView();
	pView->setDesignResolutionSize(Setting::g_ResolusionWidth,Setting::g_ResolusionHeight,kResolutionExactFit);

	
    // turn on display FPS
   // pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
   // SceneManager::goPlay(kSceneTagMain);
	CCScene *pscene = CCScene::create();
	logo *pLayer = logo::create();
	pscene->addChild(pLayer);
	pDirector->runWithScene(pscene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	 SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	 Music_Resume();
}
