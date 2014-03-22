#include "SceneManager.h"
#include "MainScene.h"
#include "HelloWorldScene.h"
#include "GameSceneLayer.h"
#include "SelectLevelScene.h"


USING_NS_CC;

void SceneManager::goPlay(int sceneid)
{
	CCScene* scene;
	switch (sceneid) {
	case kSceneTagMain:
		scene = CMainScene::scene();
		break;
	case kSceneTagSelectGate:
		scene = SelectLevelScene::scene();
		break;
	case kSceneTagGame:
		scene = GameSceneLayer::scene();
		break;
	case kSceneModelSelect:
		//scene = ModelSelectScene::scene();
		break;
	case kSceneShenghuaSelectScene:
		//scene = ShenghuaSelectScene::scene();
		break;
	case KSceneTagShenHua:
		//scene = BiochemicalScene::scene();
		break;
	default:
		break;
	}
	SceneManager::go(scene);
}

void SceneManager::go(CCScene* scene)
{
	CCDirector* director = CCDirector::sharedDirector();

	SceneManager::releaseCaches();

	if (director->getRunningScene())
	{
		director->replaceScene(scene);
		//CCLog("0111");
	}
	else
	{
		director->runWithScene(scene);
	}
}


void SceneManager::releaseCaches(){

	CCAnimationCache::purgeSharedAnimationCache();

	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}