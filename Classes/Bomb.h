#ifndef _BOMB_H_
#define _BOMB_H_

#include "cocos2d.h"

class Bomb:public cocos2d::CCLayer{
public:
	Bomb();
	~Bomb();

	virtual bool init();

	//CCSYNTHE
	CC_PROPERTY(cocos2d::CCPoint,m_SpritePos,SpritePos);

	
	CREATE_FUNC(Bomb);

	//update 

	void updateLable(float dt);
	void tickTimer(float dt);

	//call backfunction
	void ExplodeFinish(cocos2d::CCObject *obj);

public:
	cocos2d::CCSprite *getTheSprite();
	void startBombing();
	void setCallbackFunc(cocos2d::CCObject* target, cocos2d::SEL_CallFuncN callfun);

private:
	cocos2d::CCSprite*m_pSprite;//文理精灵
	int m_iTickTimer;
	cocos2d::CCAnimate *m_pExplodeAnimate;

	cocos2d::CCObject* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;

	static const int m_iTextLabelTag = 100;
	bool isstartbool;//是否 启动炸弹定时
};


#endif