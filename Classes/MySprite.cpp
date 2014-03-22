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
/* ��ʼ��                                                                     */
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

    spriteBody = m_pMyworld->CreateBody(&bd);//���body��box2d world ��
	spriteBody->CreateFixture(&fixturedef);//

	return true;
}

/************************************************************************/
/*              ��ȡ����
  @param plistName �����plist�ļ�����
  @param spriteName ����ͼƬ������ ��ʽ ���� fire_%d.png
  @return��������Ľڵ�
  @mark ����һ������ ͼ �������� ״̬ ���� ����״̬ һ������ ״̬
   ���� 1-5������ fire_1.png fire_2.png ������
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

	//if (getType() == false){//�����player����
	if (m_targeit && m_callfunc){//�����ص�
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
/* ���� ���� true �ǵ��� false ���ǵ���                                                                     */
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