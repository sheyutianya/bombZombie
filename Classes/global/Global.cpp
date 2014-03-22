#include "Global.h"

 int MyGlobal::testCount = 0;
/************************************************************************/
/* 根据本地化语言获取字符串                                                                     */
/************************************************************************/
const char* getStringForLanguage(const char * name)
{
	ccLanguageType nType = CCApplication::sharedApplication()->getCurrentLanguage();  
	//字典   
	CCDictionary *pDic;  

	switch (nType)
	{
	case kLanguageChinese:
		pDic = CCDictionary::createWithContentsOfFile("language/cn.xml");  break;
	case kLanguageFrench:
		pDic = CCDictionary::createWithContentsOfFile("language/fr.xml");  break;
	case kLanguageItalian:
		pDic = CCDictionary::createWithContentsOfFile("language/it.xml");  break;
	case kLanguageGerman:
		pDic = CCDictionary::createWithContentsOfFile("language/ger.xml");  break;
	case kLanguageSpanish:
		pDic = CCDictionary::createWithContentsOfFile("language/sp.xml");  break;
	case kLanguageRussian:
		pDic = CCDictionary::createWithContentsOfFile("language/ru.xml");  break;
	case kLanguageKorean:
		pDic = CCDictionary::createWithContentsOfFile("language/kor.xml");  break;
	case kLanguageJapanese:
		pDic = CCDictionary::createWithContentsOfFile("language/jp.xml");  break;
	case kLanguageArabic:
		pDic = CCDictionary::createWithContentsOfFile("language/ar.xml");  break;
	default:
		pDic = CCDictionary::createWithContentsOfFile("language/en.xml");  break;
	}
	//返回key对应的value   
	return (pDic -> valueForKey(name))->getCString();  
}

/************************************************************************/
/* 根据本地化语言创建CCSprite                                                                     */
/************************************************************************/
CCSprite *getSpriteForLanguage(const char * name){

    CCString tempstr;
	ccLanguageType nType = CCApplication::sharedApplication()->getCurrentLanguage(); 
	switch(nType){
		case kLanguageChinese:
			tempstr.m_sString = "ui/chinese"+(*name);
			break;
		default:
			tempstr.m_sString = "ui/english"+(*name);
			break;
	}
	return CCSprite::create(tempstr.getCString());
}

long MyGlobal::getcurrentTime()  
{ 
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	return (now.tv_sec * 1000 + now.tv_usec / 1000); 

} 


/******************************* *****************************************/
/* 产生随机数 0 -Max              最大值 1000                                                        */
/************************************************************************/
int MyGlobal::random(int Max)
{   
	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		return (CCRANDOM_0_1()*Max);
	}else{
		srand( getcurrentTime()); 
		return ((int)(CCRANDOM_0_1()*100) + getcurrentTime() % 10000)%Max;
	}
}

unsigned char screenBuffer[1024*1024*8];
/************************************************************************/
/* 获取屏幕截图                                                                     */
/************************************************************************/
CCImage *saveScreenToImage(bool upsideDown){
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
	int w = winSize.width;
	int h = winSize.height;
	int myDataLength = w * h * 4;

	GLubyte *buffer = screenBuffer;
	glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,buffer);

	CCImage *image = new CCImage();

	if (upsideDown){

		GLubyte *buffer2 = (GLubyte*) malloc(myDataLength);
		for (int y = 0 ; y< h ; y++){
			for (int x = 0 ; x< w*4 ; x++){
				buffer2[(h - 1 - y) * w * 4 +x] = buffer[y * 4 * w + x];
			}
		}

		bool ok = image->initWithImageData(buffer2,myDataLength,
			CCImage::kFmtRawData,w,h);
		free(buffer2);

	}else{
		bool ok = image->initWithImageData(buffer,myDataLength,
			CCImage::kFmtRawData, w , h);
	}
	return image;
}




/************************************************************************/
/* 使用&作为分隔符                                                                     */
/************************************************************************/
// first, judge whether the form of the string like this: {x,y}
// if the form is right,the string will be split into the parameter strs;
// or the parameter strs will be empty.
// if the form is right return true,else return false.
static bool mysplitWithForm(const char* pStr, strArray& strs)
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!pStr);

		// string is empty
		std::string content = pStr;
		CC_BREAK_IF(content.length() == 0);

		int nPosLeft  = content.find('{');
		int nPosRight = content.find('}');

		// don't have '{' and '}'
		CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
		// '}' is before '{'
		CC_BREAK_IF(nPosLeft > nPosRight);

		std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
		// nothing between '{' and '}'
		CC_BREAK_IF(pointStr.length() == 0);

		int nPos1 = pointStr.find('{');
		int nPos2 = pointStr.find('}');
		// contain '{' or '}' 
		CC_BREAK_IF(nPos1 != (int)std::string::npos || nPos2 != (int)std::string::npos);

		split(pointStr, "&", strs);
		if (strs.size() != 2 || strs[0].length() == 0 || strs[1].length() == 0)
		{
			strs.clear();
			break;
		}

		bRet = true;
	} while (0);

	return bRet;
}


CCPoint PointFromString(const char* pszContent)
{
	CCPoint ret = CCPointZero;

	do 
	{
		strArray strs;
		CC_BREAK_IF(!mysplitWithForm(pszContent, strs));

		float x = (float) atof(strs[0].c_str());
		float y = (float) atof(strs[1].c_str());

		ret = CCPointMake(x, y);
	} while (0);

	return ret;
}

/************************************************************************/
/* 0,123 形式                                                                     */
/************************************************************************/
CCPoint PointFromString2(const char* pszContent)
{
	CCPoint ret = CCPointZero;
	
	char* str = const_cast<char*>(pszContent);
	char *str1 = new char[strlen(str)];
	strncpy(str1,str,strlen(str));
	do 
	{
		char* strtokchar = strtok(str1,",");
		float x = (float) atof(strtokchar);
		strtokchar = strtok(NULL,",");
		float y = (float) atof(strtokchar);

		ret = CCPointMake(x, y);
	} while (0);

	delete []str1;
	return ret;
}

/************************************************************************/
/* 0,123 形式                                                                     */
/************************************************************************/
//CCPoint 



