#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Floor.h"

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();

	virtual bool init();
    
    virtual void update(float delta);

	CREATE_FUNC(GameScene);

private:
	//UI's Node
	cocos2d::Node* n_GameUI;
	//Floors's Node
	cocos2d::Node* m_floorsNode;
    //Bottom's Node
    cocos2d::Node* m_bottomNode;
	Player* player;
	//Is Player Moved left or right
    bool moveL,moveR;
	//Now Level
	int level;
	//当前所在floor层数
	int floorNowNum;
	//floors 总层数
	int floorsNum;

	void genFloors(cocos2d::Node* node);
	void setAllZOrders();
	void checkNowFloor();
	void collisionWithFloors();

    void BtLeftOnTouch(Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
    void BtRightOnTouch(Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
	void BtAttackOnClick(Ref *pSender);
	void BtJumpOnClick(Ref *pSender);
};

