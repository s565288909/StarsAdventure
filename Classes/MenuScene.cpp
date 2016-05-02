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
    
    //通过csb创建动画
    ActionTimeline *action = CSLoader::createTimeline("Scene/MenuScene.csb");
    rootnode->runAction(action);
    
    //同一个文件创建的节点只能使用同一个文件创建的动画。
    //从第0帧循环播放动画
    action->gotoFrameAndPlay(0,true);

	auto strBt = (Button*)rootnode->getChildByName("startbt");
	
    strBt->addClickEventListener([](Ref* ref){
        SceneManager::getInstance()->changeScene(SceneManager::GameScene);
    });

	return true;
}