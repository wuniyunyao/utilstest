#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2DTiledMapManager.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
class HelloWorld : public cocos2d::CCLayer
{
	GLESDebugDraw* mDebugDraw; 
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	
	Box2DTiledMapManager tool;

	b2World* mWorld;
	virtual void update(float dt);
private:
	// 绘制物理世界debug区域
    void draw();
    
    // 开启物理世界debug
    void setDebug(bool isDebug);
};

#endif // __HELLOWORLD_SCENE_H__
