#ifndef _MYSPRITE_H_
#define _MYSPRITE_H_

#include "cocos2d.h"
#include "Global.h"
#include <Box2D/Box2D.h>
USING_NS_CC;

enum MOSTERSTATE
{
	NORMAL = 0,
	HURTSTATE,
	DIESTATE
};

class MySprite :public CCSprite
{
public:
	MySprite();
	~MySprite();
	 static MySprite* getInstance(CCPoint point,const char* plistName ,const char * spriteName,b2World *pMyworld);
	 void hurt();
	 void die();
	 void setType(bool);
	 bool getType();
	 MOSTERSTATE getMosterState();
	CREATE_FUNC(MySprite);

	void setCallbackFunc(cocos2d::CCObject*obj,SEL_CallFunc callfunc);

protected:
	cocos2d::CCObject*m_targeit;
	cocos2d::SEL_CallFunc m_callfunc;

private:
	bool initPhySprite();
	const char* m_spriteName;
	void releaseMysprite();
	b2World *m_pMyworld;
	b2Body* spriteBody;
	bool  isEnemy;// «∑Ò «µ–»À
	MOSTERSTATE m_State;
};

#endif