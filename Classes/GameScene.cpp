#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Floor.h"

USING_NS_CC;
using namespace ui;


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init(){
	if (!Layer::init())
	{
		return false;
	}
    moveL = moveR = false;
    
    auto whitelayer = CCLayerColor::create(ccc4(255, 251, 240, 255));
    this->addChild(whitelayer);
    
	auto rootnode = CSLoader::createNode("Scene/GameScene.csb");
	this->addChild(rootnode);

	player = Player::Create(rootnode->getChildByName("Player"));

	n_GameUI = rootnode->getChildByName("UILayer");

	auto bt_Left = (Button*)n_GameUI->getChildByName("Bt_Left");
	auto bt_Right = (Button*)n_GameUI->getChildByName("Bt_Right");
	auto bt_Attack = (Button*)n_GameUI->getChildByName("Bt_Attack");
	auto bt_Jump = (Button*)n_GameUI->getChildByName("Bt_Jump");

    bt_Left->addTouchEventListener(CC_CALLBACK_2(GameScene::BtLeftOnTouch, this));
    bt_Right->addTouchEventListener(CC_CALLBACK_2(GameScene::BtRightOnTouch, this));
	bt_Attack->addClickEventListener(CC_CALLBACK_1(GameScene::BtAttackOnClick, this));
	bt_Jump->addClickEventListener(CC_CALLBACK_1(GameScene::BtJumpOnClick, this));

    this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta){
    if (moveL) {
        player->MoveLeft();
    }else if (moveR){
        player->MoveRight();
    }
}

void GameScene::genFloors(){
	Floor floor = CSLoader::createNode("Node/Floor.csb");
}

void GameScene::setAllZOrders()
{
	//人物等Zorder值:10-49
	//Floor的Zorder值：50-99
	//场景的UILayer等：100-
	player->getNode()->setZOrder(10);

	n_GameUI->setZOrder(100);

}

void GameScene::BtLeftOnTouch(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            if(!moveR) moveL = true;
            break;
        case Widget::TouchEventType::ENDED:
            if(!moveR){
                moveL = false;
                player->StopMove();
            }
            break;
        case Widget::TouchEventType::CANCELED:
            if(!moveR){
                moveL = false;
                player->StopMove();
            }
            break;
        default:
            break;
    }
}

void GameScene::BtRightOnTouch(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            if(!moveL) moveR = true;
            break;
        case Widget::TouchEventType::ENDED:
            if(!moveL){
                moveR = false;
                player->StopMove();
            }
            break;
        case Widget::TouchEventType::CANCELED:
            if(!moveL){
                moveR = false;
                player->StopMove();
            }
            break;
        default:
            break;
    }
}

void GameScene::BtAttackOnClick(Ref *pSender){
    player->Attack();
}

void GameScene::BtJumpOnClick(Ref *pSender){
    player->Jump();
}
