#include "GameSceneLayer.h"
#include "Bomb.h"
#include "GameFaildLayer.h"
#include "GameVictoryLayer.h"
#include "PauseLayer.h"

#define PT_RATIO 32
USING_NS_CC;

//使用tag来标记物体类型
//1001表示炸弹

GameSceneLayer::GameSceneLayer():gamefinish(false)
,m_pCannonAnimate(NULL)
,m_pBatteryAnimate(NULL){

}

GameSceneLayer::~GameSceneLayer(){

	delete m_pMyworld;
	//delete m_pDebugDraw;
	m_pMyContactListener->clearContact();
	//CCLOG("mcount= %d",MyContactListener::count);
	delete m_pMyContactListener;

	m_pCannonAnimate->release();
	m_pBatteryAnimate->release();
}

CCScene *GameSceneLayer::scene(){

	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameSceneLayer *layer = GameSceneLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameSceneLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		setKeypadEnabled(true);

		//CCLOG("init1");
		//创建物理世界
		b2Vec2 gravity;
		gravity.Set(0.0f,-10.0f);
		m_pMyworld = new b2World(gravity);
		m_pMyworld->SetAllowSleeping(true);

		m_pMyContactListener = new MyContactListener();
		m_pMyworld->SetContactListener(m_pMyContactListener);

		//m_pDebugDraw = new GLESDebugDraw( PT_RATIO );
		//m_pMyworld->SetDebugDraw(m_pDebugDraw);
		//uint32 flags = 0;
		//flags += b2Draw::e_shapeBit;
		//flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		//m_pDebugDraw->SetFlags(flags);

		//创建一个地面
		//b2BodyDef groundboxDef;
		////groundboxDef.

		//b2Body *groundBody = m_pMyworld->CreateBody(&groundboxDef);
	
		//b2EdgeShape groundbox;
		////groundbox.m_type
		//groundbox.Set(b2Vec2(0,220/32),b2Vec2(640.0f/32,220/32));
		//groundBody->CreateFixture(&groundbox,0);

		//groundbox.Set(b2Vec2(0,0/32),b2Vec2(0,480.0f/32));
		//groundBody->CreateFixture(&groundbox,0);

		//groundbox.Set(b2Vec2(640.0f/32,0/32),b2Vec2(640.0f/32,480.0f/32));
		//groundBody->CreateFixture(&groundbox,0);

		//groundbox.Set(b2Vec2(0,480.0f/32),b2Vec2(640.0f/32,480.0f/32));
		//groundBody->CreateFixture(&groundbox,0);

		//创建几个动态刚体

		//for (int i = 0; i < 4; i++){

		//	CCSprite *sprite = CCSprite::create("image 277.png");
		//	sprite->setPosition(ccp(200+100*i,200));
		//	addChild(sprite);
		//	addBoxbodyFromSprite(sprite);
		//	//b2BodyDef bodydef;
		//	//bodydef.type = b2_dynamicBody;
		//	//bodydef.position.Set(200/32+100/32*i,200/32);

		//	//b2Body *body = m_pMyworld->CreateBody(&bodydef);

		//	//b2PolygonShape dynamicbox;
		//	//dynamicbox.SetAsBox(0.5f,0.5f);

		//	//b2FixtureDef fixturedef;
		//	//fixturedef.shape = &dynamicbox;
		//	//fixturedef.density = 1.0f;
		//	//fixturedef.friction = 0.3f;
		//	//fixturedef.restitution = 0.5f;
		//	//body->CreateFixture(&fixturedef);
		//}

		//init 
		CCSprite* bg;
		if (Setting::g_icurrentGate < 10)
		{
			 bg = CCSprite::create("gamebg_1.png");
		}else
		{
		  bg = CCSprite::create("gamebg_2.png");
		}
		bg->setPosition(ccp(Setting::g_ResolusionWidth/2,Setting::g_ResolusionHeight/2));
		addChild(bg,-1);

		m_bDrawlineFlag = false;
		m_LineEndpos = m_LineStartpos = ccp(105,155);

		m_iResuduoMonsterNum = 0;
		//CCLOG("init2");
		initTiledMap();


		//添加一个炮台
		CCSprite*cannonSprite = CCSprite::createWithSpriteFrameName("cannon.png");
		addChild(cannonSprite,1);
		cannonSprite->setPosition(ccp(105,155));
		cannonSprite->setTag(m_iCannonSpriteTag);

		CCSprite*batterySprite = CCSprite::createWithSpriteFrameName("battery.png");
		addChild(batterySprite,1);
		batterySprite->setPosition(ccp(100,140));
		batterySprite->setTag(m_iBatterySpriteTag);

		CCAnimation *pCannonAnimation = CCAnimation::create();
		CCSpriteFrameCache *framecache = CCSpriteFrameCache::sharedSpriteFrameCache();
		for(int i = 0 ; i < 5 ; i++){
			pCannonAnimation->addSpriteFrame(framecache->spriteFrameByName(CCString::createWithFormat("cannon%d.png",i+1)->getCString()));
		}
		pCannonAnimation->setDelayPerUnit(0.08f);
		pCannonAnimation->setRestoreOriginalFrame(true);
		m_pCannonAnimate = CCAnimate::create(pCannonAnimation);
		m_pCannonAnimate->retain();
		m_pCannonAnimate->setTag(m_iCannonAnimateTag);

		CCAnimation *pBatteryAnimation = CCAnimation::create();
		for (int i = 0 ; i < 3 ; i++)	{
			pBatteryAnimation->addSpriteFrame(framecache->spriteFrameByName(CCString::createWithFormat("battery%d.png",i+1)->getCString()));
		}
		pBatteryAnimation->setDelayPerUnit(0.08f);
		pBatteryAnimation->setRestoreOriginalFrame(true);
		m_pBatteryAnimate = CCAnimate::create(pBatteryAnimation);
		m_pBatteryAnimate->retain();


		CCMenuItem* menuItem = CCMenuItemImage::create("button/btn_pause.png","button/btn_pause.png",this,menu_selector(GameSceneLayer::onPause));
		menuItem->setPosition(ccp(60,460));
		menuItem->setScale(0.5f,0.5f);
		CCMenu* menu = CCMenu::create(menuItem,NULL);
		menu->setPosition(ccp(0,0));
        menu->setAnchorPoint(ccp(0,0));
		this->addChild(menu,10);



		schedule(schedule_selector(GameSceneLayer::tick));

		bRet = true;

		
	} while (0);
	return bRet;
}

