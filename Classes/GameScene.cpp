#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
	auto rootnode = CSLoader::createNode("Scene/GameScene.csb");
	this->addChild(rootnode);

	n_GameUI = rootnode->getChildByName("UILayer");

	auto bt_Left = (Button*)n_GameUI->getChildByName("Bt_Left");
	auto bt_Right = (Button*)n_GameUI->getChildByName("Bt_Right");
	auto bt_Attack = (Button*)n_GameUI->getChildByName("Bt_Attack");
	auto bt_Jump = (Button*)n_GameUI->getChildByName("Bt_Jump");

	bt_Left->addClickEventListener(CC_CALLBACK_1(GameScene::BtLeftOnClick, this));
	bt_Right->addClickEventListener(CC_CALLBACK_1(GameScene::BtRightOnClick, this));
	bt_Attack->addClickEventListener(CC_CALLBACK_1(GameScene::BtAttackOnClick, this));
	bt_Jump->addClickEventListener(CC_CALLBACK_1(GameScene::BtJumpOnClick, this));

	return true;
}

void GameScene::BtLeftOnClick(Ref *pSender){
	CCLOG("OnClick");
}

void GameScene::BtRightOnClick(Ref *pSender){
	
}

void GameScene::BtAttackOnClick(Ref *pSender){

}

void GameScene::BtJumpOnClick(Ref *pSender){

}
