#ifndef __MY_OBJECT__
#define __MY_OBJECT__

#include "cocos2d.h"
#include "Global.h"
#include <Box2D/Box2D.h>
USING_NS_CC;

class MyObject :public CCSprite
{
public:
	enum ObjectType{
		WOOD =0,
		IRON_V,
		IRON_H,
		TRIANGLE,
		CIRCLE,
	};
	MyObject();
	~MyObject();
	CREATE_FUNC(MyObject);
	static MyObject* getInstance(CCPoint point ,const char * spriteName,b2World *pMyworld,ObjectType type);
	 void initPhySpriteWood() ;
	 void initPhySpriteIronV();
	 void initPhySpriteIronH();
	 void initTriangle();//初始化 三角形
	 void initCircle();//初始化圆形
	 void releaseMyObject();
	 void checkBound(float time);
	 void setProperties(CCPoint speed,CCPoint top_bottom,CCPoint left_right);
private:
	CCPoint speed,top_bottom,left_right;
	b2World *m_pMyworld;
	b2Body* spriteBody;
	bool isVect;//是否是垂直

};



#endif