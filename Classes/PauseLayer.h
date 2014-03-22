#ifndef _PAUSE_LAYER_H_
#define _PAUSE_LAYER_H_

#include "cocos2d.h"
#include "Setting.h"
#include "cocos-ext.h"


class CPauseLayer:public cocos2d::CCLayerColor{
public:
	virtual bool init();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	void onResume(cocos2d::CCObject*pSender);
	void onBackSelectLayer(cocos2d::CCObject*pSender);
	void onReStart(cocos2d::CCObject*pSender);


	CREATE_FUNC(CPauseLayer);

private:
	Setting *m_pSetting;

};

#endif