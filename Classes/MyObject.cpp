#include "MyObject.h"

MyObject::MyObject()
{

}

MyObject::~MyObject()
{
	//releaseMyObject();
}

MyObject* MyObject::getInstance(CCPoint point ,const char * spriteName,b2World *pMyworld,ObjectType type)
{
	MyObject* mySpriteNode = MyObject::create();
	mySpriteNode->m_pMyworld = pMyworld;
	mySpriteNode->initWithFile(spriteName);
	mySpriteNode->setAnchorPoint(ccp(0.5,0.5));
	mySpriteNode->setPosition(point);

	switch(type)
	{
	case WOOD:
		mySpriteNode->initPhySpriteWood();
		break;
	case IRON_V:
		mySpriteNode->initPhySpriteIronV();
		break;
	case IRON_H:
		mySpriteNode->initPhySpriteIronH();
		break;
	case TRIANGLE:
		mySpriteNode->initTriangle();
		break;
	case CIRCLE:
		mySpriteNode->initCircle();
		break;
	default: break;

	}
	
	return mySpriteNode;

}

/************************************************************************/
/* ��ʼ��������                                                                     */
/************************************************************************/
void MyObject::initTriangle()
{

	b2PolygonShape polygon;
	//polygon.m_radius = (float)this->getContentSize().width/PT_RATIO/2;
	//polygon.SetAsBox(this->getContentSize().width/PT_RATIO/2,this->getContentSize().height/PT_RATIO/2);
	this->setAnchorPoint(ccp(0,0));
	b2Vec2 vertices[3]; 
	
	vertices[2].Set(this->getContentSize().width/2/PT_RATIO,this->getContentSize().height/PT_RATIO); 
	vertices[1].Set(this->getContentSize().width/PT_RATIO,0); 
	vertices[0].Set(0,0); 

	polygon.Set(vertices,3);

	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 0.5f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.2f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)(this->getPosition().x / PT_RATIO),(float)(this->getPosition().y /PT_RATIO));
	bd.userData = this;

	spriteBody = m_pMyworld->CreateBody(&bd);//���body��box2d world ��
	//spriteBody->SetLinearVelocity(b2Vec2(0,-2));
	spriteBody->CreateFixture(&fixturedef);//
}

/************************************************************************/
/* ��ʼ��Բ��                                                                     */
/************************************************************************/
void MyObject::initCircle()
{
	b2CircleShape polygon;
	polygon.m_radius = (float)this->getContentSize().width/PT_RATIO/2;
	//polygon.SetAsBox(this->getContentSize().width/PT_RATIO/2,this->getContentSize().height/PT_RATIO/2);

	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 0.6f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.1f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)(this->getPosition().x / PT_RATIO),(float)(this->getPosition().y /PT_RATIO));
	bd.userData = this;

	spriteBody = m_pMyworld->CreateBody(&bd);//���body��box2d world ��
	//spriteBody->SetLinearVelocity(b2Vec2(0,-2));
	spriteBody->CreateFixture(&fixturedef);//
}


/************************************************************************/
/* ��ʼ������ ����                                                                     */
/************************************************************************/
void MyObject::initPhySpriteIronV()
{
	b2PolygonShape polygon;
	//polygon.m_radius = (float)this->getContentSize().width/PT_RATIO/2;
	//polygon.SetAsBox(this->getContentSize().width/PT_RATIO/2,this->getContentSize().height/PT_RATIO/2);
	this->setAnchorPoint(ccp(0,0));
	b2Vec2 vertices[4]; 
	vertices[3].Set(0,17.0/PT_RATIO); 
	vertices[2].Set(0,this->getContentSize().height/PT_RATIO); 
	vertices[1].Set(this->getContentSize().width/PT_RATIO,(this->getContentSize().height -17.0)/PT_RATIO); 
	vertices[0].Set(this->getContentSize().width/PT_RATIO,0); 

	polygon.Set(vertices,4);

	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 0.5f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.2f;
	b2BodyDef bd;
	bd.type = b2_kinematicBody;
	bd.position = b2Vec2((float)(this->getPosition().x / PT_RATIO),(float)(this->getPosition().y /PT_RATIO));
	bd.userData = this;

	spriteBody = m_pMyworld->CreateBody(&bd);//���body��box2d world ��
	spriteBody->CreateFixture(&fixturedef);//
}

