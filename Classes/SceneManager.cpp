//
//  SceneManager.cpp
//  MyPlane
//
//  Created by К·дм on 16/04/29.
//
//

#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

SceneManager* SceneManager::mSceneManager = NULL;

SceneManager* SceneManager::getInstance(){
	if (mSceneManager == NULL) {
		mSceneManager = new SceneManager();
	}
	return mSceneManager;
}

void SceneManager::changeScene(SceneType sceneType){
	Scene* scene = NULL;
	switch (sceneType) {
	case MenuScene:
		scene = MenuScene::createScene();
		break;
	case GameScene:
		scene = GameScene::createScene();
		break;
	default:
		break;
	}

	if (scene == NULL) {
		return;
	}
	Director* director = Director::getInstance();
	Scene* curScene = director->getRunningScene();
	if (curScene == NULL) {
		director->runWithScene(scene);
	}
	else{
		director->replaceScene(TransitionFade::create(1.2f, scene));
	}
}