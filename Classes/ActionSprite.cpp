#include "ActionSprite.h"

USING_NS_CC;

ActionSprite::ActionSprite(){
	m_pidleAction = NULL;
	m_pattackAction1 = NULL;
	m_pattackAction2 = NULL;
	m_pattackAction3 = NULL;
}

ActionSprite::~ActionSprite(){

}



void ActionSprite::attack()
{
	if (m_currentActionState == kActionStateIdle || m_currentActionState == kActionStateAttack1 || m_currentActionState == kActionStateWalk)
	{
		this->stopAllActions();
		//this->runAction(m_pattackAction);
		m_currentActionState = kActionStateAttack1;
	}
}