#ifndef _GAMESCENE_LAYER_H_
#define _GAMESCENE_LAYER_H_

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "GLES-Render.h"
#include "Global.h"
#include "MySprite.h"
#include "MyContactListener.h"
#include "MyObject.h"

class  GameSceneLayer:public cocos2d::CCLayer
{
public:
	GameSceneLayer();
	~GameSceneLayer();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();

	virtual void draw();
	static cocos2d::CCScene *scene();

	void gameFaild();
	void gameVictory();

	CREATE_FUNC(GameSceneLayer);

	void tick(float dt);

public:
	void Bombing(cocos2d::CCNode *node);//炸弹爆炸的回调
	void doBomb(b2Vec2 pos);
	void addBoxbodyFromSprite(cocos2d::CCNode *sprite,b2Vec2 vec);
	void addStaicBodyFromSprite(cocos2d::CCNode *sprite);
	void desdoryBodyBySprite(cocos2d::CCSprite* sprite);

private:
	b2World *m_pMyworld;
	//GLESDebugDraw *m_pDebugDraw;
	MyContactListener* m_pMyContactListener; // Contact event listener


	CCTMXTiledMap *pTiledMap;
	void initTiledMap();

	bool m_bDrawlineFlag;
	void addFire(CCPoint point);
	cocos2d::CCPoint m_LineStartpos,m_LineEndpos;

	int m_iResuduoMonsterNum; //剩余的怪物数量
	bool gamefinish;
	long lasttime;//记录上次点击的时间 ，每秒只能发射 一颗炮弹
	void onPause(CCObject *pSender);
private:
	cocos2d::CCAnimate *m_pCannonAnimate;
	cocos2d::CCAnimate *m_pBatteryAnimate;

private:
	static const int m_iMosterSpriteTag = 1002;
	static const int m_iFireSpriteTag = 1003;
	static const int m_iPlayerSpriteTag = 1004;

	static const int m_iCannonSpriteTag = 1005;
	static const int m_iBatterySpriteTag = 1006;
	static const int m_iCannonAnimateTag = 1007;

	static const int m_iPauseLayerTag = 1008;

};

#endif
