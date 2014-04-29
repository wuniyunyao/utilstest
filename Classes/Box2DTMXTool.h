#ifndef __BOX2DTMXTOOL_H_
#define __BOX2DTMXTOOL_H_
#define PTM_RATIO 32
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "StaticBlockObject.h"
using namespace cocos2d;
/*
文件名：Box2DTMLTool.h
描述：该工具用于将tiled map中的地形读出供Box2D使用
创建者：无逆云遥
创建日期：2013/4/24
*/
class Box2DTMXTool{
public:
	Box2DTMXTool();
	bool readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap);
	bool readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	void destoryAllBlocks();
	std::vector<StaticBlockObject*> mStaticBlockList;
private:
	CCTMXTiledMap* mTiledMap;
	b2Body* mBody;	
	float contentScaleFactor;
	float offset;
	b2World* mWorld;
	CC_SYNTHESIZE(int, bodyListLength,BodyListLength);
	std::list<b2Body*> mBodyList;
	bool autorelease();
};
#endif //__BOX2DTMXTOOL_H_