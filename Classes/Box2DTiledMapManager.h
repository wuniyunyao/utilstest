#pragma once
#include "Box2DTMXReader.h"
class Box2DTiledMapManager
{
public:
	Box2DTiledMapManager(void);
	~Box2DTiledMapManager(void);
	bool readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap);
	bool readTiledMapForCoins(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMapForCoins(b2World* world,CCTMXTiledMap *tiledmap);
	void destroyCoin(b2Fixture* fixture);
private:
private:
	std::list<Box2DTMXReader*> blockReaderList;	
	std::list<Box2DTMXReader*> coinReaderList;	
	bool autorelease();
	CC_SYNTHESIZE(int, blockReaderListLength,BlockReaderListLength);
	CC_SYNTHESIZE(int, coinReaderListLength,coinReaderListLength);
	b2World* mWorld;
};

