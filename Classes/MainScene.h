#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "pthread.h"
#include "Setting.h"

static bool g_loadcomplete = false;

class CMainScene: public cocos2d::CCLayer{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void keyBackClicked();

	static cocos2d::CCScene*scene();

    //menu callback Function
	void onStart(cocos2d::CCObject*pSender);
	void onHelp(cocos2d::CCObject *pSender);
	void onMusicSwitch(cocos2d::CCObject *pSender);
	void onAudioSwitch(cocos2d::CCObject *pSender);
	void loadingCallBack(cocos2d::CCObject *obj);
	void onStartRaceMode(cocos2d::CCObject *pSender);


	CREATE_FUNC(CMainScene);

	void update(float delta);

private:
	int m_nNumberOfSprites;
	int m_nNumberOfLoadedSprites;


	void initScene();

private:
	pthread_t m_pid;//线程ID//
	static void*updataIfo(void *args);//线程函数//
	Setting *m_Setting;
};
#endif