void MyObject::initPhySpriteIronH()
{
	b2PolygonShape polygon;
	//polygon.m_radius = (float)this->getContentSize().width/PT_RATIO/2;
	//polygon.SetAsBox(this->getContentSize().width/PT_RATIO/2,this->getContentSize().height/PT_RATIO/2);
	this->setAnchorPoint(ccp(0,0));
	b2Vec2 vertices[4]; 
	vertices[3].Set(0,0); 
	vertices[2].Set(22.0/PT_RATIO,this->getContentSize().height/PT_RATIO); 
	vertices[1].Set(this->getContentSize().width/PT_RATIO,this->getContentSize().height/PT_RATIO); 
	vertices[0].Set((this->getContentSize().width - 22.0)/PT_RATIO,0); 

	polygon.Set(vertices,4);

	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 0.5f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.2f;
	b2BodyDef bd;
	bd.type = b2_kinematicBody;
	bd.position = b2Vec2((float)(this->getPosition().x / PT_RATIO),(float)(this->getPosition().y /PT_RATIO));
	bd.userData = this;

	spriteBody = m_pMyworld->CreateBody(&bd);//���body��box2d world ��
	spriteBody->CreateFixture(&fixturedef);//
}


/************************************************************************/
/* ���߽�λ��                                                                     */
/************************************************************************/
void MyObject::checkBound(float time)
{
	if (isVect)
	{
		if(this->getPosition().y > top_bottom.x - this->getContentSize().height)
		{
			spriteBody->SetLinearVelocity(b2Vec2(-speed.x,-speed.y));
		}else if (this->getPosition().y <  top_bottom.y )
		{
			spriteBody->SetLinearVelocity(b2Vec2(speed.x,speed.y));
		}
	}else
	{
		if(this->getPosition().x < left_right.x )
		{
			spriteBody->SetLinearVelocity(b2Vec2(speed.x,speed.y));
		}else if (this->getPosition().x >  left_right.y - this->getContentSize().width )
		{
			spriteBody->SetLinearVelocity(b2Vec2(-speed.x,-speed.y));
		}
	}
	
}

/************************************************************************/
/* ���� �˶� ���������
@param speed �ٶ�(0,1)���� �ƶ� �ٶ�Ϊ 0  ���� Ϊÿ�� �ƶ�1��
@param top ����  ���˶����� ���λ��
@param bottom �� �ұ� �˶��������λ��
*/
/************************************************************************/
void MyObject::setProperties(CCPoint speed,CCPoint top_bottom,CCPoint left_right)
{
	this->speed = speed;
	this->top_bottom = top_bottom;
	this->left_right = left_right;
	if (!left_right.equals(ccp(0,0)))
	{
		isVect = false;
	 spriteBody->SetLinearVelocity(b2Vec2(-2,0));
	}else
	{
		isVect = true;
		spriteBody->SetLinearVelocity(b2Vec2(0,-2));
	}
	this->schedule(schedule_selector(MyObject::checkBound)); 

}

/************************************************************************/
/* ��ʼ�� ��ľ��                                                                     */
/************************************************************************/
void MyObject::initPhySpriteWood()
{
	b2PolygonShape polygon;
	//polygon.m_radius = (float)this->getContentSize().width/PT_RATIO/2;
	polygon.SetAsBox(this->getContentSize().width/PT_RATIO/2,this->getContentSize().height/PT_RATIO/2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 0.5f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.2f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)(this->getPosition().x / PT_RATIO),(float)(this->getPosition().y /PT_RATIO));
	bd.userData = this;


	spriteBody = m_pMyworld->CreateBody(&bd);//���body��box2d world ��
	spriteBody->CreateFixture(&fixturedef);//
}

void MyObject::releaseMyObject()
{
	if (m_pMyworld != NULL)
	{
		m_pMyworld->DestroyBody(spriteBody);
	}
	
}

