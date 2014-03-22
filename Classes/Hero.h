#pragma once
#include "ActionSprite.h"

class Hero : public ActionSprite
{
public:
	Hero(void);
	~Hero(void);

	CREATE_FUNC(Hero);
	bool init();
	void knockout();

public:
	void Heroattack();
};
