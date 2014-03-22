#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Setting.h"

#include "String"
using namespace std;
#define PT_RATIO 32
using namespace CocosDenshion;
using namespace cocos2d;
#define PI  3.1415926
typedef std::vector<std::string> strArray;

//对字符串进行加密和解密//
inline void encode(string &str){
	for(int i = 0 ; i < str.length() ; i++){
		int ch = str[i];
		ch = ch +10;
		str[i] = ch;
	}
}

inline void decode(string &str){
	for(int i = 0 ; i < str.length() ; i++){
		int ch = str[i];
		ch = ch -10;
		str[i] = ch;
	}
}

/************************************************************************/
/* 定义数据存储                                                         */
/************************************************************************/
#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey  
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey  
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey  
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey  
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey  
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey  
#define SaveFlush CCUserDefault::sharedUserDefault()->flush


/************************************************************************/
/* 数据校验算法                                                                     */
/************************************************************************/
#define Encode(num)  (((num+123456789)&0xffff) + (((num+123456789)>>4) & 0xffff))


/************************************************************************/
/* 保存校验数据                                                          */
/************************************************************************/
#define  SaveNumWithEncode(name,num){ SaveIntegerToXML(name,num);\
	CCString *pstr = CCString::createWithFormat("%s_CHECK",name);\
	SaveIntegerToXML(pstr->getCString(),Encode(num));}            


/************************************************************************/
/* 获取 校验 后的数据 如果数据 被修改 返回 0                                                                     */
/************************************************************************/          
#define getNumWithDecode(name) Encode(LoadIntegerFromXML(name,0)) == \
	LoadIntegerFromXML((CCString::createWithFormat("%s_CHECK",name))->getCString(),0) ? LoadIntegerFromXML(name,0):0


//预加载背景音乐//
inline void Music_PreLoadMusic(CCString path){

	CCString *pstr = CCString::createWithFormat("music/%s",path.getCString());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(pstr->getCString());
}

//预加载音效文件
inline void Music_PreLoadEffect(CCString path) {

	CCString *pstr = CCString::createWithFormat("music/%s",path.getCString());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(pstr->getCString());
}

//播放音效
inline void Music_playEffect(CCString path){

	if (Setting::g_MusicSwitch){
		CCString *pstr = CCString::createWithFormat("music/%s",path.getCString());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pstr->getCString());
		
	}
}

//播放 背景音乐
inline void Music_playBackgroundMusic(CCString path){

	if (Setting::g_BgMusicSwitch){
		CCString *pstr = CCString::createWithFormat("music/%s",path.getCString());
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pstr->getCString(),true);
	}
}

//停止背景音乐
inline void Music_stopBackgroundMusic(){

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}


//停止音效
inline void Music_stopAllEffect(){

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

//停止所有音乐
inline void Music_stopAlldMusic(){ 

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}


//暂停 所有音效
inline void Music_Pause() {

	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}


//恢复所有音效
inline void Music_Resume(){

	if (Setting::g_BgMusicSwitch){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
} 

//设置 背景音乐 大小
inline void Music_BackgroundVolume(int num) {

	if (Setting::g_BgMusicSwitch){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(num);
	}
}



/************************************************************************/
/* 解析坐标                                                                     */
/************************************************************************/
// string toolkit
 inline void Mysplit(std::string src, const char token, strArray& vect)
{
	int nend=0;
	int nbegin=0;
	while(nend != -1)
	{
		nend = src.find(token, nbegin);
		if(nend == -1)
			vect.push_back(src.substr(nbegin, src.length()-nbegin));
		else
			vect.push_back(src.substr(nbegin, nend-nbegin));
		//CCLOG("%s",src.substr(nbegin, nend-nbegin).c_str());
		nbegin = nend + 1;//strlen(token);
	}
}

 inline void split(std::string src, const char* token, strArray& vect)
 {
	 int nend=0;
	 int nbegin=0;
	 while(nend != -1)
	 {
		 nend = src.find(token, nbegin);
		 if(nend == -1)
			 vect.push_back(src.substr(nbegin, src.length()-nbegin));
		 else
			 vect.push_back(src.substr(nbegin, nend-nbegin));
		 nbegin = nend + strlen(token);
	 }
 }


//本地化语言//
const char* getStringForLanguage(const char * name);
CCSprite* getSpriteForLanguage(const char * name);

//截屏功能
cocos2d::CCImage *saveScreenToImage(bool upsideDown);

//坐标解析
CCPoint PointFromString(const char* pszContent);
CCPoint PointFromString2(const char* pszContent);
CCPoint PointFromString3(const char* pszContent);

class MyGlobal{
public:
	static long  getcurrentTime();
	static int random(int Max);
	static int testCount;
	

};


#endif