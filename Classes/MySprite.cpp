#include "MySprite.h"



MySprite::MySprite():
m_State(NORMAL)
{
}

MySprite::~MySprite()
{
	delete [] this->m_spriteName;
}

/************************************************************************/
/* 初始化                                                                     */
/************************************************************************/
bool  MySprite::initPhySprite()
{
	b2CircleShape polygon;
	polygon.m_radius = (float)this->getContentSize().width/PT_RATIO/2;
	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 0.8f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.1f;
	fixturedef.filter.categoryBits =0x0008;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)(this->getPosition().x / PT_RATIO),(float)(this->getPosition().y /PT_RATIO));
	bd.userData = this;

    spriteBody = m_pMyworld->CreateBody(&bd);//添加body到box2d world 中
	spriteBody->CreateFixture(&fixturedef);//

	return true;
}

/************************************************************************/
/*              获取精灵
  @param plistName 精灵的plist文件名称
  @param spriteName 精灵图片的名称 格式 例如 fire_%d.png
  @return包含精灵的节点
  @mark 精灵一共五张 图 两张正常 状态 两张 受伤状态 一张死亡 状态
   命名 1-5；例如 fire_1.png fire_2.png ………
  */
/************************************************************************/
MySprite* MySprite::getInstance(CCPoint point,const char* plistName ,const char * spriteName,b2World *pMyworld)
{
   
	MySprite* mySpriteNode = MySprite::create();
	mySpriteNode->m_pMyworld = pMyworld;
	char*  tempname = new char[50];
	//sprintf(tempname,spriteName,1);
	strcpy(tempname,spriteName);
	mySpriteNode->m_spriteName = tempname;

	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile(plistName);
	char*  temp = new char[50];
	sprintf(temp,spriteName,1);

	mySpriteNode->initWithSpriteFrameName(temp);
	mySpriteNode->setAnchorPoint(ccp(0.5,0.5));
	mySpriteNode->setPosition(point);

	CCAnimation *pAnimation = CCAnimation::create();
	pAnimation->setDelayPerUnit(0.3f);


	for(int i = 1 ; i < 3 ;i++)
	{
		sprintf(temp,spriteName,i);
		pAnimation->addSpriteFrame(frameCache->spriteFrameByName(temp));
	}

	delete []temp;
	mySpriteNode->runAction(CCRepeatForever::create(CCSequence::create(CCAnimate::create(pAnimation),CCDelayTime::create(2.0f),NULL)));


	mySpriteNode->initPhySprite();


	return mySpriteNode;
}

void MySprite::hurt()
{
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCAnimation *pAnimation = CCAnimation::create();
	pAnimation->setDelayPerUnit(0.3f);
	this->cleanup();
	char*  temp = new char[20];
	for(int i = 3 ; i < 5 ;i++)
	{
		sprintf(temp,this->m_spriteName,i);
		pAnimation->addSpriteFrame(frameCache->spriteFrameByName(temp));
	}
	this->runAction(CCRepeatForever::create(CCSequence::create(CCAnimate::create(pAnimation),CCDelayTime::create(2.0f),NULL)));
	delete []temp;
	m_State = HURTSTATE;
}

void MySprite::die()
{
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCAnimation *pAnimation = CCAnimation::create();
	pAnimation->setDelayPerUnit(1.0f);
	pAnimation->setRestoreOriginalFrame(false);
	
	char*  temp = new char[20];
	sprintf(temp,this->m_spriteName,5);
	this->cleanup();
	this->setDisplayFrame(frameCache->spriteFrameByName(temp));

	//	sprintf(temp,this->m_spriteName,i);
	pAnimation->addSpriteFrame(frameCache->spriteFrameByName(temp));
	//}

	CCCallFunc *callFunc1 = CCCallFunc::create(this,callfunc_selector(MySprite::releaseMysprite));

	this->runAction(CCSequence::create(CCAnimate::create(pAnimation),(CCActionInterval*)callFunc1,NULL));
	delete []temp;
	m_State = DIESTATE;

	//if (getType() == false){//如果是player死了
	if (m_targeit && m_callfunc){//死亡回调
			(m_targeit->*m_callfunc)();
	}
	//}else{
	Music_playEffect("sound145.mp3");
	//}
}

void MySprite::releaseMysprite()
{
	m_pMyworld->DestroyBody(spriteBody);
	this->removeFromParentAndCleanup(true);
}
/************************************************************************/
/* 设置 类型 true 是敌人 false 不是敌人                                                                     */
/************************************************************************/
void MySprite::setType(bool isEnemy)
{
	this->isEnemy = isEnemy;
}

bool MySprite::getType()
{
	return isEnemy;
}



MOSTERSTATE MySprite::getMosterState(){
	return m_State;
}

void MySprite::setCallbackFunc(cocos2d::CCObject*obj,SEL_CallFunc callfunc){

	m_targeit = obj;
	m_callfunc = callfunc;
}