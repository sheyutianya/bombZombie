/************************************************************************/
/*  静态全局变量*/
/************************************************************************/

#ifndef _SETTING_H_
#define _SETTING_H_

#include "cocos2d.h"
#include <vector>
using namespace std;


struct GOLD_STRUCT{
	cocos2d::CCSprite *goldSprite;
	int goldNum;
};

class Setting{
private:
	static Setting *m_setting;
	Setting();//私有构造函数
public:
	static Setting*GetSettingInstance();
	~Setting();

	//针对手机屏幕分辩率的手机设计，//
	//其他分辩率的手机自动缩放//
	static const int g_ResolusionWidth = 800;
	static const int g_ResolusionHeight = 480;

	//留的上边距和下边距//
	static const int g_TopMargin = 160;
	static const int g_BottomMargin = 160;

	//上边距和下边距//
	static const int g_LeftMargin = 0;
	static const int g_RightMargin = 0;


	//当前的关卡//
	static int g_icurrentGate;


	//声音开关//
	static bool g_MusicSwitch;
	static bool g_BgMusicSwitch;
	static bool g_ShookSwitch;
	static bool g_AudioSwitch ;

	//获取金币的数量
	static int g_iCoinNum;

	//获取图片路径//
	static const char *gettipsNumPicture(char name);
	static const char *getButtonNumPicture(char name);
	static const char *getRegularTipsPicture(char name);

	static cocos2d::CCArray *m_pGrondSpriteArray;//地面//
	static cocos2d::CCArray *g_pGroundPlantArray;//地面上的草坪//
	static cocos2d::CCArray *g_pMosterSpriteArray;//障碍物//
	static cocos2d::CCArray *g_pGoldSpriteArray;//金币//
	//static cocos2d::CCArray *g_pGoldObjectpool;//金币的对象池//
	static cocos2d::CCArray *g_pTreesSpriteArray;//树木//

	static std::vector<GOLD_STRUCT> m_goldStructVector;
};

#endif

