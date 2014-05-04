#include "Box2DTiledMapManager.h"


Box2DTiledMapManager::Box2DTiledMapManager(void):coinReaderListLength(2),blockReaderListLength(2)
{
}


Box2DTiledMapManager::~Box2DTiledMapManager(void)
{
}

bool Box2DTiledMapManager::autorelease(){
	if(blockReaderList.size() > blockReaderListLength){
		delete(blockReaderList.front());
		blockReaderList.pop_front();
	}
	if(coinReaderList.size() > coinReaderListLength){
		delete(coinReaderList.front());
		coinReaderList.pop_front();
	}
	return true;
}

bool Box2DTiledMapManager::readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap,float xOffset){
	Box2DTMXReader* newReader = new Box2DTMXReader();
	bool tag = newReader->readTiledMap(world,tiledmap,xOffset);
	blockReaderList.push_back(newReader);
	autorelease();
	return tag;
}
bool Box2DTiledMapManager::readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap){
	Box2DTMXReader* newReader = new Box2DTMXReader();
	bool tag = newReader->readTiledMap(world,tiledmap);
	blockReaderList.push_back(newReader);
	autorelease();
	return tag;
}
bool Box2DTiledMapManager::readTiledMapForCoins(b2World* world,CCTMXTiledMap *tiledmap,float xOffset){
	Box2DTMXReader* newReader = new Box2DTMXReader();
	bool tag = newReader->readTiledMap(world,tiledmap,xOffset,"CoinObjects",b2_kinematicBody);
	coinReaderList.push_back(newReader);
	autorelease();
	return tag;
}
bool Box2DTiledMapManager::readTiledMapForCoins(b2World* world,CCTMXTiledMap *tiledmap){
	Box2DTMXReader* newReader = new Box2DTMXReader();
	bool tag = newReader->readTiledMap(world,tiledmap,0,"CoinObjects",b2_kinematicBody);
	coinReaderList.push_back(newReader);
	autorelease();
	return tag;
}

void Box2DTiledMapManager::destroyCoin(b2Fixture* fixture){
	coinReaderList.front()->destroyFixture(fixture);
}