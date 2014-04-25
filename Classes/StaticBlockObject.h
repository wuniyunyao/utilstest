#ifndef __STATICBLOCKOBJECT_H_
#define __STATICBLOCKOBJECT_H_
#define PTM_RATIO 32
#include "cocos2d.h"
#include "Box2D\Box2D.h"
using namespace cocos2d;
/*
文件名：StaticBlocObject.h
描述：该类用于存储静态阻碍
创建者：无逆云遥
创建日期：2013/4/24
*/
struct StaticBlockObject : public b2FixtureDef{
public:
	enum type
	{
		ST_POLYGON,
		ST_CIRCLE
	};
	type shape;	
	b2Fixture *fixture;
};
#endif //__STATICBLOCKOBJECT_H_