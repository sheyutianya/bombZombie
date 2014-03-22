
#include "logo.h"
#include "SceneManager.h"

USING_NS_CC;


bool logo::init()
{
    bool flag=false;
    if(!CCLayer::init())
    {
        return false;
    }
	//CCSprite *bg = CCSprite::create("logobg.png");
	//addChild(bg);
	//bg->setAnchorPoint(ccp(0,0));

    flag=true;
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
   CCSprite *sprite=CCSprite::create("logo2.png");
    sprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(sprite);
    CCFadeOut *out=CCFadeOut::create(1.0f);
	CCFadeIn *in = CCFadeIn::create(1.0f);
    CCCallFunc *call=CCCallFunc::create(this, SEL_CallFunc(&logo::replace));
    CCFiniteTimeAction *finite=CCSequence::create(in,CCDelayTime::create(1.0f),call,NULL);
    sprite->runAction(finite);
    return flag;
}

void logo::replace(){
 SceneManager::goPlay(kSceneTagMain);
}