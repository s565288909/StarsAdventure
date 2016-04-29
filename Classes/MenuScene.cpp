#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootnode = CSLoader::createNode("Scene/MenuScene.csb");
	this->addChild(rootnode);

	auto strBt = (Button*)rootnode->getChildByName("startbt");
	
	strBt->addTouchEventListener([&]{
		SceneManager::getInstance()->changeScene(SceneManager::GameScene);
	});

	return true;
}