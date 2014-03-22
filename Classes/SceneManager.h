#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

enum sceneTag
{
	kSceneTagMain = 0,
	kSceneModelSelect,
	kSceneTagSelectGate,
	kSceneTagGame,
	kSceneShenghuaSelectScene,
	KSceneTagShenHua,//Éú»¯³¡¾°
};

class SceneManager
{
public:
	static void goPlay(int sceneid = kSceneTagMain);
private:
	static void go(cocos2d::CCScene* scene);
	static void releaseCaches();
};

#endif