#include "Setting.h"

USING_NS_CC;

Setting* Setting::m_setting = new Setting();


int Setting::g_icurrentGate = 1;//当前关卡//

//声音开关//
bool Setting::g_MusicSwitch = false;
bool Setting::g_AudioSwitch = false;
bool Setting::g_BgMusicSwitch = false;

//获取的金币数量//
int Setting::g_iCoinNum = 0;

CCArray *Setting::m_pGrondSpriteArray = NULL;
CCArray *Setting::g_pMosterSpriteArray = NULL;
CCArray *Setting::g_pGroundPlantArray = NULL;
CCArray *Setting::g_pGoldSpriteArray = NULL;
CCArray *Setting::g_pTreesSpriteArray = NULL;
vector<GOLD_STRUCT> Setting::m_goldStructVector;


Setting::Setting(){
	m_setting = this;
}

Setting::~Setting(){

	m_setting = NULL;
}

Setting*Setting::GetSettingInstance(){
	return m_setting;
}

const char* Setting::gettipsNumPicture(char name){
	const char * rChar = new char[30];
	switch(name){
	case '0':
		rChar = "0.png";
		break;
	case '1':
		rChar = "1.png";
		break;
	case '2':
		rChar = "2.png";
		break;
	case '3':
		rChar = "3.png";
		break;
	case '4':
		rChar = "4.png";
		break;
	case '5':
		rChar = "5.png";
		break;
	case '6':
		rChar = "6.png";
		break;
	case '7':
		rChar = "7.png";
		break;
	case '8':
		rChar = "8.png";
		break;
	case '9':
		rChar = "9.png";
		break;
	case '.':
		rChar = "..png";
		break;
	case '?':
		rChar = "10.png";
		break;
	case '+':
		rChar = "+.png";
		break;
	case '-':
		rChar = "-.png";
		break;
	case '=':
		rChar = "=.png";
		break;
	default:
		rChar = "NULL.png";
		break;
	}
	return rChar;
}

const char* Setting::getButtonNumPicture(char name){
	const char * rChar = new char[30];
	switch(name){
	case '0':
		rChar = "02.png";
		break;
	case '1':
		rChar = "12.png";
		break;
	case '2':
		rChar = "22.png";
		break;
	case '3':
		rChar = "32.png";
		break;
	case '4':
		rChar = "42.png";
		break;
	case '5':
		rChar = "52.png";
		break;
	case '6':
		rChar = "62.png";
		break;
	case '7':
		rChar = "72.png";
		break;
	case '8':
		rChar = "82.png";
		break;
	case '9':
		rChar = "92.png";
		break;
	case '.':
		rChar = ".2.png";
		break;
	case '?':
		rChar = "10.png";
		break;
	case '+':
		rChar = "+2.png";
		break;
	case '-':
		rChar = "-2.png";
		break;
	case '<':
		rChar = "xiaoyu.png";
		break;
	case '>':
		rChar = "dayu.png";
		break;
	case '=':
		rChar = "=2.png";
		break;
	case 'a':
		rChar = "frog222.png";
		break;
	case 'b':
		rChar = "hedgehog222.png";
		break;
	case 'c':
		rChar = "panda222.png";
		break;
	case 'd':
		rChar = "pig222.png";
		break;
	default:
		rChar = rChar = "NULL.png";
		break;
	}
	return rChar;
}

const char* Setting::getRegularTipsPicture(char name){
	const char * rChar = new char[30];
	switch(name){
	case '1':
		rChar = "frog22.png";
		break;
	case '2':
		rChar = "hedgehog22.png";
		break;
	case '3':
		rChar = "panda22.png";
		break;
	case '4':
		rChar = "pig22.png";
		break;
	case '?':
		rChar = "102.png";
		break;
	default:
		rChar = "NULL.png";
		break;
	}
	return rChar;
}