void GameSceneLayer::keyBackClicked(){
	if (getChildByTag(m_iPauseLayerTag)){
		this->removeChildByTag(m_iPauseLayerTag);
	}else{
		CPauseLayer *layer = CPauseLayer::create();
		addChild(layer,100);
		layer->setTag(m_iPauseLayerTag);
	}
}

void GameSceneLayer::onPause(CCObject *pSender)
{
	//showSplashAd();
	keyBackClicked();
}


void GameSceneLayer::initTiledMap()
{
	pTiledMap = CCTMXTiledMap::create(CCString::createWithFormat("map/lev%d.tmx",Setting::g_icurrentGate)->getCString());
	//pTiledMap = CCTMXTiledMap::create("map/lev4.tmx");
	pTiledMap->setTag(100);
	pTiledMap->setAnchorPoint(ccp(0,0));
	pTiledMap->setPosition(ccp(0,0));
	this->addChild(pTiledMap,0);

	//b2BodyDef groundBodydef;
	//groundBodydef.position.Set(0,0);
	//b2Body *groundBody = m_pMyworld->CreateBody(&groundBodydef);
	//b2EdgeShape groundbox;


	CCTMXObjectGroup *pgroup =  pTiledMap->objectGroupNamed("ground");
	CCArray *pChildrenArray = pgroup->getObjects();
	CCDictionary* dict = NULL;
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(pChildrenArray,pObject)
	{
		dict = (CCDictionary *)pObject;
		if(!dict)
			break;
		const char* key = "x";
		int x = ((CCString*)dict->objectForKey(key))->intValue();
		key = "y";
		int y = ((CCString*)dict->objectForKey(key))->intValue();
		y = Setting::g_ResolusionHeight -y;
		key = "polylinePoints";
		CCString* polyLine = ((CCString*)dict->objectForKey(key));
		vector<string> ployLines;
		split(polyLine->m_sString," ",ployLines);
		CCPoint pointFirst = ccp(0,0);
	    for(int i = 0; i < ployLines.size() ;i++ )
		{
			 string str = ployLines[i];
			 CCPoint point = PointFromString2(str.c_str());
             point.x+= x;
			 point.y += y;
			 point.y = Setting::g_ResolusionHeight - point.y;//Tilemap 坐标 转换
			 if(i == 0 )
			 {
				 pointFirst = point;
			 }
			 CCPoint point1;
			 if((i+1) < ployLines.size())
			 {
				 str = ployLines[i+1];
				 point1 = PointFromString2(str.c_str());
			     point1.x+= x;
			     point1.y += y;
			     point1.y = Setting::g_ResolusionHeight - point1.y;//Tilemap 坐标 转换
			 }else{
                  point1 = pointFirst;
			 }

			 //坐标修正
			 if (abs(point.x - point1.x) < 5) {
				 point1.x = point.x;
			 }
			 if (abs(point.y - point1.y) < 5) {
				 point1.y = point.y;
			 }

			b2BodyDef groundBodydef;
			groundBodydef.position.Set(0,0);
			b2Body *groundBody = m_pMyworld->CreateBody(&groundBodydef);
			b2EdgeShape groundbox;
			groundbox.Set(b2Vec2(point.x/PT_RATIO,point.y/PT_RATIO),b2Vec2(point1.x/PT_RATIO,point1.y/PT_RATIO));
			groundBody->CreateFixture(&groundbox,0);
		}
		for(int j = 0; j< ployLines.size();j++)
		{
			ployLines[j].clear();
		}
		ployLines.clear();
	}

	/************************************************************************/
	/* 解析tmp上的物体                                                                     */
	/************************************************************************/
	pgroup = pTiledMap->objectGroupNamed("object");
	pChildrenArray = pgroup->getObjects();
	//CCDictionary* dict = NULL;
	//CCObject *pObject = NULL;
	CCARRAY_FOREACH(pChildrenArray,pObject)
	{
		dict = (CCDictionary *)pObject;
		if(!dict)
			break;
		const char* key = "name";
		CCString* name = (CCString*)dict->objectForKey(key);
		if(name->isEqual(CCString::create("fire")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();
			addFire(ccp(x,y));
		}else if(name->isEqual(CCString::create("monster")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();
			key = "plistname";
			CCString* temp = ((CCString*)dict->objectForKey(key));
			string* plistname = new string(temp->getCString());
			plistname->append(".plist");
			string* spritename = new string(temp->getCString());
			spritename->append("_%d.png");

			MySprite* sprite =	MySprite::getInstance(ccp(x,y),plistname->c_str(),spritename->c_str(),m_pMyworld);		

			key = "enemy";
		    sprite->setType(((CCString*)dict->objectForKey(key))->isEqual(CCString::create("true")));//设置 敌人

			sprite->setTag(m_iMosterSpriteTag);
	

			if (((CCString*)dict->objectForKey(key))->isEqual(CCString::create("true"))){//如果是敌人
				m_iResuduoMonsterNum++;
				sprite->setCallbackFunc(this,callfunc_selector(GameSceneLayer::gameVictory));
			}else{
				sprite->setCallbackFunc(this,callfunc_selector(GameSceneLayer::gameFaild));
			}

			this->addChild(sprite);
			delete plistname;
			delete spritename;
		}else if(name->isEqual(CCString::create("wood")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();
			key = "sprite_name";
			CCString* sprite_name= (CCString*)dict->objectForKey(key);
			MyObject* sprite =	MyObject::getInstance(ccp(x,y),sprite_name->getCString(),m_pMyworld,MyObject::WOOD);		
			this->addChild(sprite);
		}else if(name->isEqual(CCString::create("iron_v")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();

			key = "bottom";
			int bottom = ((CCString*)dict->objectForKey(key))->intValue();
			key = "speed";
			int speed = ((CCString*)dict->objectForKey(key))->intValue();
			key = "top";
			int top = ((CCString*)dict->objectForKey(key))->intValue();

			MyObject* sprite =	MyObject::getInstance(ccp(x,y),"iron_v.png",m_pMyworld,MyObject::IRON_V);	
			sprite->setProperties(ccp(0,speed),ccp(top,bottom),ccp(0,0));
			this->addChild(sprite);
		}else if(name->isEqual(CCString::create("iron_h")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();

			key = "left";
			int left = ((CCString*)dict->objectForKey(key))->intValue();
			key = "speed";
			int speed = ((CCString*)dict->objectForKey(key))->intValue();
			key = "right";
			int right = ((CCString*)dict->objectForKey(key))->intValue();

			MyObject* sprite =	MyObject::getInstance(ccp(x,y),"iron_h.png",m_pMyworld,MyObject::IRON_H);	
			sprite->setProperties(ccp(speed,0),ccp(0,0),ccp(left,right));
			this->addChild(sprite);
		}else if(name->isEqual(CCString::create("triangle")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();
			MyObject* sprite =	MyObject::getInstance(ccp(x,y),"triangle.png",m_pMyworld,MyObject::TRIANGLE);		
			this->addChild(sprite);
		}else if(name->isEqual(CCString::create("circle")))
		{
			key = "x";
			int x = ((CCString*)dict->objectForKey(key))->intValue();
			key = "y";
			int y = ((CCString*)dict->objectForKey(key))->intValue();
			key = "sprite_name";
			CCString* sprite_name= (CCString*)dict->objectForKey(key);
			MyObject* sprite =	MyObject::getInstance(ccp(x,y),sprite_name->getCString(),m_pMyworld,MyObject::CIRCLE);		
			this->addChild(sprite);
		}	

	}
	
}

/************************************************************************/
/* 添加火苗       
@param point 添加的位置*/
/************************************************************************/
void GameSceneLayer::addFire(CCPoint point)
{

	

	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("fire.plist");

	CCSprite *fireSprite = CCSprite::createWithSpriteFrameName("fire_1.png");
	fireSprite->setAnchorPoint(ccp(0.5,0.5));
	fireSprite->setPosition(point);
	fireSprite->setTag(m_iFireSpriteTag);
	addStaicBodyFromSprite(fireSprite);

	CCAnimation *pAnimation = CCAnimation::create();
	pAnimation->setDelayPerUnit(0.1f);
	char*  temp = new char[20];
	for(int i = 1 ; i < 8 ;i++)
	{
		sprintf(temp,"fire_%d.png",i);
		pAnimation->addSpriteFrame(frameCache->spriteFrameByName(temp));
	}
	delete []temp;
	fireSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));

	this->addChild(fireSprite,5);
}



void GameSceneLayer::draw(){
	//m_pMyworld->DrawDebugData();
	if (m_bDrawlineFlag){
		ccDrawLine(m_LineStartpos,m_LineEndpos);
	}
}

void GameSceneLayer::tick(float dt){
	if (gamefinish)
	{
		return;
	}
	if (m_pMyworld)
		m_pMyworld->Step(dt, 10, 10);

	//基于box2d的坐标更新精灵的位置//
	
	for (b2Body *b = m_pMyworld->GetBodyList(); b; b = b->GetNext()){
		if (b->GetUserData() != NULL){
	
			CCSprite *sprite = (CCSprite*)b->GetUserData();
			if (sprite){
				b2Vec2 point = b->GetPosition();
				sprite->setPosition(ccp(point.x*PT_RATIO,point.y*PT_RATIO));
				sprite->setRotation(-(b->GetAngle() * (180/PI)));
				
			}
			
		}
	}

			
	//处理碰撞//
	for( std::vector<MyContact*>::iterator it = m_pMyContactListener->contact_list.begin(); 
		it != m_pMyContactListener->contact_list.end();
		it++)
	{
		MyContact *contact = *it;
		//b2WorldManifold worldManifold;
		//contact.GetWorldManifold(  &worldManifold );
		b2Body* bodyA = contact->fixtureA->GetBody();
		b2Body* bodyB = contact->fixtureB->GetBody();
		b2WorldManifold s = contact->manifold;
		//s->Initialize()
		//获取碰撞点//
		//CCPoint x = CCPointMake(s.points[0].x*PT_RATIO,s.points[0].y*PT_RATIO);//
		//glVertex2f(s->points[0].x,s->points[0].y);

		CCSprite* sa = (CCSprite*)bodyA->GetUserData();
		CCSprite* sb = (CCSprite*)bodyB->GetUserData();

		if (sa){
			if (sa->getTag() == 1001){
				((Bomb*)sa->getParent())->startBombing();

			}else if (sa->getTag() == m_iMosterSpriteTag && sb != NULL){
				if (((MySprite*)sa)->getMosterState() == NORMAL){
					((MySprite*)sa)->hurt();
				}
			}
			
		}

		if (sb){
			if (sb->getTag() == 1001){
				((Bomb*)sb->getParent())->startBombing();

			}else if (sb->getTag() == m_iMosterSpriteTag && sa != NULL){
				if (((MySprite*)sb)->getMosterState() == NORMAL){
					((MySprite*)sb)->hurt();
				}
				
			}
		}

		if (sa&&sb){
			if (sa->getTag() == m_iFireSpriteTag && sb->getTag() == m_iMosterSpriteTag){
				if (((MySprite*)sb)->getMosterState() != DIESTATE){
					((MySprite*)sb)->die();
				}
			}
			if (sb->getTag() == m_iFireSpriteTag && sa->getTag() == m_iMosterSpriteTag){
				if (((MySprite*)sa)->getMosterState() != DIESTATE){
					((MySprite*)sa)->die();
				}
			}
		}
		
		
	}
	m_pMyContactListener->clearContact();
}

void GameSceneLayer::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	lasttime = 0;
	Music_playBackgroundMusic("sound149.mp3");
}

void GameSceneLayer::onExit(){
	CCLayer::onExit();

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GameSceneLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

	CCPoint pos = pTouch->getLocation();
	m_bDrawlineFlag = true;
	m_LineEndpos = pos;


	//移动炮台
	//CCPoint pos = pTouch->getLocation();
	double nAngle = atan(((pos.y-m_LineStartpos.y)/abs(pos.x-m_LineStartpos.x)))*180/M_PI;
	CCSprite*cannonsprite = (CCSprite*)this->getChildByTag(m_iCannonSpriteTag);
	if(pos.x - m_LineStartpos.x < 0){
		cannonsprite->setRotation(180+nAngle);
	}else{
		cannonsprite->setRotation(360.0-nAngle);
	}
	//test//
	//doBomb(b2Vec2(pos.x/PT_RATIO,pos.y/PT_RATIO));
	//return false;


	return true;
}

void GameSceneLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	ccTouchEnded(pTouch,pEvent);
}


void GameSceneLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

	m_bDrawlineFlag = false;
	if ((MyGlobal::getcurrentTime() - lasttime) < 501)
	{
		return;
	}
	CCSprite * cannonSprite =(CCSprite*)this->getChildByTag(m_iCannonSpriteTag);
	if (cannonSprite->getActionManager()->getActionByTag(m_iCannonAnimateTag,cannonSprite)){
		return;
	}
	CCSprite *batterySprite = (CCSprite*)this->getChildByTag(m_iBatterySpriteTag);

	cannonSprite->runAction(m_pCannonAnimate);
    batterySprite->runAction(m_pBatteryAnimate);

	lasttime = MyGlobal::getcurrentTime();

	Music_playEffect("sound153.mp3");

	CCPoint pos = pTouch->getLocation();
    m_LineEndpos = pos;

	b2Vec2 orignVec(m_LineStartpos.x/PT_RATIO,m_LineStartpos.y/PT_RATIO);
	b2Vec2 destinatinoPos(pos.x/PT_RATIO,pos.y/PT_RATIO);
	b2Vec2 implus = b2Vec2(destinatinoPos-orignVec);


	//addChild(sprite);
	Bomb *sprite = Bomb::create();
	addChild(sprite);
	sprite->setSpritePos(m_LineStartpos);
	sprite->setCallbackFunc(this,callfuncN_selector(GameSceneLayer::Bombing));



	addBoxbodyFromSprite(sprite->getTheSprite(),b2Vec2(implus.x,implus.y));
	
}

void GameSceneLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

 
	ccTouchBegan(pTouch,pEvent);
	/*CCPoint pos = pTouch->getLocation();
	m_LineEndpos = pos;

	//移动炮台
	//CCPoint pos = pTouch->getLocation();
	double nAngle = atan(((pos.y-m_LineStartpos.y)/abs(pos.x-m_LineStartpos.x)))*180/M_PI;
	CCSprite*cannonsprite = (CCSprite*)this->getChildByTag(m_iCannonSpriteTag);
	if(pos.x - m_LineStartpos.x < 0){
		cannonsprite->setRotation(180+nAngle);
	}else{
		cannonsprite->setRotation(360.0-nAngle);
	}*/
}

