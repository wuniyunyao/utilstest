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