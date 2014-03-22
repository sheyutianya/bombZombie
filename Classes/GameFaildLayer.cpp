#include "GameFaildLayer.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"


using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

void CGameFaildLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority * 2, true);
}

bool CGameFaildLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	menuRestart(NULL);
	return true;
}

bool CGameFaildLayer::init(){
	bool bRet = false;
	do 
	{
		if (!CCLayerColor::initWithColor(ccc4(50,50,50,50))){
			return false;
		}
		setTouchEnabled(true);

		//CCLabelTTF *tips = CCLabelTTF::create("game faild , restart","",20);
		//addChild(tips);
		//tips->setPosition(ccp(240,400));
		//CCSprite*tipsprite = CCSprite::create("levlost.png");
		//addChild(tipsprite);
		//tipsprite->setPosition(ccp(240,400));
		CCArmature *tipsprite = CCArmature::create("levfaild");
		addChild(tipsprite);
		tipsprite->getAnimation()->play("levfaildanimate");
		tipsprite->setPosition(ccp(400,240));

		bRet = true;
	} while (0);

	return bRet;
}

void CGameFaildLayer::menuCloseCallback(CCObject* pSender){

	CCDirector::sharedDirector()->resume();
	getParent()->removeChild(this);
}

void CGameFaildLayer::menuRestart(cocos2d::CCObject*pSender){

	getParent()->removeChild(this);
	SceneManager::goPlay(kSceneTagGame);
}

void CGameFaildLayer::menuSelectedLayer(cocos2d::CCObject*pSender){

	SceneManager::goPlay(kSceneTagMain);
	getParent()->removeChild(this);
}

void CGameFaildLayer::keyBackClicked(){

}

void CGameFaildLayer::step(float dt){
	SceneManager::goPlay(kSceneTagSelectGate);
}


void CGameFaildLayer::onEnter(){

	CCLayer::onEnter();
}

void CGameFaildLayer::onExit(){

	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}