/************************************************************************/
/* 在给定地方产生一个爆破效果                                                                    */
/************************************************************************/
void GameSceneLayer::doBomb(b2Vec2 pos){

	for (int i = 0;i < 100;i++)
	{
		float angle = 360/100*i;
		int x = cos(angle)*5+pos.x;
		int y = sin(angle)*5+pos.y;

	
		b2RayCastInput input;
		input.p1.Set(pos.x,pos.y);
		input.p2.Set(x,y);
		input.maxFraction = 1.0f;

		b2RayCastOutput output;
		b2Body *tempBody = NULL;
		b2Vec2 tempPoint;

		float minDistance = -1;

		for (b2Body *b = m_pMyworld->GetBodyList(); b; b = b->GetNext()){// 遍历所有刚体
			b2Shape *shape = b->GetFixtureList()->GetShape();
			bool hit =shape->RayCast(&output, input, b->GetTransform(),0);//判断是否与射线相交

			if(hit){//如果相交

				b2Vec2 hitPoint = input.p1 +output.fraction * (input.p2 - input.p1);
				float nowDistance = sqrtf(powf((pos.x-hitPoint.x), 2)+powf((pos.y-hitPoint.y), 2));
				if(minDistance == -1 || nowDistance < minDistance){
					minDistance = nowDistance;
					tempBody = b;
					tempPoint = hitPoint;
				}
			}
		}

		if(tempBody)//获得距离最近的刚体，给其施加一个冲量
		{
			b2Vec2 vec = tempPoint - pos;
			tempBody->ApplyForce(b2Vec2(vec.x*(1.0f-output.fraction)*300, vec.y*(1.0f-output.fraction)*300),tempPoint);
			tempBody->ApplyLinearImpulse(b2Vec2(vec.x*(1.0f-output.fraction)*30, vec.y*(1.0f-output.fraction)*30),tempPoint);
		    CCSprite* sa = (CCSprite*)tempBody->GetUserData();
			if (sa && sa->getTag() == m_iMosterSpriteTag){
				if (((MySprite*)sa)->getMosterState() != DIESTATE){
					((MySprite*)sa)->die();
				}		
			}
		}

	}
}

