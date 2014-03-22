#include "Hero.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Hero::Hero(void)
{
}

Hero::~Hero(void)
{
}

bool Hero::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!ActionSprite::initWithFile("roleaction/image 415.png"));		

		//idle animation
		CCAnimation *idleAnimation =CCAnimation::create();
		char *tempchar = new char[100];
		for (int i = 0; i < 5; i++){
			sprintf(tempchar,"roleaction/image %d.png",i+418);
			idleAnimation->addSpriteFrameWithFileName(tempchar);
		}
		idleAnimation->setDelayPerUnit(float(1.0 / 12.0));
		idleAnimation->setRestoreOriginalFrame(true);
		CCAnimate *animate = CCAnimate::create(idleAnimation);
		
		CCAction *maction = CCRepeatForever::create(animate);
		this->setIdleAction(maction);

		//attack animation
		CCAnimation *attacanimation1 = CCAnimation::create();
		for (int i = 0 ; i < 9 ; i++){
			sprintf(tempchar,"attackaction/image%d.png",i+463);
			attacanimation1->addSpriteFrameWithFileName(tempchar);
		}
		attacanimation1->setDelayPerUnit(1.0f/24);
		attacanimation1->setRestoreOriginalFrame(false);
		CCAnimate *attackanimate1 = CCAnimate::create(attacanimation1);
		this->setAttackAction1(attackanimate1);
		
		CCAnimation *attacanimation2 = CCAnimation::create();
		for (int i = 0 ; i < 10 ; i++){
			sprintf(tempchar,"attackaction/image%d.png",i+482);
			attacanimation2->addSpriteFrameWithFileName(tempchar);
		}
		attacanimation2->setDelayPerUnit(1.0f/24);
		attacanimation2->setRestoreOriginalFrame(false);
		CCAnimate *attackanimate2 = CCAnimate::create(attacanimation2);
		this->setAttackAction2(attackanimate2);

		CCAnimation *attacanimation3 = CCAnimation::create();
		for (int i = 0 ; i < 8 ; i++){
			sprintf(tempchar,"attackaction/image%d.png",i+503);
			attacanimation3->addSpriteFrameWithFileName(tempchar);
		}
		attacanimation3->setDelayPerUnit(1.0f/24);
		attacanimation3->setRestoreOriginalFrame(false);
		CCAnimate *attackanimate3 = CCAnimate::create(attacanimation3);
		this->setAttackAction3(attackanimate3);
	
		//for (i = 0; i < 3; i++)
		//{
		//	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_attack_00_%02d.png", i)->getCString());
		//	attackFrames->addObject(frame);
		//}
		//CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, float(1.0 / 24.0));
		//this->setAttackAction(CCSequence::create(CCAnimate::create(attackAnimation), CCCallFunc::create(this, callfunc_selector(Hero::idle)), NULL));

		////walk animation
		//CCArray *walkFrames = CCArray::createWithCapacity(8);
		//for (i = 0; i < 8; i++)
		//{
		//	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_walk_%02d.png", i)->getCString());
		//	walkFrames->addObject(frame);
		//}
		//CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, float(1.0 / 12.0));
		//this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));

		////hurt animation
		//CCArray *hurtFrames = CCArray::createWithCapacity(3);
		//for (i = 0; i < 3; i++)
		//{
		//	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_hurt_%02d.png", i)->getCString());
		//	hurtFrames->addObject(frame);
		//}
		//CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(hurtFrames, float(1.0 / 12.0));
		//this->setHurtAction(CCSequence::create(CCAnimate::create(hurtAnimation), CCCallFunc::create(this, callfunc_selector(Hero::idle)), NULL));

		////knocked out animation
		//CCArray *knockedOutFrames = CCArray::createWithCapacity(5);
		//for (i = 0; i < 5; i++)
		//{
		//	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_knockout_%02d.png", i)->getCString());
		//	knockedOutFrames->addObject(frame);
		//}
		//CCAnimation *knockedOutAnimation = CCAnimation::createWithSpriteFrames(knockedOutFrames, float(1.0 / 12.0));
		//this->setKnockedOutAction(CCSequence::create(CCAnimate::create(knockedOutAnimation), CCBlink::create(2.0, 10.0), NULL));

		//this->setCenterToBottom(39.0);
		//this->setCenterToSides(29.0);
		//this->setHitPoints(100.0);
		//this->setDamage(20.0);
		//this->setWalkSpeed(80.0);

		//this->setHitbox(this->createBoundingBoxWithOrigin(ccp(-this->getCenterToSides(), -this->getCenterToBottom()),
		//	CCSizeMake(this->getCenterToSides() * 2, this->getCenterToBottom() * 2)));
		//this->setAttackBox(this->createBoundingBoxWithOrigin(ccp(this->getCenterToSides(), -10), CCSizeMake(20, 20)));

		this->setCurrentActionState(kActionStateIdle);

		bRet = true;
	} while (0);

	return bRet;
}

void Hero::knockout()
{
	//ActionSprite::knockout();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pd_herodeath.wav");
}

void Hero::Heroattack(){

	if (getCurrentActionState() == kActionStateIdle){

		this->runAction(getAttackAction1());
		this->setCurrentActionState(kActionStateAttack1);

	}else if (getCurrentActionState() == kActionStateAttack1){

		this->runAction(getAttackAction2());
		this->setCurrentActionState(kActionStateAttack2);

	}else if (getCurrentActionState() == kActionStateAttack2){

		this->runAction(getAttackAction3());
		this->setCurrentActionState(kActionStateAttack3);

	}else if (getCurrentActionState() == kActionStateAttack1){

		this->runAction(getAttackAction1());
		this->setCurrentActionState(kActionStateAttack3);
	}

	//this->runAction()
	
}