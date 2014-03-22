
#include "PauseLayer.h"
#include "SceneManager.h"
#include "Global.h"

using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

void CPauseLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CPauseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

	return true;
}

bool CPauseLayer::init(){

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(50,50,50,50)));
		setKeypadEnabled(true);
		setTouchEnabled(true);
		m_pSetting = Setting::GetSettingInstance();

		UILayer *uiLayer = UILayer::create();
		addChild(uiLayer);
		uiLayer->addWidget(dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("pause_1.ExportJson")));
		uiLayer->setTouchPriority(kCCMenuHandlerPriority*2 - 1);

		UIButton *btn_menu = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("button_menu"));
		btn_menu->addReleaseEvent(this,coco_releaseselector(CPauseLayer::onBackSelectLayer));
		//btn_menu->

		UIButton*btn_restart = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("button_restart"));
		btn_restart->addReleaseEvent(this,coco_releaseselector(CPauseLayer::onReStart));

		UIButton*btn_resume = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("button_resume"));
		btn_resume->addReleaseEvent(this,coco_releaseselector(CPauseLayer::onResume));

		bRet = true;
	} while (0);
	return bRet;
}


void CPauseLayer::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->pause();
}

void CPauseLayer::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->resume();
}

void CPauseLayer::onResume(CCObject*pSender){

	this->getParent()->removeChild(this);
}

void CPauseLayer::onBackSelectLayer(cocos2d::CCObject*pSender){
	SceneManager::goPlay(kSceneTagSelectGate);
}

void CPauseLayer::onReStart(cocos2d::CCObject*pSender){
	SceneManager::goPlay(kSceneTagGame);
}