/************************************************************************/
/* 给精灵加上一个box2d body    
   @param vec 附加的冲量
*/
/************************************************************************/
void GameSceneLayer::addBoxbodyFromSprite(cocos2d::CCNode* sprite,b2Vec2 vec)
{
	//PTM_RATIO  这个数一般定义为： 32.0，
	//在box 世界中 是以 米 为单位的，
	//这里是将坐标兑换为box世界中的米，即除以 PTM_RATIO
	// Create physic body for cat
	b2CircleShape polygon;
	polygon.m_radius = (float)sprite->getContentSize().width/PT_RATIO/2;
	//polygon.SetAsBox((float)sprite->getContentSize().width/PT_RATIO/2, (float)sprite->getContentSize().height/PT_RATIO/2);


	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 1.0f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.5f;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)(sprite->getPosition().x / PT_RATIO),(float)(sprite->getPosition().y /PT_RATIO));
	bd.userData = sprite;
	bd.bullet = true;

	b2Body* spriteBody = m_pMyworld->CreateBody(&bd);//添加body到box2d world 中
	spriteBody->CreateFixture(&fixturedef);//

	spriteBody->ApplyLinearImpulse(vec,bd.position);

}  

void GameSceneLayer::addStaicBodyFromSprite(cocos2d::CCNode *sprite){
	//PTM_RATIO  这个数一般定义为： 32.0，
	//在box 世界中 是以 米 为单位的，
	//这里是将坐标兑换为box世界中的米，即除以 PTM_RATIO
	// Create physic body for cat
	b2CircleShape polygon;
	polygon.m_radius = (float)sprite->getContentSize().width/PT_RATIO/2;
	//polygon.SetAsBox((float)sprite->getContentSize().width/PT_RATIO/2, (float)sprite->getContentSize().height/PT_RATIO/2);
	

	b2FixtureDef fixturedef;
	fixturedef.shape = &polygon;
	fixturedef.density = 1.0f;
	fixturedef.friction = 0.3f;
	fixturedef.restitution = 0.5f;
	fixturedef.filter.maskBits  = 0x0008;

	b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position = b2Vec2((float)(sprite->getPosition().x / PT_RATIO),(float)(sprite->getPosition().y /PT_RATIO));
	bd.userData = sprite;
	

	b2Body* spriteBody = m_pMyworld->CreateBody(&bd);//添加body到box2d world 中
	spriteBody->CreateFixture(&fixturedef);//

	//spriteBody->ApplyLinearImpulse(vec,bd.position);
}

