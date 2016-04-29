//
//  SceneManager.hpp
//  MyPlane
//
//  Created by К·дм on 16/04/29.
//
//

#ifndef SceneManager_h
#define SceneManager_h

#include <cocos2d.h>

USING_NS_CC;

class SceneManager : public Ref
{
public:
	enum SceneType{
		MenuScene,
		GameScene
	};
	static SceneManager* getInstance();
	void changeScene(SceneType sceneType);

private:
	static SceneManager* mSceneManager;
};

#endif /* SceneManager_h */