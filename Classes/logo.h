#ifndef _MY_LOGO_
#define _MY_LOGO_

#include "cocos2d.h"

class logo:public cocos2d::CCLayer
{
public:
    virtual bool init();
    void replace();
    CREATE_FUNC(logo);
};
#endif /* defined(__tsDemo__logo__) */
