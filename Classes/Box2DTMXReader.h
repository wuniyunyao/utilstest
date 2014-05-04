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
class Box2DTMXReader{
public:
	Box2DTMXReader();
	~Box2DTMXReader();
	bool readTiledMap(b2World* world,CCTMXTiledMap *tiledmap,float xOffset,const char* layerName,b2BodyType type);
	bool readTiledMap(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMap(b2World* world,CCTMXTiledMap *tiledmap);
	bool destroyFixture(b2Fixture* fixture);

	void destory();
	std::vector<StaticBlockObject*> mStaticBlockList;
	/*b2Body* getBody(){
		return mBody;
	};*/
private:
	CCTMXTiledMap* mTiledMap;
	b2Body* mBody;	
	float contentScaleFactor;
	float curXOffset;
	b2World* mWorld;
	CC_SYNTHESIZE(int, bodyListLength,BodyListLength);
	//std::list<b2Body*> mBlocksBodyList;
	//bool autorelease();
};
#endif //__BOX2DTMXTOOL_H_