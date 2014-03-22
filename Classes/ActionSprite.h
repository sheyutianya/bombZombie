#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

#include "cocos2d.h"
#include "logo.h"
typedef enum _ActionState {
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateAttack1,
	kActionStateAttack2,
	kActionStateAttack3,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateKnockedOut
} ActionState;

typedef struct _BoundingBox {
	cocos2d::CCRect actual;
	cocos2d::CCRect original;
} BoundingBox;

class ActionSprite:public cocos2d::CCSprite{
public:
	ActionSprite();
	~ActionSprite();


	CC_SYNTHESIZE(ActionState,m_currentActionState,CurrentActionState);

	virtual void attack();



	//actions
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_pidleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_pattackAction1, AttackAction1);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_pattackAction2, AttackAction2);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_pattackAction3, AttackAction3);
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_pwalkAction, WalkAction);
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_phurtAction, HurtAction);
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, m_pknockedOutAction, KnockedOutAction);

	//攻击和挨打矩形
	CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
	CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);

};

#endif