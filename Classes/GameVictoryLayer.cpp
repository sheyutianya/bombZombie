#include "GameVictoryLayer.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "Global.h"

using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

void CGameVictoryLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority * 2, true);
}

bool CGameVictoryLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	menuRestart(NULL);
	return true;
}

bool CGameVictoryLayer::init(){
	
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(50,50,50,50)));
		setKeypadEnabled(true);
		setTouchEnabled(true);
		m_Setting = Setting::GetSettingInstance();

		//CCSprite*tipsprite = CCSprite::create("levcross.png");
		//addChild(tipsprite);
		//tipsprite->setPosition(ccp(240,400));
		CCArmature *tipArmature = CCArmature::create("levcross");
		addChild(tipArmature);
		tipArmature->getAnimation()->play("levcrossanimate");
		tipArmature->setPosition(ccp(400,240));


		Setting::g_icurrentGate++;
		int unlockNum = getNumWithDecode("Unlock_gate");
		if (unlockNum < Setting::g_icurrentGate)	{
			SaveNumWithEncode("Unlock_gate",Setting::g_icurrentGate);
			//LeveCount(Setting::g_icurrentGate);//统计 用户 关卡
		}
		CCString *temp = CCString::createWithFormat("GATE%d_STARNUM",(Setting::g_icurrentGate)-1);
		SaveNumWithEncode(temp->getCString(),3);

		bRet = true;
	} while (0);
	return bRet;
}

void CGameVictoryLayer::menuCloseCallback(CCObject* pSender){

	CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
	bool bAduio = userDefault->getBoolForKey("AudioSwitch");
	if (bAduio){
		SimpleAudioEngine::sharedEngine()->playEffect("audio/sfx_click.ogg",false);
	}
	getParent()->removeChild(this);
}

void CGameVictoryLayer::menuRestart(cocos2d::CCObject*pSender){





	getParent()->removeChild(this);
	SceneManager::goPlay(kSceneTagSelectGate);
}

void CGameVictoryLayer::menuSelectedLayer(cocos2d::CCObject*pSender){
	getParent()->removeChild(this);
	SceneManager::goPlay(kSceneTagSelectGate);
}

void CGameVictoryLayer::keyBackClicked(){

}

void CGameVictoryLayer::step(float dt){

	//播放粒子效果//
}


void CGameVictoryLayer::onEnter(){
	CCLayer::onEnter();
}

void CGameVictoryLayer::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}