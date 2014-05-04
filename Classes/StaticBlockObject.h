#ifndef __STATICBLOCKOBJECT_H_
#define __STATICBLOCKOBJECT_H_
#define PTM_RATIO 32
#include "cocos2d.h"
#include "Box2D\Box2D.h"
using namespace cocos2d;
/*
�ļ�����StaticBlocObject.h
�������������ڴ洢��̬�谭
�����ߣ�������ң
�������ڣ�2013/4/24
*/
class StaticBlockObject{
public:
	enum type
	{
		ST_POLYGON = 0,
		ST_CIRCLE
	};
	type shape;
	b2Fixture* fixture;
	float32 friction;
    float32 restitution;
    float32 density;
	StaticBlockObject(){
		density = 1.0f;
		friction = 0;
		restitution = 0;
	};
};
#endif //__STATICBLOCKOBJECT_H_