void GameSceneLayer::Bombing(cocos2d::CCNode *node){

	b2Vec2 vec(node->getPositionX()/PT_RATIO,node->getPositionY()/PT_RATIO);
	doBomb(vec);
	desdoryBodyBySprite((CCSprite*)node);
}

void GameSceneLayer::desdoryBodyBySprite(cocos2d::CCSprite* sprite){

	b2Body* spriteBody = NULL;
	for(b2Body* b = m_pMyworld->GetBodyList(); b; b=b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite* curSprite = (CCSprite*)b->GetUserData();
			if (curSprite == sprite)
			{
				spriteBody = b;
				m_pMyworld->DestroyBody(spriteBody);
				break;
			}
		}
	}
}

void GameSceneLayer::gameFaild(){
	gamefinish = true;
	CGameFaildLayer *layer = CGameFaildLayer::create();
	addChild(layer,100);
	unschedule(schedule_selector(GameSceneLayer::tick));
	//showSplashAd();//显示插屏 广告
}

void GameSceneLayer::gameVictory(){

	m_iResuduoMonsterNum--;
	if (m_iResuduoMonsterNum <= 0){
		gamefinish = true;
		CGameVictoryLayer *layer = CGameVictoryLayer::create();
		addChild(layer,100);
		unschedule(schedule_selector(GameSceneLayer::tick));
		//showSplashAd();//显示插屏广告
	}
	
}