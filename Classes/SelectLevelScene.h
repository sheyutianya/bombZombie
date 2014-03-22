#ifndef _SELECT_LEVEL_SCENE_H_
#define _SELECT_LEVEL_SCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"


class SelectLevelScene: public cocos2d::CCLayer{
public:
	virtual bool init();
	virtual void keyBackClicked();
	virtual void onExit();
	virtual void onEnter();

	static cocos2d::CCScene*scene();

	CREATE_FUNC(SelectLevelScene);

	void onStart(cocos2d::CCObject *pSender);
	void onBack(cocos2d::CCObject *pSender);
private:
	cocos2d::extension::UILayer *m_pUILayer;

};
#endif