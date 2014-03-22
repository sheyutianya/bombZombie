#include "Bomb.h"
#include "Global.h"

USING_NS_CC;

Bomb::Bomb():isstartbool(false)
{

}

Bomb::~Bomb(){
	
	m_pExplodeAnimate->release();
	//CC_SAFE_RELEASE(m_pExplodeAnimate);
}

bool Bomb::init(){
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_pSprite = CCSprite::create("image 277.png");
		addChild(m_pSprite);
		m_pSprite->setTag(1001);//100表示附加的刚体为炸弹

		m_iTickTimer = 3.0f;
		CCLabelTTF *Text = CCLabelTTF::create("3","",18);
		addChild(Text);
		Text->setTag(m_iTextLabelTag);
		Text->setVisible(false);

		//爆炸动画
		CCAnimation *panimation = CCAnimation::create();
		for (int i= 0 ; i < 6 ; i++){
			panimation->addSpriteFrameWithFileName((CCString::createWithFormat("baoza/baoza%d.png",i+1))->getCString());
		}
		panimation->setDelayPerUnit(0.1f);
		m_pExplodeAnimate = CCAnimate::create(panimation);
		m_pExplodeAnimate->retain();

		schedule(schedule_selector(Bomb::updateLable));
	

		//startBombing();//开始爆炸

		bRet = true;
	} while (0);

	return bRet;
}

CCSprite* Bomb::getTheSprite(){

	return m_pSprite;
}

CCPoint Bomb::getSpritePos(){
	
	return m_pSprite->getPosition();
}

void Bomb::setSpritePos(CCPoint position){

	m_pSprite->setPosition(position);
}

void Bomb::updateLable(float dt){
	CCLabelTTF *text = (CCLabelTTF*)getChildByTag(m_iTextLabelTag);
	text->setPosition(ccp(m_pSprite->getPositionX(),m_pSprite->getPositionY()+20));
}

void Bomb::startBombing(){
	if(isstartbool)
	{
		return;
	}
		CCLabelTTF *text = (CCLabelTTF*)getChildByTag(m_iTextLabelTag);
	text->setVisible(true);

	schedule(schedule_selector(Bomb::tickTimer),1.0f);
	isstartbool = true;
}

void Bomb::tickTimer(float dt){
	m_iTickTimer--;
	CCString *timeNum = CCString::createWithFormat("%d",m_iTickTimer);
	CCLabelTTF *text = (CCLabelTTF*)getChildByTag(m_iTextLabelTag);
	text->setString(timeNum->getCString());

	if (m_iTickTimer <= 0)	{
		if (m_callback && m_callbackListener){
			(m_callbackListener->*m_callback)(m_pSprite);
		}
		unschedule(schedule_selector(Bomb::tickTimer));
		unschedule(schedule_selector(Bomb::updateLable));
		text->setVisible(false);
		//this->removeFromParentAndCleanup(true);
		//播放爆炸动画
		Music_playEffect("sound154.mp3");
		
		CCCallFuncO *call = CCCallFuncO::create(this,callfuncO_selector(Bomb::ExplodeFinish),m_pSprite);
		CCSequence *seq = CCSequence::create(m_pExplodeAnimate,call,NULL);
		m_pSprite->runAction(seq);
	}
}

void Bomb::setCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncN callfun){
	m_callbackListener = target;
	m_callback = callfun;    
}

void Bomb::ExplodeFinish(cocos2d::CCObject *obj){
	this->removeAllChildrenWithCleanup(true);
}