#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "Global.h"

using namespace CocosDenshion;
using namespace cocos2d;
USING_NS_CC;
USING_NS_CC_EXT;

CCScene* CMainScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		// 'layer' is an autorelease object
		CMainScene *layer = CMainScene::create();
		CC_BREAK_IF(! layer);
		//	ccColor4B c4b={0x00,0x00,0x00,0x12};
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CMainScene::init()
{
	bool bRet = false;
	do 
	{	
		CC_BREAK_IF(! CCLayer::init());
		setKeypadEnabled(true);
	    m_Setting = Setting::GetSettingInstance();

		//1加载动画
		//2数据初始化
		if (! LoadBooleanFromXML("bomb_isExist")){
			SaveBooleanToXML("bomb_isExist",true);
			SaveBooleanToXML("MusicSwitch",true);
			SaveBooleanToXML("AudioSwitch",true);
			SaveBooleanToXML("BgMusicSwitch",true);
			SaveNumWithEncode("Unlock_gate",1);
			SaveFlush();
		}
		
		initScene();



		bRet=true;
	} while (0);

	return bRet;
}




void CMainScene::keyBackClicked(){
	CCDirector::sharedDirector()->end();
}

void CMainScene::initScene(){

	//add the background image
	CCSprite*bgSprite = CCSprite::create("main_bg.png");
	addChild(bgSprite);
	bgSprite->setAnchorPoint(ccp(0,0));

	CCSprite *title = CCSprite::create("title.png");
	addChild(title);
	title->setPosition(ccp(400,380));

	//音效和音乐按钮
	CCMenuItemToggle *pMusicItem = CCMenuItemToggle::createWithTarget(this,  
		menu_selector(CMainScene::onMusicSwitch),  
		CCMenuItemImage::create("button/btn_yinyue1.png","button/btn_yinyue1.png"),  
		CCMenuItemImage::create("button/btn_yinyue2.png","button/btn_yinyue2.png"),
		NULL); 
	CCMenuItemToggle *pAudioItem = CCMenuItemToggle::createWithTarget(this,
		menu_selector(CMainScene::onAudioSwitch),
		CCMenuItemImage::create("button/btn_yinxiao1.png","button/btn_yinxiao2.png"),
		CCMenuItemImage::create("button/btn_yinxiao2.png","button/btn_yinxiao2.png"),
		NULL);

	if (LoadBooleanFromXML("MusicSwitch")){
		m_Setting->g_MusicSwitch = true;
		pMusicItem->setSelectedIndex(0);
	}else{
		pAudioItem->setSelectedIndex(1);
		m_Setting->g_MusicSwitch = false;
	}

	if (LoadBooleanFromXML("BgMusicSwitch")){
		m_Setting->g_BgMusicSwitch = true;
		pAudioItem->setSelectedIndex(0);
	}else{
		pAudioItem->setSelectedIndex(1);
		m_Setting->g_BgMusicSwitch = false;
	}

	CCMenu *menuSound = CCMenu::create(pMusicItem,pAudioItem,NULL);
	menuSound->alignItemsHorizontallyWithPadding(20);
	addChild(menuSound);
	menuSound->setTag(90);
	menuSound->setPosition(250,60);
	//开始按钮
	// add menu item 
	CCMenuItemImage *StartGameItem = CCMenuItemImage::create("button/btn_start1.png","button/btn_start1.png",this,menu_selector(CMainScene::onStart));
	CCMenu *StartMenu = CCMenu::create(StartGameItem,NULL);
	addChild(StartMenu);
	StartMenu->setPosition(ccp(400,240));

	CCParticleSnow * pSnow = CCParticleSnow::create();
	pSnow->setPosition(ccp(400,480));
	addChild(pSnow);

	pSnow->setSpeedVar(10);
	pSnow->setTangentialAccelVar(10);

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("levcross0.png","levcross0.plist","levcross.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("levfaild0.png","levfaild0.plist","levfaild.ExportJson");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cannonsheet.plist");

	Music_PreLoadEffect("sound16.mp3");
	Music_PreLoadEffect("sound35.mp3");
	Music_PreLoadEffect("sound41.mp3");
	Music_PreLoadEffect("sound42.mp3");
	Music_PreLoadEffect("sound145.mp3");
	Music_PreLoadEffect("sound146.mp3");
	Music_PreLoadEffect("sound147.mp3");
	Music_PreLoadEffect("sound150.mp3");
	Music_PreLoadEffect("sound151.mp3");
	Music_PreLoadEffect("sound152.mp3");
	Music_PreLoadEffect("sound153.mp3");
	Music_PreLoadEffect("sound154.mp3");
	Music_PreLoadEffect("ms_button.mp3");

	Music_PreLoadMusic("sound148.mp3");
	Music_PreLoadMusic("sound149.mp3");
	Music_playBackgroundMusic("sound148.mp3");

}


void CMainScene::onStart(CCObject*pSender){

	Music_playEffect("ms_button.mp3");
	SceneManager::goPlay(kSceneTagSelectGate);
}

void CMainScene::onMusicSwitch(CCObject *pSender){

	Music_playEffect("ms_button.mp3");
	if (m_Setting->g_MusicSwitch){
		m_Setting->g_MusicSwitch = false;
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}else{
		m_Setting->g_MusicSwitch = true;
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

void CMainScene::onAudioSwitch(cocos2d::CCObject *pSender){
	
	Music_playEffect("ms_button.mp3");
	if (m_Setting->g_AudioSwitch){
		m_Setting->g_AudioSwitch = false;
	}else{
		m_Setting->g_AudioSwitch = true;
	}
}


void CMainScene::loadingCallBack(CCObject *obj){

	++m_nNumberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp,"%d", (int)(((float)m_nNumberOfLoadedSprites / m_nNumberOfSprites) * 100));

	if (m_nNumberOfLoadedSprites == m_nNumberOfSprites)	{
	}
}

void CMainScene::onEnter(){

	CCLayer::onEnter();
	Music_Resume();
	
}

void CMainScene::onExit(){

	CCLayer::onExit();
	SaveBooleanToXML("MusicSwitch",m_Setting->g_MusicSwitch);
	SaveBooleanToXML("BgMusicSwitch",m_Setting->g_BgMusicSwitch);
	SaveFlush();
	//CCArmatureDataManager::sharedArmatureDataManager()->purge();

}

void CMainScene::update(float delta){

	if (g_loadcomplete){
		initScene();
		unscheduleUpdate();
	}
}

void* CMainScene::updataIfo(void *args){

	g_loadcomplete = true;
	return NULL;
}

void CMainScene::onHelp(cocos2d::CCObject *pSender){
}

void CMainScene::onStartRaceMode(cocos2d::CCObject *pSender){
}