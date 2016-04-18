#pragma once

#include "cocos2d.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

private:
	cocos2d::Node* n_GameUI;
	Player* player;

	void BtLeftOnClick(Ref *pSender);
	void BtRightOnClick(Ref *pSender);
	void BtAttackOnClick(Ref *pSender);
	void BtJumpOnClick(Ref *pSender);
};

