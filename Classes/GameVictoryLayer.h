#ifndef _GAMEVICTORY_LAYER_H_
#define _GAMEVICTORY_LAYER_H_

#include "cocos2d.h"
#include "Setting.h"
#include "cocos-ext.h"

class CGameVictoryLayer:public cocos2d::CCLayerColor{
public:
	virtual bool init();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

	void menuCloseCallback(cocos2d::CCObject* pSender);
	void menuRestart(cocos2d::CCObject*pSender);
	void menuSelectedLayer(cocos2d::CCObject*pSender);
	
	virtual void keyBackClicked();
	CREATE_FUNC(CGameVictoryLayer);

	//添加的粒子个数//
	int m_iparticalNum;
private:
    Setting *m_Setting;
	void step(float dt);
};

#endif