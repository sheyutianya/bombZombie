#include "SelectLevelScene.h"
#include "SceneManager.h"
#include "Global.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* SelectLevelScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SelectLevelScene *layer = SelectLevelScene::create();
		CC_BREAK_IF(! layer);
		layer->setZOrder(2);
		scene->addChild(layer);
	
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SelectLevelScene::init()
{
	bool bRet = false;
	do 
	{	//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());
		setKeypadEnabled(true);
		CCSprite *bg = CCSprite::create("selectbg1.png");
		addChild(bg,-2);
		bg->setAnchorPoint(ccp(0,0));

		int unlock_gate = getNumWithDecode("Unlock_gate");

		m_pUILayer = UILayer::create();
		addChild(m_pUILayer);

		m_pUILayer->addWidget(dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("bombselect_1.json")));
		
		for (int i = 0; i < 20; i++){

			UIButton *btn_gate = dynamic_cast<UIButton*>(m_pUILayer->getWidgetByName(CCString::createWithFormat("btn_gate%d",i+1)->getCString()));
			btn_gate->setTag((i+1));
			btn_gate->addReleaseEvent(this,coco_releaseselector(SelectLevelScene::onStart));
			if (i + 1 > unlock_gate){
				btn_gate->removeAllChildren();
				btn_gate->disable(false);
			}
			CCString *temp = CCString::createWithFormat("GATE%d_STARNUM",i+1);
			int StarNum = getNumWithDecode(temp->getCString());
			if (3 == StarNum){
				CCSprite*starSprite = CCSprite::create("gateicon/star3.png");
				addChild(starSprite,2);
				starSprite->setPosition(ccpAdd(btn_gate->getPosition(),ccp(-2,-1)));
			}
		}

		UIButton *btn_back = dynamic_cast<UIButton*>(m_pUILayer->getWidgetByName("btn_back"));
		btn_back->addReleaseEvent(this,coco_releaseselector(SelectLevelScene::onBack));
	
		bRet=true;
	} while (0);

	return bRet;
}


void SelectLevelScene::keyBackClicked(){
	SceneManager::goPlay(kSceneTagMain);
}

void SelectLevelScene::onExit(){

	CCLayer::onExit();
	//CCArmatureDataManager::sharedArmatureDataManager()->purge();
	//CCArmatureDataManager::sharedArmatureDataManager()->removeAll();
}

void SelectLevelScene::onEnter(){
	CCLayer::onEnter();
	Music_playBackgroundMusic("sound148.mp3");
}

void SelectLevelScene::onStart(CCObject *pSender){

	UIButton* temp  = (UIButton*)pSender;
	Setting::g_icurrentGate = temp->getTag();
	SceneManager::goPlay(kSceneTagGame);
}

void SelectLevelScene::onBack(cocos2d::CCObject *pSender){
	SceneManager::goPlay(kSceneTagMain);
}